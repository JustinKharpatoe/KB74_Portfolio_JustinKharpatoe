#ifndef CONVERTDATA_H
#define CONVERTDATA_H

#include <QString>
#include <QMessageBox>
#include <vector>

#include <QFileDialog>

#include "import.h"
#include "logger.h"

class windowConnectDatabase;

class convertData: public import {
    public:
        convertData();
        std::vector< std::vector<QString> > convertDataPres(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam,QString sensorID);
        std::vector< std::vector<QString> > convertDataGen(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID);
        std::vector< std::vector<QString> > convertDataAirValve(std::vector< std::vector<QString> > data, std::vector< std::vector<QString> > rawdata, QString sensorNaam, QString sensorID);
        std::vector< std::vector<QString> > convertDataDatabase(std::vector<std::vector<QString> > data, std::vector<QString> colnames, std::vector<std::vector<QString> > newColumn, int timeInterval, unsigned int highFlow, unsigned int lowFlow);
        std::vector< std::vector<float> > convertDataDatabase(std::vector<std::vector<float> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval, unsigned int highFlow, unsigned int lowFlow);
        bool convertEverything(int currentSensor, int currentSensorID, windowConnectDatabase* parentWindow, std::vector< std::vector<QString> > *currentData, std::vector< std::vector<QString> > currentResult);

    private:
        bool getColPos(std::vector<QString> cols, int &CO2pos, int &Airpos, int &PIRpos);
        Logger *dataLogger;

};

#endif // CONVERTDATA_H
