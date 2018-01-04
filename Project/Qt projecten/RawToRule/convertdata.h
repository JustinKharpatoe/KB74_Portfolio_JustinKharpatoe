#ifndef CONVERTDATA_H
#define CONVERTDATA_H

#include <vector>
#include <QFileDialog>
#include <QDebug>

#include "logger.h"

class convertData
{
public:
    convertData();

    std::vector< std::vector<QString> > convertDataDatabase(std::vector<std::vector<QString> > data, std::vector<QString> colnames, std::vector<std::vector<QString> > newColumn, int timeInterval);
    std::vector< std::vector<float> > convertDataDatabase(std::vector<std::vector<float> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval);

private:
    void getColPos(std::vector<QString> cols, int &CO2pos, int &Airpos, int &PIRpos);
    Logger* dataLogger;
};

#endif // CONVERTDATA_H
