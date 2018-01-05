#include "symptom.h"
#include <QtAlgorithms>


symptom::symptom(QMap<QString, evidence*> evidlist, QString name, int col): evidenceList(evidlist), name(name),column(col)
{

}

QMap<QString, evidence*> symptom::getEvidencelist()
{
    return evidenceList;
}

int symptom::getEvidencelistSize()
{
    return evidenceList.size();
}

QString symptom::getName()
{
    return name;
}

QString symptom::getName2() const
{
     return name;
}

void symptom::setEvidencelist(QMap<QString, evidence*> list)
{
    evidenceList = list;
}

bool symptom::sortEvidenceList()
{




//      vector<evidence> sortedList;

//    evidence first = evidenceList[0];

//     for(unsigned int k =1; k< evidenceList.size();k++){

//        if(first.setop() < evidenceList[k].){


//        }else{

//        }

//    }
//      QVector<int> operators;
//      for(unsigned int k=0;k< evidenceList.size();k++ ){
//            operators.push_back(evidenceList[k].getop());
//      }

//      qSort(operators.begin(),operators.end);
//      for(unsigned int k =0; k<operators;k++){

//      }




return true;

}

int symptom::getColumn()
{
    return column;
}

