#ifndef IMPORT_H
#define IMPORT_H
#include <stdio.h>
#include <string>
#include <QString>
#include <vector>
#include <QMap>
#include <QFile>
#include <iostream>
#include <QtXml>
#include <QString>
#include <QDir>

#include "nodes/symptom.h"
#include "nodes/evidence.h"
#include "logger.h"


using namespace std;

class import
{
public:
    import();
    bool readSmileFile(QString path, QMap<QString, vector<QString> > &readData);
    bool readCsvFile(QString path, QString delimiter, int rowbegin, int colbegin, bool timeAvialble, bool rawOrprep);
    bool readCsvDatabase(vector<vector<QString> > data, int rowbegin, int colbegin, bool timeAvailable);
    bool readXmlFile(QString path, QMap<QString, symptom *> &importSymps);
    bool readSmileResultData(QString path, QString delimiter, vector<vector<QString> > &data);
    bool readXmlSortedNodes(QString path,QMap<QString,int> &symps, QMap<QString,int> &results);
    bool readXmllinkedNodes(QString path,QMap<QString,QString> &linkednodes);


    vector<vector<float> > getSensorData();
    vector<vector<QString> > getHeaderData();
    vector<vector<QString> > getTimeData();
    vector<vector<QString> > getTotalData();

//protected:
    void setSensorData(vector<vector<float> > sensor);
    void setHeaderData(vector<vector<QString> > headers);
    void setTimeData(vector<vector<QString> > time);
    void setTotalData(vector<vector<QString> > total);

private:
    Logger *dataLogger;
    // SensorData is converted totaldata
    vector<vector<float> > sensorData;
    vector<vector<QString> > timeData;
    // totalData is without date and time
    vector<vector<QString> > totalData;
    vector<vector<QString> > headerData;

    bool switchRowAndCols(vector<vector<QString> > &strdata,bool timeavailble, int colbegin);
    bool convertToFloat();


};

#endif // IMPORT_H
