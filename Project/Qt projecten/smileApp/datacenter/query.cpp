#include "query.h"

Query::Query() { }

void Query::queryToVector(QSqlQuery query, int columns){
    //QString response;
    lastResult.clear();
    while (query.next())
    {
        std::vector<QString> row; // Create an empty row
        for(int i=0; i<=columns; i++) {
            row.push_back(query.value(i).toString());
        }
        lastResult.push_back(row);
        rowCount++;
    }
    qDebug() << rowCount << " records verwerkt";
}

void Query::locationQuery()
{
    QSqlQuery query;
    //QString response;
    rowCount = 0;
    //query.exec("SELECT id, description FROM octalixnode WHERE position='2e Verdieping' OR position='Begane grond' OR position='1e Verdieping' OR position='Kelder' ORDER BY description;");
    query.exec("SELECT id, description FROM octalixnode WHERE description LIKE 'K.%' OR description LIKE '0.%' OR description LIKE '1.%' OR description LIKE '2.%' OR description LIKE '3.%' ORDER BY description;");
    //query.exec("SELECT id, description FROM octalixnode WHERE description LIKE '1.%' ORDER BY description;");
    queryToVector(query, 1);
}

void Query::locationQueryByLevels(int pos)
{
    QSqlQuery query;
    //QString response;
    rowCount = 0;
    if(pos==0){
       query.exec("SELECT id, description FROM octalixnode WHERE description LIKE '0.%' ORDER BY description;");
    }
    if(pos==1){
         query.exec("SELECT id, description FROM octalixnode WHERE description LIKE '1.%' ORDER BY description;");
    }
    if(pos==2){
         query.exec("SELECT id, description FROM octalixnode WHERE description LIKE '2.%' ORDER BY description;");
    }

    query.exec("SELECT id, description FROM octalixnode WHERE description LIKE '1.%' ORDER BY description;");
    queryToVector(query, 1);

}

void Query::fieldQuery(int room)
{
    QSqlQuery query;
    //QString response;
    rowCount = 0;

    query.prepare("SELECT id, owner_id, type, fieldtype_id, description FROM field WHERE owner_id = :room OR owner_id IN (SELECT node_id FROM nodelocation WHERE id IN (SELECT id FROM nodelocation WHERE owner_id= :room)) ORDER BY description");
    query.bindValue(":room", room);
    query.exec();
    queryToVector(query, 4);
}

void Query::fieldhistoryQuery(int sensor, QString begin, QString end)
{
    QSqlQuery query;
    //QString response;
    rowCount = 0;

    query.prepare("SELECT timestamp, value FROM fieldhistory WHERE field_id=:sensor AND timestamp>=:begin AND timestamp<=:end ORDER BY timestamp");
    //query.prepare("SELECT id, owner_id, type, fieldtype_id, value, description FROM field WHERE owner_id = :room OR owner_id IN (SELECT node_id FROM nodelocation WHERE id IN (SELECT id FROM nodelocation WHERE owner_id= :room)) ORDER BY description");
    query.bindValue(":sensor", sensor);
    query.bindValue(":begin", begin);
    query.bindValue(":end", end);
    query.exec();
    queryToVector(query, 1);
    //cout << sensor << " sensor" << endl;
}

std::vector< std::vector<QString> > Query::returnLastResult()
{
    return lastResult;
}

int Query::totalRows()
{
    return rowCount;
}
