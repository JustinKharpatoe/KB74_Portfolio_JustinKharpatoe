#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "window.h"

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
    Ui::MainWindow *ui;
    Window* window;
};

#endif // MAINWINDOW_H