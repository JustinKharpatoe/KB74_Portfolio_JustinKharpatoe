/********************************************************************************
** Form generated from reading UI file 'windowconnectdatabase.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWCONNECTDATABASE_H
#define UI_WINDOWCONNECTDATABASE_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_windowConnectDatabase
{
public:
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *logEntry;
    QSpacerItem *verticalSpacer;
    QTableView *tableView;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_15;
    QLabel *Text_startdate;
    QLabel *Text_enddate;
    QVBoxLayout *verticalLayout_5;
    QLabel *Text_host;
    QLabel *Text_database;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *db_host;
    QLineEdit *db_name;
    QVBoxLayout *verticalLayout_16;
    QDateEdit *date_start;
    QDateEdit *date_end;
    QVBoxLayout *verticalLayout_18;
    QTimeEdit *time_start;
    QTimeEdit *time_end;
    QVBoxLayout *verticalLayout_17;
    QLabel *Text_starttime;
    QLabel *Text_endtime;
    QVBoxLayout *verticalLayout_9;
    QLineEdit *db_user;
    QLineEdit *db_passw;
    QVBoxLayout *verticalLayout_10;
    QLabel *Text_username_3;
    QLabel *Text_password_3;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Text_refreshrooms_3;
    QPushButton *pushRefresh;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_19;
    QCheckBox *checkAirFlow;
    QCheckBox *checkValve;
    QCheckBox *checkCO2;
    QCheckBox *checkLightState;
    QCheckBox *checkPres;
    QCheckBox *checkTempIr;
    QCheckBox *checkTemp;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_5;
    QLabel *Text_timeslot;
    QComboBox *comboTime;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushStart;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_20;
    QCheckBox *checkOutRain;
    QCheckBox *checkOutAirDest;
    QCheckBox *checkOutLight;
    QCheckBox *checkOutTemp;
    QCheckBox *checkOutAirSpeed;
    QCheckBox *checkOutScherming;
    QCheckBox *checkOutHumidity;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *tab_2;
    QWidget *verticalLayoutWidget_14;
    QVBoxLayout *verticalLayout_25;
    QTableView *tableSensors;
    QTableView *tableRawData;
    QWidget *tab_6;
    QWidget *widget;
    QVBoxLayout *verticalLayout_24;
    QVBoxLayout *verticalLayout_21;
    QTableView *tableConvertedData;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_12;
    QComboBox *comboExportDelim;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushExportCSV;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushAnalyseData;

    void setupUi(QWidget *windowConnectDatabase)
    {
        if (windowConnectDatabase->objectName().isEmpty())
            windowConnectDatabase->setObjectName(QStringLiteral("windowConnectDatabase"));
        windowConnectDatabase->resize(1213, 643);
        tabWidget = new QTabWidget(windowConnectDatabase);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1191, 615));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(1191, 615));
        tabWidget->setMaximumSize(QSize(781, 16777215));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        verticalLayoutWidget = new QWidget(tab_1);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(460, 10, 721, 561));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        logEntry = new QTextBrowser(verticalLayoutWidget);
        logEntry->setObjectName(QStringLiteral("logEntry"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(logEntry->sizePolicy().hasHeightForWidth());
        logEntry->setSizePolicy(sizePolicy1);
        logEntry->setMaximumSize(QSize(16777215, 100));
        logEntry->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        logEntry->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout->addWidget(logEntry);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName(QStringLiteral("tableView"));

        verticalLayout->addWidget(tableView);

        gridLayoutWidget = new QWidget(tab_1);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 10, 431, 561));
        gridLayout_4 = new QGridLayout(gridLayoutWidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        Text_startdate = new QLabel(gridLayoutWidget);
        Text_startdate->setObjectName(QStringLiteral("Text_startdate"));
        Text_startdate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_15->addWidget(Text_startdate);

        Text_enddate = new QLabel(gridLayoutWidget);
        Text_enddate->setObjectName(QStringLiteral("Text_enddate"));
        Text_enddate->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_15->addWidget(Text_enddate);


        horizontalLayout_5->addLayout(verticalLayout_15);


        gridLayout_4->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        Text_host = new QLabel(gridLayoutWidget);
        Text_host->setObjectName(QStringLiteral("Text_host"));
        Text_host->setLayoutDirection(Qt::LeftToRight);
        Text_host->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(Text_host);

        Text_database = new QLabel(gridLayoutWidget);
        Text_database->setObjectName(QStringLiteral("Text_database"));
        Text_database->setLayoutDirection(Qt::LeftToRight);
        Text_database->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_5->addWidget(Text_database);


        gridLayout_4->addLayout(verticalLayout_5, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        db_host = new QLineEdit(gridLayoutWidget);
        db_host->setObjectName(QStringLiteral("db_host"));
        db_host->setMinimumSize(QSize(120, 0));
        db_host->setMaximumSize(QSize(120, 16777215));

        verticalLayout_6->addWidget(db_host);

        db_name = new QLineEdit(gridLayoutWidget);
        db_name->setObjectName(QStringLiteral("db_name"));
        db_name->setMinimumSize(QSize(120, 0));
        db_name->setMaximumSize(QSize(120, 16777215));

        verticalLayout_6->addWidget(db_name);


        gridLayout_4->addLayout(verticalLayout_6, 0, 1, 1, 1);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        date_start = new QDateEdit(gridLayoutWidget);
        date_start->setObjectName(QStringLiteral("date_start"));
        date_start->setDateTime(QDateTime(QDate(2014, 1, 1), QTime(0, 0, 0)));
        date_start->setCurrentSection(QDateTimeEdit::DaySection);
        date_start->setCalendarPopup(true);
        date_start->setDate(QDate(2014, 1, 1));

        verticalLayout_16->addWidget(date_start);

        date_end = new QDateEdit(gridLayoutWidget);
        date_end->setObjectName(QStringLiteral("date_end"));
        date_end->setDateTime(QDateTime(QDate(2014, 1, 2), QTime(0, 0, 0)));
        date_end->setCalendarPopup(true);
        date_end->setDate(QDate(2014, 1, 2));

        verticalLayout_16->addWidget(date_end);


        gridLayout_4->addLayout(verticalLayout_16, 3, 1, 1, 1);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        time_start = new QTimeEdit(gridLayoutWidget);
        time_start->setObjectName(QStringLiteral("time_start"));
        time_start->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(6, 0, 0)));
        time_start->setCalendarPopup(false);
        time_start->setTime(QTime(6, 0, 0));

        verticalLayout_18->addWidget(time_start);

        time_end = new QTimeEdit(gridLayoutWidget);
        time_end->setObjectName(QStringLiteral("time_end"));
        time_end->setDateTime(QDateTime(QDate(2000, 1, 1), QTime(23, 0, 0)));
        time_end->setTime(QTime(23, 0, 0));

        verticalLayout_18->addWidget(time_end);


        gridLayout_4->addLayout(verticalLayout_18, 3, 3, 1, 1);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        Text_starttime = new QLabel(gridLayoutWidget);
        Text_starttime->setObjectName(QStringLiteral("Text_starttime"));
        Text_starttime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_17->addWidget(Text_starttime);

        Text_endtime = new QLabel(gridLayoutWidget);
        Text_endtime->setObjectName(QStringLiteral("Text_endtime"));
        Text_endtime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_17->addWidget(Text_endtime);


        gridLayout_4->addLayout(verticalLayout_17, 3, 2, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        db_user = new QLineEdit(gridLayoutWidget);
        db_user->setObjectName(QStringLiteral("db_user"));
        db_user->setMinimumSize(QSize(120, 0));
        db_user->setMaximumSize(QSize(120, 16777215));

        verticalLayout_9->addWidget(db_user);

        db_passw = new QLineEdit(gridLayoutWidget);
        db_passw->setObjectName(QStringLiteral("db_passw"));
        db_passw->setMinimumSize(QSize(120, 0));
        db_passw->setMaximumSize(QSize(120, 16777215));
        db_passw->setAutoFillBackground(false);
        db_passw->setEchoMode(QLineEdit::Password);

        verticalLayout_9->addWidget(db_passw);


        gridLayout_4->addLayout(verticalLayout_9, 0, 3, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        Text_username_3 = new QLabel(gridLayoutWidget);
        Text_username_3->setObjectName(QStringLiteral("Text_username_3"));
        Text_username_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(Text_username_3);

        Text_password_3 = new QLabel(gridLayoutWidget);
        Text_password_3->setObjectName(QStringLiteral("Text_password_3"));
        Text_password_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_10->addWidget(Text_password_3);


        gridLayout_4->addLayout(verticalLayout_10, 0, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        Text_refreshrooms_3 = new QLabel(gridLayoutWidget);
        Text_refreshrooms_3->setObjectName(QStringLiteral("Text_refreshrooms_3"));
        Text_refreshrooms_3->setScaledContents(false);
        Text_refreshrooms_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(Text_refreshrooms_3);

        pushRefresh = new QPushButton(gridLayoutWidget);
        pushRefresh->setObjectName(QStringLiteral("pushRefresh"));
        pushRefresh->setEnabled(true);

        horizontalLayout_4->addWidget(pushRefresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_4->addLayout(horizontalLayout_4, 1, 0, 1, 4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_3);

        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        checkAirFlow = new QCheckBox(gridLayoutWidget);
        checkAirFlow->setObjectName(QStringLiteral("checkAirFlow"));
        checkAirFlow->setEnabled(true);
        checkAirFlow->setChecked(false);

        verticalLayout_19->addWidget(checkAirFlow);

        checkValve = new QCheckBox(gridLayoutWidget);
        checkValve->setObjectName(QStringLiteral("checkValve"));

        verticalLayout_19->addWidget(checkValve);

        checkCO2 = new QCheckBox(gridLayoutWidget);
        checkCO2->setObjectName(QStringLiteral("checkCO2"));
        checkCO2->setEnabled(true);
        checkCO2->setChecked(false);

        verticalLayout_19->addWidget(checkCO2);

        checkLightState = new QCheckBox(gridLayoutWidget);
        checkLightState->setObjectName(QStringLiteral("checkLightState"));

        verticalLayout_19->addWidget(checkLightState);

        checkPres = new QCheckBox(gridLayoutWidget);
        checkPres->setObjectName(QStringLiteral("checkPres"));
        checkPres->setChecked(false);

        verticalLayout_19->addWidget(checkPres);

        checkTempIr = new QCheckBox(gridLayoutWidget);
        checkTempIr->setObjectName(QStringLiteral("checkTempIr"));

        verticalLayout_19->addWidget(checkTempIr);

        checkTemp = new QCheckBox(gridLayoutWidget);
        checkTemp->setObjectName(QStringLiteral("checkTemp"));
        checkTemp->setEnabled(false);
        checkTemp->setChecked(false);

        verticalLayout_19->addWidget(checkTemp);


        horizontalLayout_8->addLayout(verticalLayout_19);


        gridLayout_4->addLayout(horizontalLayout_8, 5, 0, 1, 2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_5);

        Text_timeslot = new QLabel(gridLayoutWidget);
        Text_timeslot->setObjectName(QStringLiteral("Text_timeslot"));

        horizontalLayout_10->addWidget(Text_timeslot);

        comboTime = new QComboBox(gridLayoutWidget);
        comboTime->setObjectName(QStringLiteral("comboTime"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboTime->sizePolicy().hasHeightForWidth());
        comboTime->setSizePolicy(sizePolicy2);

        horizontalLayout_10->addWidget(comboTime);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_6);


        gridLayout_4->addLayout(horizontalLayout_10, 6, 0, 1, 4);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_4, 4, 0, 1, 4);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_7);

        pushStart = new QPushButton(gridLayoutWidget);
        pushStart->setObjectName(QStringLiteral("pushStart"));
        pushStart->setEnabled(false);
        sizePolicy2.setHeightForWidth(pushStart->sizePolicy().hasHeightForWidth());
        pushStart->setSizePolicy(sizePolicy2);
        pushStart->setMinimumSize(QSize(101, 32));
        pushStart->setMaximumSize(QSize(101, 32));
        pushStart->setCursor(QCursor(Qt::ArrowCursor));

        horizontalLayout_11->addWidget(pushStart);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_8);


        gridLayout_4->addLayout(horizontalLayout_11, 9, 0, 1, 4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        horizontalLayout_12->addItem(verticalSpacer_3);


        gridLayout_4->addLayout(horizontalLayout_12, 8, 0, 1, 4);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        verticalLayout_20 = new QVBoxLayout();
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        checkOutRain = new QCheckBox(gridLayoutWidget);
        checkOutRain->setObjectName(QStringLiteral("checkOutRain"));

        verticalLayout_20->addWidget(checkOutRain);

        checkOutAirDest = new QCheckBox(gridLayoutWidget);
        checkOutAirDest->setObjectName(QStringLiteral("checkOutAirDest"));

        verticalLayout_20->addWidget(checkOutAirDest);

        checkOutLight = new QCheckBox(gridLayoutWidget);
        checkOutLight->setObjectName(QStringLiteral("checkOutLight"));

        verticalLayout_20->addWidget(checkOutLight);

        checkOutTemp = new QCheckBox(gridLayoutWidget);
        checkOutTemp->setObjectName(QStringLiteral("checkOutTemp"));

        verticalLayout_20->addWidget(checkOutTemp);

        checkOutAirSpeed = new QCheckBox(gridLayoutWidget);
        checkOutAirSpeed->setObjectName(QStringLiteral("checkOutAirSpeed"));

        verticalLayout_20->addWidget(checkOutAirSpeed);

        checkOutScherming = new QCheckBox(gridLayoutWidget);
        checkOutScherming->setObjectName(QStringLiteral("checkOutScherming"));

        verticalLayout_20->addWidget(checkOutScherming);

        checkOutHumidity = new QCheckBox(gridLayoutWidget);
        checkOutHumidity->setObjectName(QStringLiteral("checkOutHumidity"));

        verticalLayout_20->addWidget(checkOutHumidity);


        horizontalLayout_9->addLayout(verticalLayout_20);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_4);


        gridLayout_4->addLayout(horizontalLayout_9, 5, 2, 1, 2);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_4->addItem(verticalSpacer_5, 2, 0, 1, 4);

        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayoutWidget_14 = new QWidget(tab_2);
        verticalLayoutWidget_14->setObjectName(QStringLiteral("verticalLayoutWidget_14"));
        verticalLayoutWidget_14->setGeometry(QRect(12, 10, 1161, 561));
        verticalLayout_25 = new QVBoxLayout(verticalLayoutWidget_14);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 0, 0, 0);
        tableSensors = new QTableView(verticalLayoutWidget_14);
        tableSensors->setObjectName(QStringLiteral("tableSensors"));

        verticalLayout_25->addWidget(tableSensors);

        tableRawData = new QTableView(verticalLayoutWidget_14);
        tableRawData->setObjectName(QStringLiteral("tableRawData"));

        verticalLayout_25->addWidget(tableRawData);

        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        widget = new QWidget(tab_6);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(11, 18, 1160, 551));
        verticalLayout_24 = new QVBoxLayout(widget);
        verticalLayout_24->setObjectName(QStringLiteral("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(0, 0, 0, 0);
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setObjectName(QStringLiteral("verticalLayout_21"));
        tableConvertedData = new QTableView(widget);
        tableConvertedData->setObjectName(QStringLiteral("tableConvertedData"));

        verticalLayout_21->addWidget(tableConvertedData);


        verticalLayout_24->addLayout(verticalLayout_21);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QStringLiteral("horizontalLayout_15"));
        label_12 = new QLabel(widget);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_15->addWidget(label_12);

        comboExportDelim = new QComboBox(widget);
        comboExportDelim->setObjectName(QStringLiteral("comboExportDelim"));
        sizePolicy2.setHeightForWidth(comboExportDelim->sizePolicy().hasHeightForWidth());
        comboExportDelim->setSizePolicy(sizePolicy2);

        horizontalLayout_15->addWidget(comboExportDelim);

        horizontalSpacer_10 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);

        pushExportCSV = new QPushButton(widget);
        pushExportCSV->setObjectName(QStringLiteral("pushExportCSV"));
        pushExportCSV->setEnabled(false);
        sizePolicy2.setHeightForWidth(pushExportCSV->sizePolicy().hasHeightForWidth());
        pushExportCSV->setSizePolicy(sizePolicy2);
        pushExportCSV->setMinimumSize(QSize(101, 32));
        pushExportCSV->setMaximumSize(QSize(150, 32));

        horizontalLayout_15->addWidget(pushExportCSV);

        horizontalSpacer_9 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_9);

        pushAnalyseData = new QPushButton(widget);
        pushAnalyseData->setObjectName(QStringLiteral("pushAnalyseData"));
        pushAnalyseData->setEnabled(false);
        sizePolicy2.setHeightForWidth(pushAnalyseData->sizePolicy().hasHeightForWidth());
        pushAnalyseData->setSizePolicy(sizePolicy2);
        pushAnalyseData->setMinimumSize(QSize(101, 32));
        pushAnalyseData->setMaximumSize(QSize(150, 32));

        horizontalLayout_15->addWidget(pushAnalyseData);


        verticalLayout_24->addLayout(horizontalLayout_15);

        tabWidget->addTab(tab_6, QString());

        retranslateUi(windowConnectDatabase);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(windowConnectDatabase);
    } // setupUi

    void retranslateUi(QWidget *windowConnectDatabase)
    {
        windowConnectDatabase->setWindowTitle(QApplication::translate("windowConnectDatabase", "Import data via database", Q_NULLPTR));
        Text_startdate->setText(QApplication::translate("windowConnectDatabase", "Start date:", Q_NULLPTR));
        Text_enddate->setText(QApplication::translate("windowConnectDatabase", "End date:", Q_NULLPTR));
        Text_host->setText(QApplication::translate("windowConnectDatabase", "Host:", Q_NULLPTR));
        Text_database->setText(QApplication::translate("windowConnectDatabase", "Database:", Q_NULLPTR));
        db_host->setText(QApplication::translate("windowConnectDatabase", "127.0.0.1", Q_NULLPTR));
        db_name->setText(QApplication::translate("windowConnectDatabase", "hhsanalysis", Q_NULLPTR));
        date_start->setDisplayFormat(QApplication::translate("windowConnectDatabase", "dd-MM-yyyy", Q_NULLPTR));
        date_end->setDisplayFormat(QApplication::translate("windowConnectDatabase", "dd-MM-yyyy", Q_NULLPTR));
        Text_starttime->setText(QApplication::translate("windowConnectDatabase", "Start time:", Q_NULLPTR));
        Text_endtime->setText(QApplication::translate("windowConnectDatabase", "End time:", Q_NULLPTR));
        db_user->setText(QApplication::translate("windowConnectDatabase", "postgres", Q_NULLPTR));
        db_passw->setText(QApplication::translate("windowConnectDatabase", "geheim", Q_NULLPTR));
        Text_username_3->setText(QApplication::translate("windowConnectDatabase", "Username:", Q_NULLPTR));
        Text_password_3->setText(QApplication::translate("windowConnectDatabase", "Password:", Q_NULLPTR));
        Text_refreshrooms_3->setText(QApplication::translate("windowConnectDatabase", "Refresh rooms:", Q_NULLPTR));
        pushRefresh->setText(QApplication::translate("windowConnectDatabase", "Refresh", Q_NULLPTR));
        checkAirFlow->setText(QApplication::translate("windowConnectDatabase", "Fresh Air", Q_NULLPTR));
        checkValve->setText(QApplication::translate("windowConnectDatabase", "Air Valve Position", Q_NULLPTR));
        checkCO2->setText(QApplication::translate("windowConnectDatabase", "CO2", Q_NULLPTR));
        checkLightState->setText(QApplication::translate("windowConnectDatabase", "Light State", Q_NULLPTR));
        checkPres->setText(QApplication::translate("windowConnectDatabase", "Beweging", Q_NULLPTR));
        checkTempIr->setText(QApplication::translate("windowConnectDatabase", "Temp IR Ambient", Q_NULLPTR));
        checkTemp->setText(QApplication::translate("windowConnectDatabase", "Temp ?", Q_NULLPTR));
        Text_timeslot->setText(QApplication::translate("windowConnectDatabase", "Timeslot:", Q_NULLPTR));
        pushStart->setText(QApplication::translate("windowConnectDatabase", "Start", Q_NULLPTR));
        checkOutRain->setText(QApplication::translate("windowConnectDatabase", "Out Rain", Q_NULLPTR));
        checkOutAirDest->setText(QApplication::translate("windowConnectDatabase", "Out Air Dest", Q_NULLPTR));
        checkOutLight->setText(QApplication::translate("windowConnectDatabase", "Out Avg Light", Q_NULLPTR));
        checkOutTemp->setText(QApplication::translate("windowConnectDatabase", "Out Temp", Q_NULLPTR));
        checkOutAirSpeed->setText(QApplication::translate("windowConnectDatabase", "Out Air Speed", Q_NULLPTR));
        checkOutScherming->setText(QApplication::translate("windowConnectDatabase", "Out Schermering", Q_NULLPTR));
        checkOutHumidity->setText(QApplication::translate("windowConnectDatabase", "Out Humidity", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("windowConnectDatabase", "Data ophalen", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("windowConnectDatabase", "RAW data", Q_NULLPTR));
        label_12->setText(QApplication::translate("windowConnectDatabase", "Export met delimeter:", Q_NULLPTR));
        pushExportCSV->setText(QApplication::translate("windowConnectDatabase", "Export to CSV", Q_NULLPTR));
        pushAnalyseData->setText(QApplication::translate("windowConnectDatabase", "Analyse data", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("windowConnectDatabase", "Converted data", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class windowConnectDatabase: public Ui_windowConnectDatabase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWCONNECTDATABASE_H
