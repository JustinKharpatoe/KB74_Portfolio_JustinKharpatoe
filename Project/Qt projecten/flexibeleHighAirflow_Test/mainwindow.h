#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool importCSV();
    bool makeMap();

    std::vector<std::vector<QString>> allData, timeData, totalData, headerData;
    std::vector<std::vector<float> > sensorData;
    std::map<QString, unsigned int> HighAirflow;
};

#endif // MAINWINDOW_H
