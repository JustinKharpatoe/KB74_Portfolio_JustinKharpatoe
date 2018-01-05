#include "exportcsv.h"

exportCSV::exportCSV(){
}

void exportCSV::prepData(vector<vector<QString> > newData){
    data = newData;
}
void exportCSV::prepDataInt(vector<vector<int> > newData){
    dataint = newData;
}

void exportCSV::saveCSV(QString filename, QString delimiter){
    QFile file( filename );
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
    data.clear();
}

void exportCSV::saveCSVInt(QString filename, QString delimiter)
{
    QFile file( filename );
    if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
        QTextStream stream( &file );
        for (unsigned int j = 0; j < dataint[0].size(); j++) {
            stream << dataint[0][j] <<  delimiter << dataint[1][j] <<  delimiter << dataint[2][j] <<  delimiter << dataint[3][j] <<  delimiter << dataint[4][j] <<  delimiter<< endl;
        }

//        for(unsigned int i=0; i< dataint.size();i++){
//            vector<int> row = dataint[i];
//                for (unsigned int j = 0; j < row.size(); j++) {
//                    stream << dataint[i][j] <<  delimiter;
//                }
//                stream << endl;
//        }
    }
    file.close();
    dataint.clear();

}
