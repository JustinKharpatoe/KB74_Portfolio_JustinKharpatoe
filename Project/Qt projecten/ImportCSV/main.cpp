#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QRegularExpression>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "D://HHS TI/Jaar 4/Minor Data Science/Data/Test5_RuleVentilation/D2008_20142015_hour_VENTILATIONRULE.csv",
            delimiter = ",";
    int rowbegin = 1, colbegin = 1;
    bool timeAvialble = true, rawOrprep = true;

    QFile importedCSV(path);
    QStringList rowOfData;
    QStringList rowData;
    QString data;
    std::vector<std::vector<QString>> allData, timeData, totalData, headerData;
    std::vector<std::vector<float> > sensorData;

    if (importedCSV.open(QFile::ReadOnly)){
        data = importedCSV.readAll();
        rowOfData = data.split("\n", QString::SkipEmptyParts);
        std::cout << rowOfData.size() << std::endl;
        //std::cout << rowOfData.at(0).toStdString() << std::endl;
        //std::cout << rowOfData.at(rowOfData.length()-1).toStdString() << std::endl;
        importedCSV.close();
    } else{
        std::cout << "Could not open file" << std::endl;
    }


    std::cout << rowData.size() << std::endl;
    for ( int x = 0; x < rowOfData.size(); x++){
        //rowData = rowOfData.at(x).split(delimiter);
        rowData = rowOfData.at(x).split(QRegularExpression("[*,;\t]"));

        std::vector<QString> row;
        for ( int y = 0; y < rowData.size(); y++){
            QString rowString = rowData[y];
            if(rowString.compare("\r")){
              row.push_back(rowData[y]);
            }
        }
        if(x<rowbegin){
           headerData.push_back(row);
           std::cout << headerData.size() << std::endl;
        } else{
           allData.push_back(row);
        }
    }
    qDebug() << allData[0][0];
    qDebug() << allData[allData.size()-1][0];
    qDebug() << allData[allData.size()-1][1];

    //allData.erase(allData.end()-1);
    std::cout << allData.size() << std::endl;
    qDebug() << allData[allData.size()-1][0];
    qDebug() << allData[allData.size()-1][1];


    return a.exec();
}
