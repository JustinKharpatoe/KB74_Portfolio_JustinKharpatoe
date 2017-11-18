#ifndef QUERY_H
#define QUERY_H

#include <QTSQL/QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <vector>

class Query
{
public:
    Query();

    void queryToVector(QSqlQuery query, int columns);
    void locationQuery();
    void locationQueryByLevels(int pos);
    void fieldQuery(int room);
    void fieldhistoryQuery(int sensor, QString begin, QString end);

    std::vector< std::vector<QString> > returnLastResult();
    int totalRows();

    int rowCount;

private:
    std::vector< std::vector<QString> > lastResult;
};

#endif // QUERY_H
