#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QFileDialog>
#include <vector>

#include "convertdata.h"
#include "logger.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    bool switchRowAndCols(std::vector< std::vector<QString> > &strdata, bool timeavailble, int colbegin);
    bool convertToFloat();
    bool exportFile(std::vector<std::vector<float> > data, QString filename, QString delimiter);
    template<class T> static std::vector< std::vector<T> > transposeData(std::vector< std::vector<T> > oldData);

    Ui::MainWindow *ui;
    Logger* dataLogger;
    convertData* converter;

    std::vector< std::vector<QString> > totalData,
                                        headerData,
                                        timeData,
                                        ruleData;
    std::vector< std::vector<float> > sensorData;
};

#endif // MAINWINDOW_H
