#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connectionSettings = QApplication::applicationDirPath() + "/SAWsettings.ini";
    QSettings settings(connectionSettings, QSettings::IniFormat);
    ui->db_name->setText(settings.value("database", "").toString());
    ui->db_host->setText(settings.value("connecthost", "").toString());
    ui->db_user->setText(settings.value("username", "").toString());
    ui->db_passw->setText(settings.value("passwd", "").toString());

    date_start = ui->date_start->date();
    date_end = ui->date_end->date();
    time_start = ui->time_start->time();
    time_end = ui->time_end->time();

    QStringList list = (QStringList()<<"60"<<"30"<<"20"<<"15"<<"10"<<"6"<<"5"<<"1");
    ui->comboTime->addItems(list);
    QStringList list2 = (QStringList()<<";"<<",");
    ui->comboExportDelim->addItems(list2);

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableSensors->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableSensors->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableSensors->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableSensors->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableRawData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableRawData->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableRawData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableRawData->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableConvertedData->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableConvertedData->setSelectionBehavior(QAbstractItemView::SelectRows);
    //ui->tableConvertedData->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableConvertedData->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(on_tab(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushStart_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString db_name = ui->db_name->text(),
            db_host = ui->db_host->text(),
            db_user = ui->db_user->text(),
            db_passw = ui->db_passw->text();

    QDateTime beginDateTime(date_start, time_start),
              endDateTime(date_end, time_end);
    if(beginDateTime>=endDateTime){
        this->new_log_entry("Begin time is after end time, please correct this");
        return;
    }


    if(dataBase.openConnectie(db_host, db_name, db_user, db_passw))
    {
        this->new_log_entry("Connection is made");

        if(normalSensors.size()!=0 && ruimte!=0){
            ruimte = ui->tableView->model()->data(ui->tableView->selectionModel()->selectedIndexes()[0]).toInt();
            ruimtenaam = ui->tableView->model()->data(ui->tableView->selectionModel()->selectedIndexes()[1]).toString();
            this->new_log_entry("Selected room: " + QString::number(ruimte));

            this->new_log_entry("Getting sensor IDs " + ruimtenaam);
            Query opvragen;
            opvragen.fieldQuery(ruimte);

            QStandardItemModel *tableSensors = new QStandardItemModel(opvragen.totalRows(),5,this); //x Rows and 3 Columns
            tableSensors->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
            tableSensors->setHorizontalHeaderItem(1, new QStandardItem(QString("Owner Id")));
            tableSensors->setHorizontalHeaderItem(2, new QStandardItem(QString("Type")));
            tableSensors->setHorizontalHeaderItem(3, new QStandardItem(QString("Fieldtype")));
            tableSensors->setHorizontalHeaderItem(4, new QStandardItem(QString("Description")));

            if(opvragen.returnLastResult().empty()){
                this->new_log_entry("No sensors found in: " + ruimtenaam);
                if(extraSensors.size()==0){
                    if(dataBase.sluitConnectie()) {
                        this->new_log_entry("Connection is closed");
                    } else {
                        this->new_log_entry("!!!Connection not closed!!!");
                    }
                    this->new_log_entry("--------------------");
                    return;
                }
            }
            else{
                currentResult = opvragen.returnLastResult();
                for (unsigned int i = 0; i < currentResult.size(); i++){
                    for (unsigned int j = 0; j < currentResult[i].size(); j++){
                        QStandardItem *firstRow = new QStandardItem(currentResult[i][j]);
                        tableSensors->setItem(i,j,firstRow);
                    }
                    //cout << currentResult[i][0].toStdString() << " - " << currentResult[i][1].toStdString() << " - " << currentResult[i][2].toStdString() << " - " << currentResult[i][3].toStdString() << endl;
                }
                ui->tableSensors->setModel(tableSensors);
                for (unsigned int i = 0; i < currentResult.size(); i++){
                    ui->tableSensors->setRowHeight(i,20);
                }
            }
            addNormalSensors();
        }
        if(extraSensors.size()!=0){
            addExtraSensors();
        }

        dateTimeCalc converter;
        currentData.clear();
        int timeslot = ui->comboTime->currentText().toInt();
        for(int x=0; beginDateTime < endDateTime.addSecs(timeslot*60); x++){
            std::vector<QString> row;
            if(x==0){
                row.push_back("Name");
                row.push_back("Time");
                currentData.push_back(row);
                row.clear();
                row.push_back("ID");
                row.push_back("00");
                currentData.push_back(row);
                row.clear();
            }
            row.push_back(beginDateTime.toString("dd-MM-yyyy hh:mm:ss"));
            row.push_back(converter.QTtoPOSTGRES(beginDateTime.date(),beginDateTime.time()));
            currentData.push_back(row);
            beginDateTime = beginDateTime.addSecs(timeslot*60);
        }

        Query sensordata;
        QString begin = converter.QTtoPOSTGRES(date_start.addDays(-2), time_start);
        QString end = converter.QTtoPOSTGRES(date_end.addDays(2), time_end);

        for (unsigned int i = 0; i < selectedSensorenID.size(); i++)
        {
            this->new_log_entry("Getting sensor data "+QString::number(selectedSensorenID[i][0])+"-"+QString::number(selectedSensorenID[i][1]));
            sensordata.fieldhistoryQuery(selectedSensorenID[i][0], begin, end);

            convertData databewerken;
            currentResult = sensordata.returnLastResult();
            databewerken.convertEverything(selectedSensorenID[i][1],selectedSensorenID[i][0],this,&currentData,currentResult);
        }

        QStandardItemModel *tableRawData = new QStandardItemModel(sensordata.totalRows(),2,this); //x Rows and 3 Columns
        tableRawData->setHorizontalHeaderItem(0, new QStandardItem(QString("Timestamp")));
        tableRawData->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));
        tableRawData->setHorizontalHeaderItem(2, new QStandardItem(QString("Value")));

        currentResult = sensordata.returnLastResult();
        for (unsigned int i = 0; i < currentResult.size(); i++)
        {
            QStandardItem *firstRow = new QStandardItem(currentResult[i][0]);
            tableRawData->setItem(i,0,firstRow);
            QDateTime rawDataTime = converter.POSTGREStoQT(currentResult[i][0]);
            QStandardItem *firstRow1 = new QStandardItem(rawDataTime.toString("dd-MM-yyyy hh:mm:ss"));
            tableRawData->setItem(i,1,firstRow1);
            QStandardItem *firstRow2 = new QStandardItem(currentResult[i][1]);
            tableRawData->setItem(i,2,firstRow2);
        }
        ui->tableRawData->setModel(tableRawData);
        for (unsigned int i = 0; i < currentResult.size(); i++){
            ui->tableRawData->setRowHeight(i,20);
        }

        QStandardItemModel *tableConvertedData = new QStandardItemModel(5,2,this); //x Rows and 3 Columns
        tableConvertedData->setHorizontalHeaderItem(0, new QStandardItem(QString("Time")));
        tableConvertedData->setHorizontalHeaderItem(1, new QStandardItem(QString("Time")));
        currentData.resize(currentData.size()-1);
        for (unsigned int i = 0; i < currentData.size(); i++){
            for (unsigned int j = 0; j < currentData[i].size(); j++){
                QStandardItem *firstRow = new QStandardItem(currentData[i][j]);
                tableConvertedData->setItem(i,j,firstRow);
            }
        }
        ui->tableConvertedData->setModel(tableConvertedData);
        for (unsigned int i = 0; i < currentData.size(); i++){
            ui->tableConvertedData->setRowHeight(i,20);
        }

        ui->pushExportCSV->setEnabled(true);

        selectedSensorenID.clear();
        if(dataBase.sluitConnectie()) {
            this->new_log_entry("Connection is closed");
        }
        else
        {
            this->new_log_entry("!!!Connection not closed!!!");
        }
    }
    else {
        this->new_log_entry("No connection is made");
    }

    this->new_log_entry("--------------------");

    QApplication::restoreOverrideCursor();

    // Ga direct naar tab "Converted data"
    ui->tabWidget->setCurrentIndex(2);
}

void MainWindow::on_pushRefresh_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString db_name = ui->db_name->text(),
            db_host = ui->db_host->text(),
            db_user = ui->db_user->text(),
            db_passw = ui->db_passw->text();

    QSettings settings(connectionSettings, QSettings::IniFormat);
    settings.setValue("database", db_name);
    settings.setValue("connecthost", db_host);
    settings.setValue("username", db_user);
    settings.setValue("passwd", db_passw);
    settings.sync();

    if(dataBase.openConnectie(db_host, db_name, db_user, db_passw))
    {
        this->new_log_entry("Connection is made");
        this->new_log_entry("Getting all rooms");

        Query lokalen;
        lokalen.locationQuery();

        QStandardItemModel *model = new QStandardItemModel(lokalen.totalRows(),2,this); //x Rows and 3 Columns
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Ruimte")));

        aanwezigeruimtes.clear();
        aanwezigeruimtes = lokalen.returnLastResult();
        for (unsigned int i = 0; i < aanwezigeruimtes.size(); i++){
            for (unsigned int j = 0; j < aanwezigeruimtes[i].size(); j++){
                QStandardItem *firstRow = new QStandardItem(aanwezigeruimtes[i][j]);
                model->setItem(i,j,firstRow);
            }
        }

        ui->tableView->setModel(model);
        ui->tableView->setCurrentIndex(ui->tableView->model()->index(0,1));
        for (unsigned int i = 0; i < aanwezigeruimtes.size(); i++){
            ui->tableView->setRowHeight(i,20);
        }

        ruimte = ui->tableView->model()->data(ui->tableView->selectionModel()->selectedIndexes()[0]).toInt();
        //buttonStartEnabling();

        this->new_log_entry("Please select a room and then click on 'start'");

        if(dataBase.sluitConnectie()) {
            this->new_log_entry("Connection is closed");
        }
        else
        {
            this->new_log_entry("!!!Connection not closed!!!");
        }
    }
    else
    {
        this->new_log_entry(dataBase.lastError());
        this->new_log_entry("Niet gelukt");
    }

    this->new_log_entry("--------------------");

    QApplication::restoreOverrideCursor();
}

void MainWindow::new_log_entry(QString newTextLine){
    logText = QTime::currentTime().toString() + "\t" + newTextLine + "\n" + ui->logEntry->toPlainText();
    ui->logEntry->setText(logText);
}

void MainWindow::buttonStartEnabling()
{
    if((ruimte!=0 && normalSensors.size()!=0) || extraSensors.size()!=0)
    {
        ui->pushStart->setEnabled(true);
    }
    else
    {
        ui->pushStart->setEnabled(false);
    }
}

//normalSensors[k]==37 && sensornaam.mid(0,9)=="CO2 Level"

void MainWindow::addExtraSensors(){
    if(ui->checkOutTemp->checkState()){
        std::vector< int > row{249114, 151}; // kan ook 35
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutLight->checkState()){
        std::vector< int > row{472293, 152};
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutAirSpeed->checkState()){
        std::vector< int > row{249118, 153};
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutAirDest->checkState()){
        std::vector< int > row{249119, 154};
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutScherming->checkState()){
        std::vector< int > row{341659, 155};
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutRain->checkState()){
        std::vector< int > row{249117, 156};
        selectedSensorenID.push_back(row);
    }
    if(ui->checkOutHumidity->checkState()){
        std::vector< int > row{341637, 157};
        selectedSensorenID.push_back(row);
    }
}

void MainWindow::addNormalSensors(){
    for (unsigned int i = 0; i < currentResult.size(); i++){
        std::vector< int > row;
        for (unsigned int k = 0; k < normalSensors.size(); k++){
            QString sensornaam = currentResult[i][4];
            if(normalSensors[k]==48 && sensornaam.mid(0,11)=="MeasAirflow"){
                row.push_back(currentResult[i][0].toInt());
                row.push_back(48);
                selectedSensorenID.push_back(row);
            }
            else if(normalSensors[k]==37 && sensornaam.mid(0,9)=="CO2 Level"){
                row.push_back(currentResult[i][0].toInt());
                row.push_back(37);
                selectedSensorenID.push_back(row);
            }
            else if(normalSensors[k]==currentResult[i][3].toInt() && normalSensors[k]!=37 && normalSensors[k]!=48){
                row.push_back(currentResult[i][0].toInt());
                row.push_back(currentResult[i][3].toInt());
                selectedSensorenID.push_back(row);
            }
            else if(normalSensors[k]==83 && sensornaam.mid(0,18)=="Estimated Presence"){
                row.push_back(currentResult[i][0].toInt());
                row.push_back(83);
                selectedSensorenID.push_back(row);
            }
            else if(normalSensors[k]==69 && sensornaam.mid(0,21)=="Valve Actual Position"){
                row.push_back(currentResult[i][0].toInt());
                row.push_back(69);
                selectedSensorenID.push_back(row);
            }
        }
    }
}

void MainWindow::on_pushExportCSV_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    exportCSV CSVexporter;
    CSVexporter.prepData(currentData);

    if(normalSensors.size() == 0){
        ruimtenaam="Buiten";
    }
    QString bmin;
    if(time_start.minute()<10) {
        bmin = "0"+QString::number(time_start.minute());
    }
    else {
        bmin = QString::number(time_start.minute());
    }
    QString emin;
    if(time_end.minute()<10) {
        emin = "0"+QString::number(time_end.minute());
    }
    else {
        emin = QString::number(time_end.minute());
    }

    QString delimiter = ui->comboExportDelim->currentText();
    QFileDialog savelocation;
    savelocation.setFileMode(QFileDialog::Directory);
    savelocation.setOption(QFileDialog::ShowDirsOnly);
    savelocation.exec();

    QString settingsDir = savelocation.directory().absolutePath();
    CSVexporter.saveCSV(settingsDir + "/Ruimte_"+ruimtenaam+"_Van_"+QString::number(date_start.year())+"-"+QString::number(date_start.month())+"-"+QString::number(date_start.day())+"_"+QString::number(time_start.hour())+"-"+bmin+"_Tot_"+QString::number(date_end.year())+"-"+QString::number(date_end.month())+"-"+QString::number(date_end.day())+"_"+QString::number(time_end.hour())+"-"+emin+"_.csv", delimiter);
    this->new_log_entry("CSV saved!");
    this->new_log_entry("--------------------");

    QApplication::restoreOverrideCursor();
}

///// (KLEINE) ON BUTTON CLICKED FUNCTIES /////

void MainWindow::on_date_start_userDateChanged(const QDate &date)
{
    date_start = date;
}

void MainWindow::on_date_end_userDateChanged(const QDate &date)
{
    date_end = date;
}

void MainWindow::on_time_start_timeChanged(const QTime &time)
{
    time_start = time;
}

void MainWindow::on_time_end_timeChanged(const QTime &time)
{
    time_end = time;
}

void MainWindow::on_checkPres_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(83);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 83), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkCO2_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(37);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 37), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkAirFlow_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(48);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 48), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkTempIr_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(48);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 48), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkLightState_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(56);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 56), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkValve_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(69);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 69), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkTemp_clicked(bool checked)
{
    if(checked)
    {
        normalSensors.push_back(46);
        normalSensors.push_back(66);
        normalSensors.push_back(67);
    }
    else
    {
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 46), normalSensors.end());
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 66), normalSensors.end());
        normalSensors.erase(std::remove(normalSensors.begin(), normalSensors.end(), 67), normalSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutTemp_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(151);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 151), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutLight_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(152);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 152), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutAirSpeed_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(153);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 153), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutAirDest_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(154);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 154), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutScherming_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(155);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 155), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutRain_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(156);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 156), extraSensors.end());
    }
    buttonStartEnabling();
}

void MainWindow::on_checkOutHumidity_clicked(bool checked)
{
    if(checked)
    {
        extraSensors.push_back(157);
    }
    else
    {
        extraSensors.erase(std::remove(extraSensors.begin(), extraSensors.end(), 157), extraSensors.end());
    }
    buttonStartEnabling();
}
