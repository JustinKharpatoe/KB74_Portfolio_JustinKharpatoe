#include "convertdata.h"
#include "windowconnectdatabase.h"
#include <cmath>

convertData::convertData() {
    dataLogger = new Logger(0, "LogConvert.txt");
}

std::vector< std::vector<QString> > convertData::convertDataPres(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID){
    data[0].push_back(sensorNaam);
    data[1].push_back(sensorID);

    if(rawdata.size()<=2){
        for (unsigned int i = 2; i < data.size()-1; i++){
            data[i].push_back("0");
        }
    }
    else{
        int count=0;
        for(unsigned int n = 0; n < rawdata.size(); n++){
            if( rawdata[n][0] > data[2][1] && rawdata[n][0] < data[data.size()-1][1] ){
                count++;
            }
        }

        if(count==0)
        {
            for (unsigned int m = 2; m < data.size()-1; m++){
                data[m].push_back("0");
            }
            return data;
        }
        else
        {
            unsigned int j /*= 0*/;
            QString aanwezigheid = "0";
            //bool teGroot = false;

            for(j = 0; data[2][1] >= rawdata[j][0] && !(j>=rawdata.size()); j++)
            {
                if(rawdata[j][1]=="1"){
                    aanwezigheid="1";
                }
                else{
                    aanwezigheid="0";
                }
            }
//            while(data[2][1] >= rawdata[j][0] && teGroot==false ){
//                if(rawdata[j][1]=="1"){
//                    aanwezigheid="1";
//                }
//                else{
//                    aanwezigheid="0";
//                }
//                j++;
//                if(j>=rawdata.size()){
//                    teGroot=true;
//                }

//            }

            int k = 0;
            for (unsigned int l = 2; l < (data.size()-1); l++){
                if(data[l+1][1] <= rawdata[j][0]){
                    data[l].push_back(aanwezigheid);
                    k = l + 1;
                }
            }
            if(k==0){
                k = 2;
            }

            bool huidigeStaat = false;
            for (unsigned int m = k; m < (data.size()-1); m++){
                bool tijdslotStaat = huidigeStaat;
                bool geenData = false;

                for (unsigned int n = 0; n < rawdata.size(); n++){
                    if( data[m][1] <= rawdata[n][0] && data[m+1][1] >= rawdata[n][0] ){
                        aanwezigheid = rawdata[n][1];
                        double tijdelijk = aanwezigheid.toDouble();
                        if(tijdelijk>=0.5){
                            huidigeStaat = true;
                            tijdslotStaat = true;
                        }
                        if(tijdelijk<=0.49){
                            huidigeStaat = false;
                        }
                    }
                }
                if(data[m][1] > rawdata[rawdata.size()-1][0]){
                    geenData=true;
                }

                if(tijdslotStaat==true){
                    data[m].push_back("1");
                }
                else if(tijdslotStaat==false){
                    data[m].push_back("0");
                }
                else if(geenData==true){
                    data[m].push_back("out of range");
                }
            }
        }
    }
    return data;
}

std::vector< std::vector<QString> > convertData::convertDataGen(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID){
    data[0].push_back(sensorNaam);
    data[1].push_back(sensorID);
    bool errorSchrijven = true;

    if(rawdata.size()<=2){
        for ( unsigned int i = 2; i < data.size()-1; i++){
            data[i].push_back("0");
        }
    }
    else{
        for (unsigned int i = 2; i < data.size()-1; i++){
            bool geenData = true;

          for(unsigned int j = 1; j < rawdata.size();j++){

            if(data[i][1] <= rawdata[j][0] && data[i][1] >= rawdata[j-1][0]){
                if( rawdata[j][1] == rawdata[j-1][1] && rawdata[j][1] != "" ){
                    data[i].push_back(rawdata[j][1]);
                    geenData = false;
                } else if( rawdata[j][1] == "" && rawdata[j-1][1] != "" ){
                    data[i].push_back(rawdata[j-1][1]);
                    geenData = false;
                } else if( rawdata[j][1] == "" && rawdata[j-1][1] == "" ){

                    int t = j;
                    bool exitError = false;
                    while( rawdata[t][1] == "" && exitError==false  ){
                        t--;
                        if(t==0){
                            if(errorSchrijven==true){
                                std::cout << "toch maar 0 wegschrijven" << std::endl;
                            }
                            exitError = true;
                            errorSchrijven = false;
                            data[i].push_back("0");
                            geenData = false;
                        }
                    }

                    if(exitError==false){
                        data[i].push_back(rawdata[t][1]);
                        geenData = false;
                    }
                } else if( rawdata[j][1] != "" && rawdata[j-1][1] == "" ){
                    data[i].push_back(rawdata[j][1]);
                    geenData = false;
                }
                else{
                      double waarde_start = rawdata[j-1][1].toDouble();
                      double waarde_eind = rawdata[j][1].toDouble();
                      double delta_waarde = waarde_eind - waarde_start;
                      double tijd_start = rawdata[j-1][0].toDouble();
                      double tijd_eind = rawdata[j][0].toDouble();
                      double delta_tijd = tijd_eind - tijd_start;
                      double waarde_geinterpoleerd = (delta_waarde/delta_tijd) * (data[i][1].toDouble()-tijd_start) + waarde_start;
                      data[i].push_back(QString::number(waarde_geinterpoleerd));
                      geenData = false;
                }
            }



/*
            if(data[i][1] <= rawdata[j][0] && data[i][1] >= rawdata[j-1][0]){
                double waarde_start = rawdata[j-1][1].toDouble();
                double waarde_eind = rawdata[j][1].toDouble();
                double delta_waarde = waarde_eind - waarde_start;
                double tijd_start = rawdata[j-1][0].toDouble();
                double tijd_eind = rawdata[j][0].toDouble();
                double delta_tijd = tijd_eind - tijd_start;
                double waarde_geinterpoleerd = (delta_waarde/delta_tijd)*(data[i][1].toDouble()-tijd_start)+waarde_start;
                data[i].push_back(QString::number(waarde_geinterpoleerd));
            }
*/

          }
          if(data[i][1]>rawdata[rawdata.size()-1][0]){
            data[i].push_back("out of range");
            geenData = false;
          }

          if(geenData==true){
              data[i].push_back("-1 out of range");
              //cout << "test" << endl;
          }


        }
    }
    return data;
}

std::vector< std::vector<QString> > convertData::convertDataAirValve(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID){
    data[0].push_back(sensorNaam);
    data[1].push_back(sensorID);

    if(rawdata.size()<=2){
        for ( unsigned int i = 2; i < data.size()-1; i++){
            data[i].push_back("0");
        }
    }else{
        int j =0;
        QString positie = "15";
        while(data[2][1] >= rawdata[j][0]){
            positie=rawdata[j][1];
            j++;
        }
        int k = 0;
        for (unsigned int l = 2; l < data.size()-1; l++){
            if(data[l+1][1] <= rawdata[j][0]){
                data[l].push_back(positie);
                k = l+1;
            }
        }

        int huidigePositie = 0;
        //cout << k << endl;
        if(k<2){
            k=2;
        }
        for (unsigned int m = k; m < data.size()-1; m++){
            bool tijdslotStaat = false;
            int tijdslotPositie = huidigePositie;
            bool geenData=false;

            for (unsigned int n = 0; n < rawdata.size(); n++){
                if( data[m][1] <= rawdata[n][0] && data[m+1][1] >= rawdata[n][0] ){
                    positie = rawdata[n][1];
                    int tijdelijk = positie.toInt();

                    if(tijdslotStaat==false){
                        tijdslotPositie=tijdelijk;
                        huidigePositie=tijdelijk;
                        tijdslotStaat=true;
                    }
                    if(tijdslotStaat==true){
                        huidigePositie=tijdelijk;
                    }
                }
            }

            if(data[m][1]>rawdata[rawdata.size()-1][0]){
                //cout << data[m][1].toStdString() << " - " << rawdata[rawdata.size()-1][0].toStdString() << endl;
                geenData=true;
                //cout << sensorNaam.toStdString() << " - - " << sensorID.toStdString() << endl;
            }

            if(geenData==false){
                data[m].push_back(QString::number(tijdslotPositie));
            }else{
                data[m].push_back("out of range");
            }
        }
    }
    return data;
}

std::vector< std::vector<QString> > convertData::convertDataDatabase(std::vector<std::vector<QString> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval, unsigned int highFlow, unsigned int lowFlow)
{
    std::vector< std::vector<QString> > ruleData(newColumn[0].size(), std::vector<QString>(data.size()));

    // Volgende variabelen zijn bepaald dmv de 25 percentile en 75 percentile op de dataset van 2.008 2014-2015 (data per uur)
    const int Low_CO2Rule = 418,
              High_CO2Rule = 630,
              Low_Airflow = lowFlow,
              //Low_Airflow = 7,
              High_Airflow = highFlow;
              //High_Airflow = 70;

    int CO2pos = -1, Airpos = -1, PIRpos = -1;
    if(!(this->getColPos(colnames, CO2pos, Airpos, PIRpos)))
    {
        QMessageBox* warning = new QMessageBox();
        warning->warning(0, "Warning!", "Kan één van de volgende kolommen niet vinden: CO2, airflow of PIR sensor.");
        delete warning;

        return std::vector< std::vector<QString> >(); // Return lege vector als min. één van de drie kolommen niet gevonden zijn
    }

    CO2pos -= 2;    // De twee kolommen "Datum" en "Tijd" worden gestript van de "echte" data
    Airpos -= 2;
    PIRpos -= 2;
    //dataLogger->write(QString::number(CO2pos) + QString::number(Airpos) + QString::number(PIRpos));

    for(unsigned int i= 0; i < data.size(); i++)
    {
        for(unsigned int j = 0; j < data[i].size(); j++)
        {
            if(j == CO2pos)
            {
                if(!std::isnan(data[i][j].toInt()))
                {
                    if(data[i][j].toInt() <= Low_CO2Rule)       // Low CO2
                    {
                        ruleData[4][i] = "1"; // Normal
                        ruleData[5][i] = "0"; // Too_low
                    }
                    else if(data[i][j].toInt() >= High_CO2Rule) // High CO2
                    {
                        ruleData[4][i] = "0"; // Too_high
                        ruleData[5][i] = "1"; // Normal
                    }
                    else
                    {
                        ruleData[4][i] = "1"; // Normal
                        ruleData[5][i] = "1"; // Normal
                    }

                    if(i > 3)                           // Frozen CO2
                    {
                        if((timeInterval < 30) && (!std::isnan(data[i-1][j].toInt())) && (!std::isnan(data[i-2][j].toInt())) &&
                           (!std::isnan(data[i-3][j].toInt())) && (!std::isnan(data[i-4][j].toInt())))
                        {
                            if((data[i][j].toInt() == data[i-1][j].toInt()) && (data[i][j].toInt() == data[i-2][j].toInt()) &&
                               (data[i][j].toInt() == data[i-3][j].toInt()) && (data[i][j].toInt() == data[i-4][j].toInt()))
                            {
                                ruleData[6][i] = "0"; // True
                            } else {
                                ruleData[6][i] = "1"; // False
                            }
                        }
                        else if(!std::isnan(data[i-1][j].toInt()))
                        {
                            if(data[i][j].toInt() == data[i-1][j].toInt()) {
                                ruleData[6][i] = "0"; // True
                            } else {
                                ruleData[6][i] = "1"; // False
                            }
                        } else {
                            ruleData[6][i] = "0"; // True
                        }
                    }
                    else  {
                        ruleData[6][i] = "1"; //False
                    }

                    if(i > 0)                      // Non-identical CO2 neighbours
                    {
                        if(!std::isnan(data[i-1][j].toInt()))
                        {
                            if((data[i][j].toInt() >= (data[i-1][j].toInt() - std::round(data[i-1][j].toInt()/100*10))) &&
                               (data[i][j].toInt() <= (data[i-1][j].toInt() + std::round(data[i-1][j].toInt()/100*10))))
                            {
                                ruleData[7][i] = "1"; // False
                            } else {
                                ruleData[7][i] = "0"; // True
                            }
                        } else {
                            ruleData[7][i] = "0"; // True
                        }
                    }
                    else {
                        ruleData[7][i] = "1"; // False
                    }

                } else {
                    ruleData[4][i] = "0"; // Too_high
                    ruleData[5][i] = "0"; // Too_low
                    ruleData[6][i] = "0"; // True
                    ruleData[7][i] = "0"; // True
                }
            }
            else if(j == Airpos)
            {
                if(!std::isnan(data[i][j].toInt()))
                {
                    if(data[i][j].toInt() >= High_Airflow)           // High airflow
                    {
                        ruleData[0][i] = "0"; // Too_high
                        ruleData[1][i] = "1"; // Normal
                    }
                    else if(data[i][j].toInt() <= Low_Airflow)       // Low airflow
                    {
                        ruleData[0][i] = "1"; // Normal
                        ruleData[1][i] = "0"; // Too_low
                    }
                    else                                    // Normal airflow
                    {
                        ruleData[0][i] = "1"; // Normal
                        ruleData[1][i] = "1"; // Normal
                    }

                    if(i > 0)                               // Frozen flow
                    {
                        if((!std::isnan(data[i-1][j].toInt())) && (!std::isnan(data[i][CO2pos].toInt())) && (!std::isnan(data[i-1][CO2pos].toInt())))
                        {
                            // CO2 verandert (binnen 10% verandering van de vorige), maar de flow niet
                            if((data[i][CO2pos].toInt() >= (data[i-1][CO2pos].toInt() - std::round(data[i-1][CO2pos].toInt()/100*10))) &&
                               (data[i][CO2pos].toInt() <= (data[i-1][CO2pos].toInt() + std::round(data[i-1][CO2pos].toInt()/100*10))) &&
                               (data[i][j].toInt() == data[i-1][j].toInt()))
                            {
                                ruleData[2][i] = "0"; // True
                            } else {
                                ruleData[2][i] = "1"; // False
                            }
                        } else {
                            ruleData[2][i] = "0"; // True
                        }
                    }
                    else
                    {
                        ruleData[2][i] = "1"; // False
                    }
                } else {
                    ruleData[0][i] = "0"; // Too_high
                    ruleData[1][i] = "0"; // Too_low
                    ruleData[2][i] = "0"; // True
                }
            }
            else if(j == PIRpos)
            {
                if(!std::isnan(data[i][j].toInt()))
                {
                    if(!std::isnan(data[i][Airpos].toInt()))
                    {
                        if((data[i][j].toInt() && data[i][Airpos].toInt()) || (data[i][j].toInt() == 0 && data[i][Airpos].toInt() == 0)) // Flow while PIR = 0
                        {
                            ruleData[3][i] = "1"; // False
                        } else {
                            ruleData[3][i] = "0"; // True
                        }
                    } else {
                        ruleData[3][i] = "0"; // True
                    }

                    if(data[i][j].toInt() == 0 || data[i][j].toInt() == 1)   // PIR NaN
                    {
                        ruleData[8][i] = "1"; // False
                    } else {
                        ruleData[8][i] = "0"; // True
                    }
                }
                else {
                    ruleData[3][i] = "0"; // True
                    ruleData[8][i] = "0"; // True
                }
            }
        }
    }

    return ruleData;
}

std::vector< std::vector<float> > convertData::convertDataDatabase(std::vector<std::vector<float> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval, unsigned int highFlow, unsigned int lowFlow)
{
    std::vector< std::vector<float> > ruleData(newColumn[0].size(), std::vector<float>(data.size()));

    // Volgende variabelen zijn bepaald dmv de 25 percentile en 75 percentile op de dataset van 2.008 2014-2015 (data per uur)
    const int Low_CO2Rule = 418,
              High_CO2Rule = 630,
              Low_Airflow = lowFlow,
              //Low_Airflow = 7,
              High_Airflow = highFlow;
              //High_Airflow = 70;

    int CO2pos = -1, Airpos = -1, PIRpos = -1;
    if(!(this->getColPos(colnames, CO2pos, Airpos, PIRpos)))
    {
        QMessageBox* warning = new QMessageBox();
        warning->warning(0, "Warning!", "Kan één van de volgende kolommen niet vinden: CO2, airflow of PIR sensor.");
        delete warning;

        return std::vector< std::vector<float> >(); // Return lege vector als min. één van de drie kolommen niet gevonden zijn
    }

    CO2pos -= 2;    // De twee kolommen "Datum" en "Tijd" worden gestript van de "echte" data
    Airpos -= 2;
    PIRpos -= 2;
    dataLogger->write(QString(QString("CO2 kolom: ") + QString::number(CO2pos) + QString(" air kolom: ") + QString::number(Airpos) + QString(" PIR kolom: ") + QString::number(PIRpos)));

    for(unsigned int i= 0; i < data.size(); i++)
    {
        for(unsigned int j = 0; j < data[i].size(); j++)
        {
            if(j == CO2pos)
            {
                if(!std::isnan(data[i][j]))
                {
                    if(data[i][j] <= Low_CO2Rule)       // Low CO2
                    {
                        ruleData[4][i] = 1; // Normal
                        ruleData[5][i] = 0; // Too_low
                    }
                    else if(data[i][j] >= High_CO2Rule) // High CO2
                    {
                        ruleData[4][i] = 0; // Too_high
                        ruleData[5][i] = 1; // Normal
                    }
                    else
                    {
                        ruleData[4][i] = 1; // Normal
                        ruleData[5][i] = 1; // Normal
                    }

                    if(i > 3)                           // Frozen CO2
                    {
                        if((timeInterval < 30) && (!std::isnan(data[i-1][j])) && (!std::isnan(data[i-2][j])) &&
                           (!std::isnan(data[i-3][j])) && (!std::isnan(data[i-4][j])))
                        {
                            if((data[i][j] == data[i-1][j]) && (data[i][j] == data[i-2][j]) &&
                               (data[i][j] == data[i-3][j]) && (data[i][j] == data[i-4][j]))
                            {
                                ruleData[6][i] = 0; // True
                            } else {
                                ruleData[6][i] = 1; // False
                            }
                        }
                        else if(!std::isnan(data[i-1][j]))
                        {
                            if(data[i][j] == data[i-1][j]) {
                                ruleData[6][i] = 0; // True
                            } else {
                                ruleData[6][i] = 1; // False
                            }
                        } else {
                            ruleData[6][i] = 0; // True
                        }
                    }
                    else  {
                        ruleData[6][i] = 1; //False
                    }

                    if(i > 0)                      // Non-identical CO2 neighbours
                    {
                        if(!std::isnan(data[i-1][j]))
                        {
                            if((data[i][j] >= (data[i-1][j] - std::round(data[i-1][j]/100*10))) &&
                               (data[i][j] <= (data[i-1][j] + std::round(data[i-1][j]/100*10))))
                            {
                                ruleData[7][i] = 1; // False
                            } else {
                                ruleData[7][i] = 0; // True
                            }
                        } else {
                            ruleData[7][i] = 0; // True
                        }
                    }
                    else {
                        ruleData[7][i] = 1; // False
                    }

                } else {
                    ruleData[4][i] = 0; // Too_high
                    ruleData[5][i] = 0; // Too_low
                    ruleData[6][i] = 0; // True
                    ruleData[7][i] = 0; // True
                }
            }
            else if(j == Airpos)
            {
                if(!std::isnan(data[i][j]))
                {
                    if(data[i][j] >= High_Airflow)           // High airflow
                    {
                        ruleData[0][i] = 0; // Too_high
                        ruleData[1][i] = 1; // Normal
                    }
                    else if(data[i][j] <= Low_Airflow)       // Low airflow
                    {
                        ruleData[0][i] = 1; // Normal
                        ruleData[1][i] = 0; // Too_low
                    }
                    else                                    // Normal airflow
                    {
                        ruleData[0][i] = 1; // Normal
                        ruleData[1][i] = 1; // Normal
                    }

                    if(i > 0)                               // Frozen flow
                    {
                        if((!std::isnan(data[i-1][j])) && (!std::isnan(data[i][CO2pos])) && (!std::isnan(data[i-1][CO2pos])))
                        {
                            // CO2 verandert (binnen 10% verandering van de vorige), maar de flow niet
                            if((data[i][CO2pos] >= (data[i-1][CO2pos] - std::round(data[i-1][CO2pos]/100*10))) &&
                               (data[i][CO2pos] <= (data[i-1][CO2pos] + std::round(data[i-1][CO2pos]/100*10))) &&
                               (data[i][j] == data[i-1][j]))
                            {
                                ruleData[2][i] = 0; // True
                            } else {
                                ruleData[2][i] = 1; // False
                            }
                        } else {
                            ruleData[2][i] = 0; // True
                        }
                    }
                    else
                    {
                        ruleData[2][i] = 1; // False
                    }
                } else {
                    ruleData[0][i] = 0; // Too_high
                    ruleData[1][i] = 0; // Too_low
                    ruleData[2][i] = 0; // True
                }
            }
            else if(j == PIRpos)
                {
                    if(!std::isnan(data[i][j]))
                    {
                        if(!std::isnan(data[i][Airpos]))
                        {
                            if((data[i][j] && data[i][Airpos]) || (data[i][j] == 0 && data[i][Airpos] == 0)) // Flow while PIR = 0
                            {
                                ruleData[3][i] = 1; // False
                            } else {
                                ruleData[3][i] = 0; // True
                            }
                        } else {
                            ruleData[3][i] = 0; // True
                        }

                        if(data[i][j] == 0 || data[i][j] == 1)   // PIR NaN
                        {
                            ruleData[8][i] = 1; // False
                        } else {
                            ruleData[8][i] = 0; // True
                        }
                    }
                    else {
                        ruleData[3][i] = 0; // True
                        ruleData[8][i] = 0; // True
                    }
                }
        }
    }

    return ruleData;
}

bool convertData::convertEverything(int currentSensor,int currentSensorID, windowConnectDatabase* parentWindow, std::vector< std::vector<QString> >* currentData, std::vector< std::vector<QString> > currentResult){
    QString sensor = QString::number(currentSensor) + " - " + QString::number(currentSensorID);
    switch (currentSensor) {
        case 83:
            //parentWindow->new_log_entry("Meetpunten Aanwezigheid interpoleren");
            *currentData = this->convertDataPres(*currentData, currentResult, "PIRSensor", sensor);
            return 1;
        break;

        case 37:
            //parentWindow->new_log_entry("Meetpunten CO2 interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "CO2Sensor", sensor);
            return 1;
        break;

        case 48:
            //parentWindow->new_log_entry("Meetpunten Airflow interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "Airflow", sensor);
            return 1;
        break;

        case 46: case 66: case 67:
            //parentWindow->new_log_entry("Meetpunten Temperatuur interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "Temp", sensor);
            return 1;
        break;

        case 69:
            //parentWindow->new_log_entry("Meetpunten Klepstand interpoleren");
            *currentData = this->convertDataAirValve(*currentData, currentResult, "Air Valve Position", sensor);
            return 1;
        break;

        case 5:
            //parentWindow->new_log_entry("Meetpunten IR Temperatuur interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "Temperature", sensor);
            return 1;
        break;

        case 56:
            //parentWindow->new_log_entry("Meetpunten Light State interpoleren");
            *currentData = this->convertDataPres(*currentData, currentResult, "Lightstate", sensor);
            return 1;
        break;

        case 151:
            //parentWindow->new_log_entry("Meetpunten outside temp interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT TEMP", sensor);
            return 1;
        break;

        case 152:
            //parentWindow->new_log_entry("Meetpunten outside avg lights interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT AVG LIGHTS", sensor);
            return 1;
        break;

        case 153:
            //parentWindow->new_log_entry("Meetpunten outside air speed interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT AIR SPEED", sensor);
            return 1;
        break;

        case 154:
            //parentWindow->new_log_entry("Meetpunten outside air dest interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT AIR DEST", sensor);
            return 1;
        break;

        case 155:
            //parentWindow->new_log_entry("Meetpunten outside schemering opnemer interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT Schermering", sensor);
            return 1;
        break;

        case 156:
            //parentWindow->new_log_entry("Meetpunten outside rain interpoleren");
            *currentData = this->convertDataPres(*currentData, currentResult, "OUT RAIN", sensor);
            return 1;
        break;

        case 157:
            //parentWindow->new_log_entry("Meetpunten outside humidity interpoleren");
            *currentData = this->convertDataGen(*currentData, currentResult, "OUT HUMIDITY", sensor);
            return 1;
        break;

        default:
        parentWindow->new_log_entry("Onbekend sensortype: "+currentSensor);
            return 0;
        break;
    }
}

// Zoekt het kolomnummer van de CO2, Airflow of PIR sensor
bool convertData::getColPos(std::vector<QString> cols, int &CO2pos, int &Airpos, int &PIRpos)
{
    for(unsigned int i = 0; i < cols.size(); i++)
    {
        if(cols[i].contains("CO2", Qt::CaseInsensitive)) {
            CO2pos = i;
        }
        else if(cols[i].contains("Air", Qt::CaseSensitive)) {
            Airpos = i;
        }
        else if(cols[i].contains("PIR", Qt::CaseInsensitive)) {
            PIRpos = i;
        }
    }

    if(CO2pos == -1 || Airpos == -1 || PIRpos == -1) {
        return false;
    } else {
        return true;
    }
}
