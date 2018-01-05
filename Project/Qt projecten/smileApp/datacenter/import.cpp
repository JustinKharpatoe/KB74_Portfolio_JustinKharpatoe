#include "import.h"



import::import()
{
    dataLogger = new Logger(0, "LogImport.txt");
}

bool import::readSmileFile(QString path, QMap<QString, vector<QString> > &readData){

    QDomDocument xmlSITUATIONS;
    QFile f(path);
//    QDir folder;
//    if(!folder.exists("smileLab")){
//       folder.mkdir("smileLab");
//    }

    QFile old("smileLab/hhsnetwork.xdsl");
    if(old.exists()){
        old.remove();
        cout<<"it exists"<<endl;
            }
    f.copy("smileLab/hhsnetwork.xdsl");
        cout<<"copied"<<endl;
    if (!f.open(QIODevice::ReadOnly )){
        cout << "Error while loading file" <<endl;
        return false;
    }else{
        xmlSITUATIONS.setContent(&f);
        f.close();
        QDomElement root=xmlSITUATIONS.documentElement();
        QDomElement Component=root.firstChild().toElement();
        QDomElement cpt = Component.firstChild().toElement();
            if ((Component.tagName()=="nodes")&&(cpt.tagName() == "cpt")){
                while(!cpt.isNull()){

                    QString name= cpt.attribute("id");
                    QDomElement state = cpt.firstChild().toElement();
                        while(!state.isNull()){
                             if(state.tagName()=="state"){
                                readData[name].push_back(state.attribute("id"));
                             }
                              state = state.nextSibling().toElement();
                        }
                   cpt=cpt.nextSibling().toElement();
                }
             }else{
                return false;
            }


            return true;
    }




}

bool import::readCsvFile(QString path, QString delimiter, int rowbegin, int colbegin, bool timeAvialble, bool rawOrprep)
{

    QFile importedCSV(path);
    QStringList rowOfData;
    QStringList rowData;
    QString data;
    vector<vector<QString> > allData;
    headerData.clear();
    sensorData.clear();
    timeData.clear();
    totalData.clear();


    if (importedCSV.open(QFile::ReadOnly)){
        data = importedCSV.readAll();
        rowOfData = data.split("\n", QString::SkipEmptyParts);
        importedCSV.close();
    }else{
        return false;
    }
    QString headerRow = rowOfData.at(0);
    std::size_t delimPos = headerRow.toStdString().find_first_of(",;\t");
    delimiter = headerRow.at(delimPos);

    for ( int x = 0; x < rowOfData.size(); x++){
        rowData = rowOfData.at(x).split(delimiter);
        //rowData = rowOfData.at(x).split(QRegularExpression("[*,;\t]"));
        vector<QString> row;
          int k=0;
        for ( int y = 0; y < rowData.size(); y++){
            QString rowString =rowData[y];
            if(rowString.compare("\r")){
              row.push_back(rowData[y]);
            }
        }
        if(x<rowbegin){
           headerData.push_back(row);
        } else{
           allData.push_back(row);
        }
    }
    //allData.erase(allData.end()-1);

//    for(unsigned int i = 0; i < allData[0].size(); i++)
//        dataLogger->write(QString(allData[0][i]));

    if(switchRowAndCols(allData,timeAvialble,colbegin)){
       if(!rawOrprep){
        if(!convertToFloat()){
           return false;
        }
       }
    }else{
        return false;
    }

    return true;
}

bool import::readCsvDatabase(vector<vector<QString> > data, int rowbegin, int colbegin, bool timeAvailable)
{
    headerData.clear();
    sensorData.clear();
    timeData.clear();
    totalData.clear();

    std::vector<std::vector<QString>> allData;

    for(unsigned int i = 0; i < data.size(); i++)
    {
        if(i < rowbegin) {
            headerData.push_back(data[i]);
        }
        else {
            allData.push_back(data[i]);
        }
    }

    if(switchRowAndCols(allData, timeAvailable, colbegin)) {
       if(!convertToFloat()){
           return false;
       }
    } else {
        return false;
    }

    return true;
}

bool import::readXmlFile(QString path,QMap<QString,symptom*> &importSymps)
{

    //symptom sympNode = new symptom();

    QDomDocument xmlSITUATIONS;
    QFile f(path);

    if (!f.open(QIODevice::ReadOnly )){
        cout << "Error while loading file" <<endl;
        return false;
    }else{
        xmlSITUATIONS.setContent(&f);
        f.close();
        QDomElement root=xmlSITUATIONS.documentElement();
       // QDomElement Component=root.firstChild().toElement();
        QDomElement cpt = root.firstChild().toElement();
        QString eerste = root.tagName();
        QString tweede = cpt.tagName();
            if ((root.tagName()=="smilenodes")&&(cpt.tagName() == "symptom")){
                while(!cpt.isNull()){
                    QString name= cpt.attribute("name");
                    QMap<QString,evidence*> evidmapList;
                    QDomElement state = cpt.firstChild().toElement();

                        while(!state.isNull()){
                             if(state.tagName()=="evidence"){
                                 if(state.attribute("operationtype")=="5"){
                                    QVector<float> values;
                                    values.push_back(state.attribute("value1").toFloat());
                                    values.push_back(state.attribute("value2").toFloat());
                                    evidence *xmlEvidence=new evidence(state.attribute("name"),state.attribute("smileindex").toInt() );
                                    xmlEvidence->setvalues(values);
                                    xmlEvidence->setop(state.attribute("operationtype").toInt());
                                    evidmapList.insert(state.attribute("name"),xmlEvidence);
                                 }else{
                                     QVector<float> values;
                                     values.push_back(state.attribute("value1").toFloat());
                                     evidence *xmlEvidence=new evidence(state.attribute("name"),state.attribute("smileindex").toInt() );
                                     xmlEvidence->setvalues(values);
                                     xmlEvidence->setop(state.attribute("operationtype").toInt());
                                     evidmapList.insert(state.attribute("name"),xmlEvidence);

                                 }




                             }
                              state = state.nextSibling().toElement();
                        }
                     importSymps.insert(name, new symptom(evidmapList,name,0));
                     evidmapList.clear();
                   cpt=cpt.nextSibling().toElement();
                }
             }else{
                return false;
            }
            return true;
    }

    return true;
}

bool import::readSmileResultData(QString path, QString delimiter, vector<vector<QString> > &data)
{
    QFile importedCSV(path);
    QStringList rowOfData;
    QStringList rowData;
    QString dataname;

    if (importedCSV.open(QFile::ReadOnly)){
        dataname = importedCSV.readAll();
        rowOfData = dataname.split("\n");
        importedCSV.close();
    }else{
        return false;
    }
    for ( int x = 0; x < rowOfData.size(); x++){
        //rowData = rowOfData.at(x).split(delimiter);
        rowData = rowOfData.at(x).split(QRegularExpression("[*,;\t]"));
        vector<QString> row;
        for ( int y = 0; y < rowData.size()-1; y++){
            row.push_back(rowData[y]);
        }
           data.push_back(row);

    }
    //data.erase(data.end()-1);


    return true;



}

bool import::readXmlSortedNodes(QString path, QMap<QString, int> &symps, QMap<QString, int> &results)
{
    QDomDocument xmlSITUATIONS;
    QFile f(path);

    if (!f.open(QIODevice::ReadOnly )){
        cout << "Error while loading file" <<endl;
        return false;
    }else{
        xmlSITUATIONS.setContent(&f);
        f.close();
        QDomElement root=xmlSITUATIONS.documentElement();
        QDomElement cpt = root.firstChild().toElement();
        if ((root.tagName()=="smilenodes")){

            while(!cpt.isNull()){
                if(cpt.tagName() == "symptomnodes"){
                    QDomElement state = cpt.firstChild().toElement();
                    while(!state.isNull()){
                        if(state.tagName()=="symptom"){
                            symps.insert(state.attribute("name"),state.attribute("child").toInt());
                        }
                        state = state.nextSibling().toElement();
                    }
                }
                if(cpt.tagName() == "resultnodes"){
                    QDomElement state2 = cpt.firstChild().toElement();
                    while(!state2.isNull()){
                        if(state2.tagName()=="result"){
                            results.insert(state2.attribute("name"),state2.attribute("child").toInt());
                        }
                        state2 = state2.nextSibling().toElement();
                    }
                }
                cpt=cpt.nextSibling().toElement();
            }
        }else{
            return false;
        }
        return true;
    }

    return true;

}

bool import::readXmllinkedNodes(QString path, QMap<QString,QString> &linkednodes)
{
    QDomDocument xmlSITUATIONS;
    QFile f(path);
    if (!f.open(QIODevice::ReadOnly )){
        cout << "Error while loading file" <<endl;
        return false;
    }else{
        xmlSITUATIONS.setContent(&f);
        f.close();
        QDomElement root=xmlSITUATIONS.documentElement();
        QDomElement cpt = root.firstChild().toElement();
        if ((root.tagName()=="smilenodes")){
            while(!cpt.isNull()){
                if(cpt.tagName() == "symptomnodes"){
                    QDomElement state = cpt.firstChild().toElement();
                    while(!state.isNull()){
                        if(state.tagName()=="symptom"){
                            linkednodes.insert(state.attribute("name"),state.attribute("linktocol"));
                        }
                        state = state.nextSibling().toElement();
                    }
                }
                cpt=cpt.nextSibling().toElement();
            }
        }else{
            return false;
        }
        return true;
    }

    return true;



}





vector<vector<float> > import::getSensorData()
{
    return sensorData;
}

vector<vector<QString> > import::getHeaderData()
{
    return headerData;
}

vector<vector<QString> > import::getTimeData()
{
    return timeData;
}

vector<vector<QString> > import::getTotalData()
{

    return totalData;
}



bool import::switchRowAndCols(vector<vector<QString> > &strdata, bool timeavailble, int colbegin)
{

    for(unsigned int i=0; i < strdata[0].size();i++){
        vector<QString> temp;
        for(unsigned int k=0;k<strdata.size();k++){
            temp.push_back(strdata[k][i]);
        }
        if(timeavailble && i<colbegin){
            timeData.push_back(temp);
        }else{
            totalData.push_back(temp);
        }
    }
    return true;
}

bool import::convertToFloat()
{
    for(unsigned int i=0; i < totalData.size(); i++){
       vector<float> temp;
       for(unsigned int k=0; k < totalData[i].size(); k++){
          //temp.push_back(totalData[i][k].toFloat());
          temp.push_back(std::atof(totalData[i][k].toStdString().c_str()));
       }
       sensorData.push_back(temp);
    }
    return true;
}

void import::setSensorData(vector<vector<float> > sensor)
{
    sensorData = sensor;
}

void import::setHeaderData(vector<vector<QString> > headers)
{
    headerData = headers;
}

void import::setTimeData(vector<vector<QString> > time)
{
    timeData = time;
}

void import::setTotalData(vector<vector<QString> > total)
{
    totalData = total;
}
