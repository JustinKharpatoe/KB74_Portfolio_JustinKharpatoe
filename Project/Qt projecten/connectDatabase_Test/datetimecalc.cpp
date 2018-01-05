#include "datetimecalc.h"

//#include <iostream>

using namespace std;

dateTimeCalc::dateTimeCalc(){
    baseDate.setDate(1899, 12, 30);
}

QString dateTimeCalc::QTtoPOSTGRES(QDate date, QTime time){
   double tempDays = baseDate.daysTo(date);
   tempDays += (((double)(time.minute() + 60 * time.hour()) * 60 + time.second()) / 86400);

   return QString::number(tempDays, 'g', 16);
}

QDateTime dateTimeCalc::POSTGREStoQT(QString timestamp){
    double tempTimeDouble = timestamp.toDouble();
    qint64 days = (qint64)tempTimeDouble;
    qint64 dayPart = (tempTimeDouble - days) * 86400;

    QDateTime returnDate(baseDate);
    returnDate = returnDate.addDays(days);
    returnDate = returnDate.addSecs(dayPart);

    return returnDate;
}
