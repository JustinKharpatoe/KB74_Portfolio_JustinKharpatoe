#ifndef GENERATEEVIDENCE_H
#define GENERATEEVIDENCE_H

#include <QString>
#include <QVector>
#include <QMap>
#include <iostream>
#include "nodes/evidence.h"
#include "nodes/evidencecomparators.h"
#include "nodes/symptom.h"
#include <algorithm>


using namespace std;

class generateEvidence
{
public:
    generateEvidence();
    QMap<QString, QVector<int> > calculateEvidence(vector<vector<float> > data, QMap<QString, symptom *> SympsNodes );
    QVector<evidence*> sortEvidenceInSymps(symptom *sympsNodes);
    int getCalculatedIndex(vector<vector<float> > &data,QVector<evidence*> list,int row, int col);
    bool calcConstant(vector<vector<float> > &data, int row, int col);
    QMap<QString,QVector<int> > getGeneratedEvidenceList();
    // QMap<QString,QVector<int> > evidenceList;


private:
   QMap<QString,QVector<int> > evidenceList;
   QVector<QVector<int> > resultList;




};

#endif // GENERATEEVIDENCE_H
