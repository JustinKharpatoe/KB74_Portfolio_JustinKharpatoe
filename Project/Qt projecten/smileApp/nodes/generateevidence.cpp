#include "generateevidence.h"

generateEvidence::generateEvidence()
{

}

QMap<QString,QVector<int> > generateEvidence::calculateEvidence(vector<vector<float> > data, QMap<QString, symptom *> SympsNodes)
{
        QMap<QString,QVector<int> > list;
        QMap<QString,symptom*>::iterator i;
        for(i = SympsNodes.begin(); i != SympsNodes.end(); i++)
        {
           QVector<evidence *> eviList;
           QVector<int> result;
           eviList= sortEvidenceInSymps(i.value());
           for(unsigned int d =0; d < data[i.value()->getColumn()].size() ;d++)
           {
               result.push_back(getCalculatedIndex(data,eviList,i.value()->getColumn(),d));
           }
           //QString name = i.value()->getName();
           list.insert(i.value()->getName(),result);
            //list.push_back(result);
        }

   return list;
}

QVector<evidence *> generateEvidence::sortEvidenceInSymps(symptom* sympsNodes)
{
    // Sort Operators values high prio to low prio
    QVector<evidence *> sortedList;
    QMap<QString,evidence*> sympsEvidence = sympsNodes->getEvidencelist();
    QMap<QString,evidence*>::iterator i;
    for(i = sympsEvidence.begin(); i != sympsEvidence.end(); ++i){
        sortedList.push_back(i.value());
    }
     std::sort(sortedList.begin(),sortedList.end(),ComparatorByOperator());

    return sortedList;
}

int generateEvidence::getCalculatedIndex(vector<vector<float> > &data,QVector<evidence*> list,int row, int col)
{
    for(int e=0; e < list.size(); e++){
     int state = list[e]->getop();
        switch (state)
              {
              case 0:// Constant
                   if(calcConstant(data,row,col)){
                      return list[e]->getIndex();
                   }
                   break;
              case 1://niet constant
                    if(!calcConstant(data,row,col)){
                       return list[e]->getIndex();
                    }
                    break;
              case 2: //gelijk aan
                    if(data[row][col] == list[e]->getOnevalue(0)){
                       return list[e]->getIndex();
                    }
                    break;
              case 3:// min
                     if(data[row][col] <= list[e]->getOnevalue(0)){
                        return list[e]->getIndex();
                     }
                     break;
             case 4://max
                   if(data[row][col] >= list[e]->getOnevalue(0)){

                     return list[e]->getIndex();
                   }
                   break;
             case 5: //between
                   if((data[row][col] > list[e]->getOnevalue(0)) && (data[row][col] < list[e]->getOnevalue(1))){
                     return list[e]->getIndex();
                   }
                   break;
              }

        // negatieve waarde geven als het niet voor komt

    }

}

bool generateEvidence::calcConstant(vector<vector<float> > &data, int row, int col)
{

    int begin;
    int end;
    // boven kan
    if(col<5){
        begin =0;

    }else{
        begin = col-5;
    }

    if((col+5)>= data[row].size()){

        end= data[row].size();
    }else{
        end= col+5;
    }

    float sum=0;
    int counter=0;
    for(int k=begin; k<end;k++){
        sum = sum + data[row][k];
        counter++;
    }

    float avg = sum/counter;
    float btwbegin = data[row][col]-0.5;
    float btwend=data[row][col]+0.5;

    if((avg>btwbegin)&&(avg<btwend)){
        return true;
    }else
        return false;

}

QMap<QString, QVector<int> > generateEvidence::getGeneratedEvidenceList()
{
    return evidenceList;
}
