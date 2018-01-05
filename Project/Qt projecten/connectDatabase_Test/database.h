#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QtDebug>
#include <iostream>

//class MainWindow;

class DataBase
{
public:
    DataBase();
    bool openConnectie(QString , QString , QString , QString );
    bool sluitConnectie();
    QString lastError();
    //int getConnID();

private:
    QSqlDatabase dataBase;
    //bool openDB = false;
    int connID = 0;
};

#endif // DATABASE_H
