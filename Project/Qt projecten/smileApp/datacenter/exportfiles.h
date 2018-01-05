#ifndef EXPORTFILES_H
#define EXPORTFILES_H

#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <vector>
#include <iostream>
#include <QMap>
#include <iterator>

#include <QMessageBox>
#include "nodes/symptom.h"

using namespace std;

class Exportfiles
{
public:
    Exportfiles();
    ~Exportfiles();
    bool saveEvidenceCsv(QMap<QString, QVector<int> > list);
    bool saveEvidenceCsvlist(QMap<QString, QVector<int> > &data);
    bool savePrepDataCsv(vector<vector<QString> > prep, QMap<QString, symptom *> MapOfSymps);
    bool savePrepDataCsv(vector<vector<float> > prep, QMap<QString, symptom *> MapOfSymps, unsigned int timeCols);   // TOEGEVOEGD
    bool saveSymptomsCSV(QMap<QString,symptom*> MapOfSymps);
    bool saveResultNodeCSV(QMap<QString, vector<QString> > MapOfResults);
    bool saveSmileresultdata(QString filename, vector<vector<QString> > &data);

    static bool saveDataBaseCsv(vector< vector<QString> > data, QString filename, QString delimiter);
    static bool saveDataBaseCsv(vector< vector<float> > data, vector< vector<QString> > headerData, vector< vector<QString> > timeData, QString filename, QString delimiter);

private:
    //QMessageBox* message;
};

#endif // EXPORTFILES_H
