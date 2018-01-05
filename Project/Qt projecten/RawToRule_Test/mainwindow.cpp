#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dataLogger = new Logger(0, "log_Main.txt");
    converter = new convertData;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dataLogger;
    delete converter;
}

void MainWindow::on_pushButton_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Select a RULE .csv file"), "D://HHS TI/Jaar 4/Minor Data Science/Data/Test6_SMILE", ".csv files (*.csv))"),
            delim;
    QFile importedCSV(filename);

    QStringList rowOfData,
                rowData;
    QString data;
    std::vector< std::vector<QString> > allData,
                                        newColumn;
    std::vector< std::vector<float> > newData,
                                      newRuleData;
    headerData.clear();
    sensorData.clear();
    timeData.clear();
    totalData.clear();

    if (importedCSV.open(QFile::ReadOnly)){
        data = importedCSV.readAll();
        rowOfData = data.split("\n", QString::SkipEmptyParts);
        importedCSV.close();
    }else{
        dataLogger->write("Could not open CSV!!!");
    }
    QString headerRow = rowOfData.at(0);
    std::size_t delimPos = headerRow.toStdString().find_first_of(",;\t");
    delim = headerRow.at(delimPos);

    for ( int x = 0; x < rowOfData.size(); x++){
        //rowData = rowOfData.at(x).split(QRegularExpression("[*,;\t]"));
        rowData = rowOfData.at(x).split(delim);
        std::vector<QString> row;
          //int k=0;
        for ( int y = 0; y < rowData.size(); y++){
            QString rowString =rowData[y];
            rowString.remove(QRegExp("[\\n\\t\\r]"));
            row.push_back(rowString);
        }
        if(x<1){
           headerData.push_back(row);
        } else{
           allData.push_back(row);
        }
    }

    if(this->switchRowAndCols(allData,true,2)){
        if(!this->convertToFloat()){
           dataLogger->write("Could not convert to float!!!");
        }
    }else{
        dataLogger->write("Could not switch rows and cols!!!");
    }

    dataLogger->write(QString("sensorData.size(): " + QString::number(sensorData.size())));
    dataLogger->write(QString("sensorData[0].size(): " + QString::number(sensorData[0].size())));

    newData = this->transposeData(sensorData);
    dataLogger->write(QString("newData.size(): " + QString::number(newData.size())));
    dataLogger->write(QString("newData[0].size(): " + QString::number(newData[0].size())));

    QMessageBox::StandardButton QsaveRawCSV;
    QsaveRawCSV = QMessageBox::question(this, "Save new raw CSV", "Do you want to save the new made raw values?",
                                         QMessageBox::Save | QMessageBox::Cancel);
    if(QsaveRawCSV == QMessageBox::Save)
    {
        QString filename2 = QFileDialog::getSaveFileName(0, QObject::tr("Select a NEW NORMAL .csv file"), ("D://HHS TI/Jaar 4/Minor Data Science/Data/Test6_SMILE"), QObject::tr(".csv files (*.csv)"));
        if(!(this->exportFile(newData, filename2, QString(";"))))
        {
            dataLogger->write("Could not export!!!");
        }
    }


    newColumn.push_back({"High_flow", "Low_flow", "Flow_frozen", "Flow_while_PIR_0", "High_CO2", "Low_CO2", "CO2_frozen", "CO2_neighbours_non_identical", "PIR_NaN"});
    newColumn.push_back({"1, 2, 3, 4, 5, 6, 7, 8, 9"});

    newRuleData = converter->convertDataDatabase(newData, headerData[0], newColumn, 60);

    newColumn[0].insert(newColumn[0].begin(), QString("Tijd"));
    newColumn[0].insert(newColumn[0].begin(), QString("Datum en tijd (uur)"));
    headerData.clear();
    headerData.push_back(newColumn[0]);

    qDebug() << newRuleData.size() << newRuleData[0].size();
    newRuleData = this->transposeData(newRuleData);
    qDebug() << newRuleData.size() << newRuleData[0].size();


    QMessageBox::StandardButton QsaveRuleCSV;
    QsaveRuleCSV = QMessageBox::question(this, "Save new rule CSV", "Do you want to save the new made rule values?",
                                         QMessageBox::Save | QMessageBox::Cancel);
    if(QsaveRuleCSV == QMessageBox::Save)
    {
        QString filename3 = QFileDialog::getSaveFileName(0, QObject::tr("Select a NEW RULE .csv file"), ("D://HHS TI/Jaar 4/Minor Data Science/Data/Test6_SMILE"), QObject::tr(".csv files (*.csv)"));
        if(!(this->exportFile(newRuleData, filename3, QString(";"))))
        {
            dataLogger->write("Could not export!!!");
        }
    }

    this->close();
}

bool MainWindow::switchRowAndCols(std::vector< std::vector<QString> > &strdata, bool timeavailble, int colbegin)
{

    for(unsigned int i=0; i < strdata[0].size();i++){
        std::vector<QString> temp;
        for(unsigned int k=0;k<strdata.size();k++){
            temp.push_back(strdata[k][i]);
        }
        if(timeavailble && i<colbegin){
            timeData.push_back(temp);
        }else{
            totalData.push_back(temp);
        }
    }
    return true;
}

bool MainWindow::convertToFloat()
{
    for(unsigned int i=0; i < totalData.size(); i++){
       std::vector<float> temp;
       for(unsigned int k=0; k < totalData[i].size(); k++){
          //temp.push_back(totalData[i][k].toFloat());
          temp.push_back(std::atof(totalData[i][k].toStdString().c_str()));
          //temp.push_back(std::atof(totalData[i][k].toLocal8Bit()));
       }
       //dataLogger->write(QString::number(temp.size()));
       sensorData.push_back(temp);
    }
    return true;
}

bool MainWindow::exportFile(std::vector< std::vector<float> > data, QString filename, QString delimiter)
{
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        //unsigned int i = 0, j = 0;
        //dataLogger->write(QString::number(data[i].size()));
        /*for(unsigned int i=0; i<data[i].size(); i++){
            //vector<QString> row = data[i];
            for (unsigned int j = 0; j < data.size(); j++) { // Was row.size()
                if(j < (data.size()-1)) {
                    stream << data[j][i] <<  delimiter;
                } else {
                    stream << data[j][i];
                }
            }
            stream << endl;
        }*/

        for(unsigned int i=0; i<headerData[0].size(); i++)
        {
            if(i < (headerData[0].size()-1)) {
                stream << headerData[0][i] <<  delimiter;
            } else {
                stream << headerData[0][i];
            }
        }
        stream << endl;

        for(unsigned int i=0; i<data.size(); i++){
            //std::vector<float> row = data[i];
            for (unsigned int j = 0; j < data[i].size(); j++) {
                if(j == 0) {
                    stream << timeData[0][i] << delimiter << timeData[1][i] << delimiter;
                }

                if(j < (data[i].size()-1)) {
                    stream << data[i][j] <<  delimiter;
                }
                else {
                    stream << data[i][j];
                }
            }
            stream << endl;
        }
    }
    else {
        return false;
    }
    file.close();

    return true;
}

template<class T> std::vector< std::vector<T> > MainWindow::transposeData(std::vector< std::vector<T> > oldData)
{
    std::vector< std::vector<T> > newDataTrans(oldData[0].size(), std::vector<T>(oldData.size()));

    for (size_t i = 0; i < oldData.size(); ++i)
        for (size_t j = 0; j < oldData[0].size(); ++j)
            newDataTrans[j][i] = oldData[i][j];

    return newDataTrans;
}
