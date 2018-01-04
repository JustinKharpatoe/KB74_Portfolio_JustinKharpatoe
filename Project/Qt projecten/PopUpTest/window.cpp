#include "window.h"
#include "ui_window.h"

#include <QHBoxLayout>

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    std::vector< std::vector<QString> > newColumn;
    newColumn.push_back({"High_flow", "Low_flow", "Flow_frozen", "Flow_while_PIR_0", "High_CO2", "Low_CO2", "CO2_frozen", "CO2_neighbours_non_identical", "PIR_NaN"});
    newColumn.push_back({"1", "2", "3", "4", "5", "6", "7", "8", " 9"});

    for(unsigned int i = 0; i < newColumn[0].size(); i++)
        ui->textBrowser->append(newColumn[0][i]);

    ui->textBrowser->append("\n");

    for(unsigned int i = 0; i < newColumn[1].size(); i++)
        ui->textBrowser->append(newColumn[1][i]);
}

Window::~Window()
{
    delete ui;
}

void Window::on_pushButton_clicked()
{
    this->close();
}
