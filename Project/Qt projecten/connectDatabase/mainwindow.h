#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDate>
#include <QTime>
#include <QStandardItemModel>
#include <QSqlQuery>
#include <QFileDialog>

#include "database.h"
#include "query.h"
#include "datetimecalc.h"
#include "convertdata.h"
#include "exportcsv.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void new_log_entry(QString newTextLine);

private slots:
    void on_pushStart_clicked();
    void on_pushRefresh_clicked();

    void on_date_start_userDateChanged(const QDate &date);
    void on_date_end_userDateChanged(const QDate &date);
    void on_time_start_timeChanged(const QTime &time);
    void on_time_end_timeChanged(const QTime &time);

    void on_pushExportCSV_clicked();

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

private:
    void buttonStartEnabling();
    void addExtraSensors();
    void addNormalSensors();
    Ui::MainWindow *ui;
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
                                        currentData;
    std::vector< std::vector<int> > selectedSensorenID;

};

#endif // MAINWINDOW_H
