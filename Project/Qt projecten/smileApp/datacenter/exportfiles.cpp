#include "exportfiles.h"

Exportfiles::Exportfiles()
{
    //message = new QMessageBox();
}

Exportfiles::~Exportfiles()
{
    //delete message;
}

bool Exportfiles::saveEvidenceCsv(QMap<QString, QVector<int> > list)
{
    QString delimiter = ",";
    QFile file("smileLab/csvofanalyzedata.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream(&file);

     // eingelijk moet je kijken als alle data even zijn
       int total = list.value(0).size();
       for(int k=0; k < total;k++){
        QMap<QString, QVector<int> >::iterator i;
        QString rowdata="";
            for (i = list.begin(); i != list.end(); ++i){

                stream << i.value().at(k) << delimiter;
            }
           stream << "\n";
           rowdata.clear();
        }
    }
    file.close();
 return true;


}

bool Exportfiles::saveEvidenceCsvlist(QMap<QString, QVector<int> > &data)
{
    QString delimiter =",";
    QFile file("smileLab/csvofanalyzedata.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream(&file);

     // eingelijk moet je kijken als alle data even zijn
       int total = data.first().size();
       for(int k=0; k < total;k++){
        QMap<QString, QVector<int> >::iterator i;
        QString rowdata="";
            for (i = data.begin(); i != data.end(); ++i){

                stream << i.value().at(k) << delimiter;
            }
           stream << "\n";
           rowdata.clear();
        }
    }
    file.close();
 return true;
}

bool Exportfiles::savePrepDataCsv( vector<vector<QString> > prep, QMap<QString, symptom *> MapOfSymps)
{
    QString delimiter = ",";
    QFile file("smileLab/csvofanalyzedata.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        // eingelijk moet je kijken als alle data even zijn
        int total = prep[0].size();

        //message->information(0, "Size", QString(QString::number(prep[0].size()) + " " + QString::number(MapOfSymps.size())));

        for(int k=0; k < total;k++)
        {
            QMap<QString, symptom*>::iterator i;
            //QString rowdata="";
            for (i = MapOfSymps.begin(); i != MapOfSymps.end(); ++i)
            {
                stream << prep[i.value()->getColumn()][k] << delimiter;
                //rowdata = rowdata + prep[i.value()->getColumn()][k] + delimiter;

                //stream << i.value()->getColumn()<<delimiter<<endl;
            }

            stream << "\n";
            //rowdata.clear();
        }


    }
    file.close();
    return true;

}

bool Exportfiles::savePrepDataCsv(vector< vector<float> > prep, QMap<QString, symptom *> MapOfSymps, unsigned int timeCols)
{
    QString delimiter = ",";
    QFile file("smileLab/csvofanalyzedata.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        // eingelijk moet je kijken als alle data even zijn
        //int total = prep[0].size();
        //message->information(0, "Size", QString(QString::number(prep[0].size()) + " " + QString::number(MapOfSymps.size())));
        for(unsigned int k=0; k < prep[0].size()/*total*/;k++){
            QMap<QString,symptom*>::iterator i;
            QString rowdata="";
            for (i = MapOfSymps.begin(); i != MapOfSymps.end(); i++)
            {
                stream << prep[(i.value()->getColumn() - timeCols)][k] << delimiter;
                //message->information(0, "VALUES", QString::number(prep[i.value()->getColumn()][k]));
                //rowdata = rowdata + prep[i.value()->getColumn()][k] + delimiter;

                //stream << i.value()->getColumn()<<delimiter<<endl;
            }

            stream << "\n";
            rowdata.clear();
        }


    }
    file.close();
    return true;

}


bool Exportfiles::saveSymptomsCSV(QMap<QString, symptom *> MapOfSymps)
{
    QString delimiter =",";
    QFile file("smileLab/csvofsymps.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        QMap<QString,symptom*>::iterator i;
        for (i = MapOfSymps.begin(); i != MapOfSymps.end(); ++i){
           stream << i.value()->getName()<<delimiter<<endl;
        }
    }
    file.close();
 return true;
}

bool Exportfiles::saveResultNodeCSV(QMap<QString, vector<QString> > MapOfResults)
{
    QString delimiter =",";
    QFile file("smileLab/csvofresult.csv");
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        QMap<QString,vector<QString> >::iterator i;
        for (i = MapOfResults.begin(); i != MapOfResults.end(); ++i){
           stream << i.key()<<delimiter<<endl;
        }
    }
    file.close();

    return true;
}

bool Exportfiles::saveSmileresultdata(QString filename, vector<vector<QString> > &data)
{
    QString delimiter =",";
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        for(unsigned int i=0; i<data.size();i++){
            vector<QString> row = data[i];
                for (unsigned int j = 0; j < row.size(); j++) {
                    stream << data[i][j] <<  delimiter;
                }
                stream << endl;
        }
    }
    file.close();
 return true;
}

bool Exportfiles::saveDataBaseCsv(vector< vector<QString> > data, QString filename, QString delimiter)
{
    QFile file( filename );

    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        for(unsigned int i=0; i<data.size(); i++){
            //vector<QString> row = data[i];
                for (unsigned int j = 0; j < data[i].size(); j++) { // Was row.size()
                    if(j < (data[i].size()-1)) {
                        stream << data[i][j] <<  delimiter;
                    } else {
                        stream << data[i][j];
                    }
                    //stream << data[i][j] <<  delimiter;
                }
                stream << endl;
        }
    }
    else {
        return false;
    }
    file.close();

    return true;
}

bool Exportfiles::saveDataBaseCsv(vector< vector<float> > data, vector< vector<QString> > headerData, vector< vector<QString> > timeData, QString filename, QString delimiter)
{
    QFile file( filename );

    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );

        for(unsigned int i=0; i<headerData.size(); i++)
        {
            for(unsigned int j=0; j<headerData[i].size(); j++)
            {
                if(j < (headerData[i].size()-1)) {
                    stream << headerData[i][j] <<  delimiter;
                } else {
                    stream << headerData[i][j];
                }
            }
            stream << endl;
        }

        for(unsigned int i=0; i<data.size(); i++)
        {
            for (unsigned int j = 0; j < data[i].size(); j++)
            {
                if(j == 0)
                {
                    if(timeData.size() > 1) {
                        for(unsigned int k=0; k<timeData.size(); k++) {
                            stream << timeData[k][i] << delimiter;
                        }
                    } else {
                        stream << timeData[0][i] << delimiter;
                    }
                }

                if(j < (data[i].size()-1)) {
                    stream << data[i][j] <<  delimiter;
                } else {
                    stream << data[i][j];
                }
                //stream << data[i][j] <<  delimiter;
            }
            stream << endl;
        }
    }
    else {
        return false;
    }
    file.close();

    return true;
}
