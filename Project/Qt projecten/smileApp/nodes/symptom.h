#ifndef SYMPTOM_H
#define SYMPTOM_H


#include "nodes/evidence.h"

#include <QString>
#include <QVector>
#include <QMap>

using namespace std;
class symptom
{
public:
    symptom(QMap<QString, evidence*> evidlist, QString name, int col);
    QMap<QString, evidence*> getEvidencelist();
    int getEvidencelistSize();
    QString getName();
     QString getName2() const;
    void setEvidencelist(QMap<QString, evidence *> list);
    bool sortEvidenceList();
    int getColumn();


private:
  QMap<QString, evidence*> evidenceList;
  QString name;
  int column;

};

#endif // SYMPTOM_H
