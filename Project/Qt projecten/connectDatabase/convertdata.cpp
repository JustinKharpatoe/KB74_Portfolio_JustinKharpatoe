#include "convertdata.h"
#include "mainwindow.h"

convertData::convertData() { }

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

bool convertData::convertEverything(int currentSensor,int currentSensorID, MainWindow* parentWindow, std::vector< std::vector<QString> >* currentData, std::vector< std::vector<QString> > currentResult){
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
