#ifndef EVIDENCE_H
#define EVIDENCE_H


#include <QString>
#include <QVector>
#include <iostream>
#include <stdexcept>
//meerdere lokalen
using namespace std;
class evidence
{
public:
    evidence(QString name, int smileIndex);
    void setName(QString nam);
    void setvalues(QVector<float>);
    void setop(int op);
    int getIndex();
    QVector<float> getvalues();
    int getValuesSize();
    float getOnevalue(int post);
    int getop();
    QString getName();
   // bool operator<(evidence & R);
   // bool operator() (evidence *lhs, evidence *rhs);

private:
    QVector<float> values;
    int oper;
    QString name;
    int index;
};

#endif // EVIDENCE_H
