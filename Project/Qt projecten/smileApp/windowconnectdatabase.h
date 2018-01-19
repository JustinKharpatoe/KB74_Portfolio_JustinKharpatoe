#ifndef WINDOWCONNECTDATABASE_H
#define WINDOWCONNECTDATABASE_H

#include <QDialog>

#include <QSettings>
#include <QDate>
#include <QTime>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QFileDialog>

#include "datacenter/database.h"
#include "datacenter/exportfiles.h"
#include "datacenter/query.h"
#include "datacenter/datetimecalc.h"
#include "datacenter/convertdata.h"

namespace Ui {
class windowConnectDatabase;
}

class windowConnectDatabase : public QDialog
{
    Q_OBJECT

public:
    explicit windowConnectDatabase(QWidget *parent = 0);
    ~windowConnectDatabase();
    void new_log_entry(QString newTextLine);
    std::vector< std::vector<QString> > getDatabaseData();
    int getTimeSlot();
    QString getRuimtenaam();

private slots:
    void on_pushStart_clicked();
    void on_pushRefresh_clicked();

    void on_date_start_userDateChanged(const QDate &date);
    void on_date_end_userDateChanged(const QDate &date);
    void on_time_start_timeChanged(const QTime &time);
    void on_time_end_timeChanged(const QTime &time);

    void on_checkPres_clicked(bool checked);
    void on_checkCO2_clicked(bool checked);
    void on_checkAirFlow_clicked(bool checked);
    void on_checkTempIr_clicked(bool checked);
    void on_checkLightState_clicked(bool checked);
    void on_checkValve_clicked(bool checked);
    void on_checkTemp_clicked(bool checked);
    void on_checkOutTemp_clicked(bool checked);
    void on_checkOutLight_clicked(bool checked);
    void on_checkOutAirSpeed_clicked(bool checked);
    void on_checkOutAirDest_clicked(bool checked);
    void on_checkOutScherming_clicked(bool checked);
    void on_checkOutRain_clicked(bool checked);
    void on_checkOutHumidity_clicked(bool checked);

    void on_pushExportCSV_clicked();

    void on_pushAnalyseData_clicked();

private:
    Ui::windowConnectDatabase *ui;

    void buttonStartEnabling();
    void addExtraSensors();
    void addNormalSensors();

    DataBase dataBase;

    int ruimte = 0;
    QString connectionSettings,
            logText,
            ruimtenaam;
    QDate date_start,
          date_end;
    QTime time_start,
          time_end;
    std::vector< int > extraSensors,
                       normalSensors;
    std::vector< std::vector<QString> > aanwezigeruimtes,
                                        currentResult,
                                        currentData ;
    std::vector< std::vector<int> > selectedSensorenID;
};


#endif // WINDOWCONNECTDATABASE_H

