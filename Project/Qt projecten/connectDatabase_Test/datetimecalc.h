#ifndef DATETIMECALC_H
#define DATETIMECALC_H

#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QString>

class dateTimeCalc
{
private:
    QDate baseDate;

public:
    dateTimeCalc();
    QString QTtoPOSTGRES(QDate date, QTime time);
    QDateTime POSTGREStoQT(QString timestamp);

};

#endif // DATETIMECALC_H
