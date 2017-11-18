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

    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    date_start = ui->date_start->date();
    date_end = ui->date_end->date();
    time_start = ui->time_start->time();
    time_end = ui->time_end->time();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushRefresh_clicked()
{
    QString db_name = ui->db_name->text(),
            db_host = ui->db_host->text(),
            dB_user = ui->db_user->text(),
            db_passw = ui->db_passw->text();

    QSettings settings(connectionSettings, QSettings::IniFormat);
    settings.setValue("database", db_name);
    settings.setValue("connecthost", db_host);
    settings.setValue("username", dB_user);
    settings.setValue("passwd", db_passw);
    settings.sync();

    if(dataBase.openConnectie(db_host, db_name, dB_user, db_passw))
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

        this->new_log_entry("\nPlease select a room and then click on 'start'");

        if(dataBase.sluitConnectie()) {
            this->new_log_entry("Connection is closed");
        }
        else
        {
            this->new_log_entry("Connection not closed");
        }
    }
    else
    {
        this->new_log_entry(dataBase.lastError());
        this->new_log_entry("Niet gelukt");
    }

    this->new_log_entry("--------------------");
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

///// (KLEINE) ON BUTTON CLICKED FUNCTIES /////

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
