#include "convertdata.h"

convertData::convertData()
{
    dataLogger = new Logger(0, "log_Convert.txt");
}

std::vector< std::vector<QString> > convertData::convertDataDatabase(std::vector<std::vector<QString> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval)
{
    // Volgende variabelen zijn bepaald dmv de 25 percentile en 75 percentile op de dataset van 2.008 2014-2015 (data per uur)
    const unsigned int Low_CO2Rule = 418,
                       High_CO2Rule = 630,
                       Low_Airflow = 7,
                       High_Airflow = 70;

    int CO2pos = 0, Airpos = 0, PIRpos = 0;
    this->getColPos(colnames, CO2pos, Airpos, PIRpos);
    //this->setHeaderData(newColumn);

    data.erase(data.begin()+1);/*
    for(unsigned int i=0; data.size(); i++) {
        for(unsigned int j=0; data[i].size(); j++) {
            data[i].erase(data[i].begin(), data[i].begin()+1);
        }
    }*/

    //std::vector< std::vector<QString> > ruleData;
    std::vector< std::vector<QString> > ruleData(newColumn[0].size(), std::vector<QString>(data.size()));

    unsigned int i=0,
                 j=0;

    dataLogger->write(QString("Aantal kolommen data: " + QString::number(data.size())));
    dataLogger->write(QString("Aantal rijen voor kolom 0 data: " + QString::number(data[0].size())));
    dataLogger->write(QString("Aantal kolommen ruleData: " + QString::number(ruleData.size())));
    dataLogger->write(QString("Aantal rijen voor kolom 0 ruleData: " + QString::number(ruleData[0].size())));
    dataLogger->write(QString("Rij 1, kolom 1: " + QString::number(data[0][0].toInt())));
    dataLogger->write(QString("Rij 2, kolom 2: " + QString::number(data[1][1].toInt())));
    dataLogger->write(QString("Rij 3, kolom 3: " + QString::number(data[2][2].toInt())));


/*    for(/*unsigned int i= 0*//*; i < data.size(); i++)
    {
        //dataLogger->write("Kolom nummer: " + i);
        for(/*unsigned int j = 0*//*; j < colnames.size(); j++)
        {
            if(colnames[j].contains("CO2", Qt::CaseInsensitive) || colnames[j].contains("Air", Qt::CaseInsensitive) || colnames[j].contains("PIR", Qt::CaseInsensitive))
            {
                if(!std::isnan(data[i][j].toInt()))
                {
                    //dataLogger->write(QString("Lijn: %1 en kolom %2").arg(i, j));
                    dataLogger->write(QString("Lijn: " + QString::number(i) + " en kolom " + colnames[j] + ": " + QString::number(data[i][j].toInt())));
                            //(QString("Lijn: ") + i + QString("en kolom: ") + j);
                    //dataLogger->write(QString("Data: " + ));
                    if(colnames[j].contains("CO2", Qt::CaseInsensitive))
                    {
                        if(data[i][j] <= Low_CO2Rule)       // Low CO2
                        {
                            ruleData[i][4] = "1";
                            ruleData[i][5] = "0";
                        }
                        else if(data[i][j] >= High_CO2Rule) // High CO2
                        {
                            ruleData[i][4] = "0";
                            ruleData[i][5] = "1";
                        }
                        else
                        {
                            ruleData[i][4] = "1";
                            ruleData[i][5] = "1";
                        }

                        if(i > 3)                           // Frozen CO2
                        {
                            if(timeInterval < 30 && !std::isnan(data[i-1][j].toInt()) && !std::isnan(data[i-2][j].toInt()) &&
                                    !std::isnan(data[i-3][j].toInt()) && !std::isnan(data[i-4][j].toInt()))
                            {
                                if(data[i][j] == data[i-1][j] && data[i][j] == data[i-2][j] &&
                                        data[i][j] == data[i-3][j] && data[i][j] == data[i-4][j])
                                {
                                    ruleData[i][6] = "0";
                                } else
                                {
                                    ruleData[i][6] = "1";
                                }
                            }
                            else if(!std::isnan(data[i-1][j].toInt()))
                            {
                                if(data[i][j] == data[i-1][j]) {
                                    ruleData[i][6] = "0";
                                } else
                                {
                                    ruleData[i][6] = "1";
                                }
                            } else
                            {
                                ruleData[i][6] = "0";
                            }
                        }
                        else if(i > 0)                      // Non-identical CO2 neighbours
                        {
                            ruleData[i][6] = "1";
                            if(!std::isnan(data[i-1][j].toInt()))
                            {
                                if((data[i][j].toInt() >= (data[i-1][j].toInt() - round(data[i-1][j].toInt()/100*10))) &&
                                        (data[i][j].toInt() <= (data[i-1][j].toInt() + round(data[i-1][j].toInt()/100*10))))
                                {
                                    ruleData[i][j] = "1";
                                }
                                else
                                {
                                    ruleData[i][j] = "0";
                                }
                            }
                            else
                            {
                                ruleData[i][j] = "0";
                            }
                        }
                        else
                        {
                            ruleData[i][6] = "1";
                            ruleData[i][7] = "1";
                        }
                    }
                    else if(colnames[j].contains("Air", Qt::CaseInsensitive))
                    {
                        if(data[i][j] > High_Airflow)           // High airflow
                        {
                            ruleData[i][0] = "0";
                            ruleData[i][1] = "1";
                        }
                        else if(data[i][j] < Low_Airflow)       // Low airflow
                        {
                            ruleData[i][0] = "1";
                            ruleData[i][1] = "0";
                        }
                        else                                    // Normal airflow
                        {
                            ruleData[i][0] = "1";
                            ruleData[i][1] = "1";
                        }

                        if(i > 0)                               // Frozen flow
                        {
                            if(!std::isnan(data[i-1][CO2pos].toInt()))
                            {
                                // CO2 verandert (binnen 10% verandering van de vorige), maar de flow niet
                                if((data[i][CO2pos].toInt() >= (data[i-1][CO2pos].toInt() - round(data[i-1][CO2pos].toInt()/100*10))) &&
                                        (data[i][CO2pos].toInt() <= (data[i-1][CO2pos].toInt() + round(data[i-1][CO2pos].toInt()/100*10))) &&
                                        (data[i][j] == data[i][j]))
                                {
                                    ruleData[i][2] = "0";
                                } else
                                {
                                    ruleData[i][2] = "1";
                                }
                            } else
                            {
                                ruleData[i][2] = "0";
                            }
                        } else
                        {
                            ruleData[i][2] = 1;
                        }
                    }
                    else if(colnames[j].contains("PIR", Qt::CaseInsensitive))
                    {
                        if((data[i][j].toInt() && data[i][Airpos].toInt()) || (data[i][j].toInt() == 0 && data[i][Airpos].toInt() == 0)) // Flow while PIR = 0
                        {
                            ruleData[i][3] = "1";
                        }
                        else
                        {
                            ruleData[i][3] = "0";
                        }

                        if(data[i][j].toInt() == 0 || data[i][j].toInt() == 1)   // PIR NaN
                        {
                            ruleData[i][8] = "1";
                        }
                        else
                        {
                            ruleData[i][8] = "0";
                        }
                    }

                    //dataLogger->write(QString(QString::number(i) + ", " + QString::number(j) + ": " + QString::number(ruleData[i][j].toInt())));

                }
                else
                {
                    //dataLogger->write(QString("VOOR het 0 toekennen bij: " + QString::number(i) + ", " + QString::number(j)));
                    ruleData[i][j] = "0";
                    //dataLogger->write(QString("NA het 0 toekennen bij: " + QString::number(i) + ", " + QString::number(j)));
                }
            }
        }
    }*/

    for(/*unsigned int i= 0*/; i < data.size(); i++)
    {
        //dataLogger->write("Kolom nummer: " + i);
        for(/*unsigned int j = 0*/; j < data[i].size(); j++)
        {
            if(data[0][j].contains("CO2", Qt::CaseInsensitive) || data[0][j].contains("Air", Qt::CaseInsensitive) || data[0][j].contains("PIR", Qt::CaseInsensitive))
            {
                if(!std::isnan(data[i][j].toInt()))
                {
                    //dataLogger->write(QString("Lijn: %1 en kolom %2").arg(i, j));
                    dataLogger->write(QString("Lijn: " + QString::number(i) + " en kolom " + colnames[j] + ": " + QString::number(data[i][j].toInt())));
                            //(QString("Lijn: ") + i + QString("en kolom: ") + j);
                    //dataLogger->write(QString("Data: " + ));
                    if(data[0][j].contains("CO2", Qt::CaseInsensitive))
                    {
                        if(data[i][j].toInt() <= Low_CO2Rule)       // Low CO2
                        {
                            ruleData[4][i] = "1";
                            ruleData[5][i] = "0";
                        }
                        else if(data[i][j].toInt() >= High_CO2Rule) // High CO2
                        {
                            ruleData[4][i] = "0";
                            ruleData[5][i] = "1";
                        }
                        else
                        {
                            ruleData[4][i] = "1";
                            ruleData[5][i] = "1";
                        }

                        if(i > 3)                           // Frozen CO2
                        {
                            if(timeInterval < 30 && !std::isnan(data[i-1][j].toInt()) && !std::isnan(data[i-2][j].toInt()) &&
                                    !std::isnan(data[i-3][j].toInt()) && !std::isnan(data[i-4][j].toInt()))
                            {
                                if(data[i][j] == data[i-1][j] && data[i][j] == data[i-2][j] &&
                                        data[i][j] == data[i-3][j] && data[i][j] == data[i-4][j])
                                {
                                    ruleData[6][i] = "0";
                                } else
                                {
                                    ruleData[6][i] = "1";
                                }
                            }
                            else if(!std::isnan(data[i-1][j].toInt()))
                            {
                                if(data[i][j].toInt() == data[i-1][j].toInt()) {
                                    ruleData[6][i] = "0";
                                } else
                                {
                                    ruleData[6][i] = "1";
                                }
                            } else
                            {
                                ruleData[6][i] = "0";
                            }
                        }
                        else if(i > 0)                      // Non-identical CO2 neighbours
                        {
                            ruleData[6][i] = "1";
                            if(!std::isnan(data[i-1][j].toInt()))
                            {
                                if((data[i][j].toInt() >= (data[i-1][j].toInt() - round(data[i-1][j].toInt()/100*10))) &&
                                   (data[i][j].toInt() <= (data[i-1][j].toInt() + round(data[i-1][j].toInt()/100*10))))
                                {
                                    ruleData[7][i] = "1";
                                }
                                else
                                {
                                    ruleData[7][i] = "0";
                                }
                            }
                            else
                            {
                                ruleData[7][i] = "0";
                            }
                        }
                        else
                        {
                            ruleData[6][i] = "1";
                            ruleData[7][i] = "1";
                        }
                    }
                    else if(data[0][j].contains("Air", Qt::CaseInsensitive))
                    {
                        if(data[i][j] > High_Airflow)           // High airflow
                        {
                            ruleData[0][i] = "0";
                            ruleData[1][i] = "1";
                        }
                        else if(data[i][j] < Low_Airflow)       // Low airflow
                        {
                            ruleData[0][i] = "1";
                            ruleData[1][i] = "0";
                        }
                        else                                    // Normal airflow
                        {
                            ruleData[0][i] = "1";
                            ruleData[1][i] = "1";
                        }

                        if(i > 0)                               // Frozen flow
                        {
                            if(!std::isnan(data[i-1][CO2pos].toInt()))
                            {
                                // CO2 verandert (binnen 10% verandering van de vorige), maar de flow niet
                                if((data[i][CO2pos].toInt() >= (data[i-1][CO2pos].toInt() - round(data[i-1][CO2pos].toInt()/100*10))) &&
                                        (data[i][CO2pos].toInt() <= (data[i-1][CO2pos].toInt() + round(data[i-1][CO2pos].toInt()/100*10))) &&
                                        (data[i][j] == data[i][j]))
                                {
                                    ruleData[2][i] = "0";
                                } else
                                {
                                    ruleData[2][i] = "1";
                                }
                            } else
                            {
                                ruleData[2][i] = "0";
                            }
                        } else
                        {
                            ruleData[2][i] = 1;
                        }
                    }
                    else if(data[0][j].contains("PIR", Qt::CaseInsensitive))
                    {
                        if((data[i][j].toInt() && data[i][Airpos].toInt()) || (data[i][j].toInt() == 0 && data[i][Airpos].toInt() == 0)) // Flow while PIR = 0
                        {
                            ruleData[3][i] = "1";
                        }
                        else
                        {
                            ruleData[3][i] = "0";
                        }

                        if(data[i][j].toInt() == 0 || data[i][j].toInt() == 1)   // PIR NaN
                        {
                            ruleData[8][i] = "1";
                        }
                        else
                        {
                            ruleData[8][i] = "0";
                        }
                    }

                    //dataLogger->write(QString(QString::number(i) + ", " + QString::number(j) + ": " + QString::number(ruleData[i][j].toInt())));

                }
                else
                {
                    //dataLogger->write(QString("VOOR het 0 toekennen bij: " + QString::number(i) + ", " + QString::number(j)));
                    ruleData[i][j] = "0";
                    //dataLogger->write(QString("NA het 0 toekennen bij: " + QString::number(i) + ", " + QString::number(j)));
                }
            }
        }
    }

    //EXPORT DATA
    QString filename = QFileDialog::getSaveFileName(0, QObject::tr("Select a .csv file"), ("C://"), QObject::tr(".csv files (*.csv)"));
    if(!filename.isEmpty())
    {
        QFile file( filename );
        if ( file.open(QIODevice::ReadWrite| QIODevice::Truncate | QIODevice::Text) ){
            QTextStream stream( &file );
            for(unsigned int j=0; j<newColumn[0].size(); j++)
            {
                if(j < (newColumn[0].size()-1)) {
                    stream << newColumn[0][j] <<  ";";
                } else {
                    stream << newColumn[0][j];
                }
            }
            stream << endl;

            for(unsigned int i=0; i<ruleData[i].size(); i++){
                //vector<QString> row = data[i];
                for (unsigned int j = 0; j < ruleData.size(); j++) { // Was row.size()
                    if(j < (ruleData.size()-1)) {
                        stream << ruleData[i][j] <<  ";";
                    } else {
                        stream << ruleData[i][j];
                    }
                }
                stream << endl;
            }
            file.close();
        }
    }
    dataLogger->write("Bestand weggeschreven");


    return ruleData;
}

std::vector< std::vector<float> > convertData::convertDataDatabase(std::vector<std::vector<float> > data, std::vector<QString> colnames, std::vector< std::vector<QString> > newColumn, int timeInterval)
{
    std::vector< std::vector<float> > ruleData(newColumn[0].size(), std::vector<float>(data.size()));

    // Volgende variabelen zijn bepaald dmv de 25 percentile en 75 percentile op de dataset van 2.008 2014-2015 (data per uur)
    const int Low_CO2Rule = 418,
              High_CO2Rule = 630,
              Low_Airflow = 7,
              High_Airflow = 70;

    int CO2pos = 0, Airpos = 0, PIRpos = 0;
    this->getColPos(colnames, CO2pos, Airpos, PIRpos);
    CO2pos -= 2;    // De twee kolommen "Datum" en "Tijd" worden gestript van de "echte" data
    Airpos -= 2;
    PIRpos -= 2;

//    unsigned int i=0,
//                 j=0;

    for(unsigned int i= 0; i < data.size(); i++)
    {
        for(unsigned int j = 0; j < data[i].size(); j++)
        {
            //if(colnames[j+2].contains("CO2", Qt::CaseInsensitive))
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
            //else if(colnames[j+2].contains("Air", Qt::CaseInsensitive))
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
            //else if(colnames[j+2].contains("PIR", Qt::CaseInsensitive))
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

            //dataLogger->write(QString(QString::number(i) + ", " + QString::number(j) + ": " + QString::number(ruleData[i][j])));
        }
    }

    return ruleData;
}

void convertData::getColPos(std::vector<QString> cols, int &CO2pos, int &Airpos, int &PIRpos)
{
    for(unsigned int i = 0; i < cols.size(); i++)
    {
        if(cols[i].contains("CO2", Qt::CaseInsensitive))
            CO2pos = i;
        if(cols[i].contains("Air", Qt::CaseSensitive))
            Airpos = i;
        if(cols[i].contains("PIR", Qt::CaseInsensitive))
            PIRpos = i;
    }
}
