#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(!this->importCSV())
    {
        qDebug() << "WROOONG";
        return;
    }
    if(!this->makeMap())
    {
        qDebug() << "WROOONG V2";
        return;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::makeMap()
{
    int descrPos, flowPos;
    for(unsigned int i = 0; i < headerData[0].size(); i++)
    {
        if(headerData[0][i].contains("class_Description", Qt::CaseInsensitive)) {
            descrPos = i;
        }
        else if(headerData[0][i].contains("value", Qt::CaseSensitive)) {
            flowPos = i;
        }
    }
    qDebug() << descrPos << flowPos;

    for(unsigned int i = 0; i < allData.size(); i++)
    {
        HighAirflow.insert(std::pair<QString, unsigned int>(allData[i][descrPos], allData[i][flowPos].toUInt()));
    }
    for(auto it = HighAirflow.cbegin(); it != HighAirflow.cend(); ++it)
    {
        if(it->first.contains("2.008", Qt::CaseInsensitive)) {
            qDebug() << it->first << " " << it->second<< "\n";
        }
    }

    return true;
}

bool MainWindow::importCSV()
{
    QString delimiter,
            filename = QFileDialog::getOpenFileName(0, QObject::tr("Selecteer een .csv bestand."), ("C://"), QObject::tr(".csv files (*.csv)"));
    int rowbegin = 1, colbegin = 1;


    QFile importedCSV(filename);
    QStringList rowOfData;
    QStringList rowData;
    QString data;

    if (importedCSV.open(QFile::ReadOnly)){
        data = importedCSV.readAll();
        rowOfData = data.split("\n", QString::SkipEmptyParts);
        importedCSV.close();
    } else{
        std::cout << "Could not open file" << std::endl;
        return false;
    }

    QString headerRow = rowOfData.at(0);
    std::size_t delimPos = headerRow.toStdString().find_first_of(",;\t");
    delimiter = headerRow.at(delimPos);
    for ( int x = 0; x < rowOfData.size(); x++){
        rowData = rowOfData.at(x).split(delimiter);
        std::vector<QString> row;

        for ( int y = 0; y < rowData.size(); y++){
            QString rowString = rowData[y];
            if(rowString.compare("\r")) {
              row.push_back(rowData[y]);
            }
        }
        if(x<rowbegin){
           headerData.push_back(row);
           std::cout << headerData.size() << std::endl;
        } else {
           allData.push_back(row);
        }
    }
    qDebug() << allData.size();
    return true;
}
