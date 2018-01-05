#include "database.h"
//#include "mainwindow.h"

DataBase::DataBase() { }

bool DataBase::openConnectie(QString hostname, QString database, QString username, QString passwd)
{
    //passwd = geheim
    dataBase = QSqlDatabase::addDatabase("QPSQL");
    dataBase.setHostName(hostname);
    dataBase.setDatabaseName(database);
    dataBase.setPassword(passwd);
    dataBase.setUserName(username);
    //QSqlQuery pid;

    if(!dataBase.isOpen())
    {
        if(dataBase.open())
        {
            //openDB = true;
            return true;
        }
        else if(dataBase.isOpenError())
        {
            //openDB = false;
            qDebug() << dataBase.lastError();
            //MainWindow::new_log_entry(dataBase.lastError().databaseText());
            return false;
        }
    }

    return false;
}

bool DataBase::sluitConnectie()
{
    if(dataBase.isOpen())
    {
        QString connection;
        connection = dataBase.connectionName();
        dataBase.close();
        dataBase = QSqlDatabase();
        dataBase.removeDatabase(connection);
        return true;
    }

    return false;
}

QString DataBase::lastError()
{
    return dataBase.lastError().text();
}

/*int DataBase::getConnID()
{
    return connID;
}*/
