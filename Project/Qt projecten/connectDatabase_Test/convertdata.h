#ifndef CONVERTDATA_H
#define CONVERTDATA_H

#include <QString>
#include <vector>

class MainWindow;

class convertData {
    public:
        convertData();
        std::vector< std::vector<QString> > convertDataPres(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam,QString sensorID);
        std::vector< std::vector<QString> > convertDataGen(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID);
        std::vector< std::vector<QString> > convertDataAirValve(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID);
        bool convertEverything(int currentSensor, int currentSensorID, MainWindow* parentWindow, std::vector< std::vector<QString> > *currentData, std::vector< std::vector<QString> > currentResult);
    private:

};

#endif // CONVERTDATA_H
