/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab_5;
    QGridLayout *gridLayout;
    QFrame *frame_2;
    QGridLayout *gridLayout_6;
    QLabel *label_32;
    QTextBrowser *configStatus;
    QTabWidget *tabWidget_2;
    QWidget *tab_6;
    QGridLayout *gridLayout_7;
    QGridLayout *gridLayout_2;
    QListWidget *listWidget;
    QPushButton *import_genie;
    QVBoxLayout *verticalLayout;
    QPushButton *next_analysedata;
    QWidget *tab_8;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_5;
    QPushButton *next_to_sort_nodes;
    QHBoxLayout *horizontalLayout;
    QPushButton *importRawCSV;
    QPushButton *importAnalyzeCSV;
    QPushButton *importDatabaseCSV;
    QHBoxLayout *horizontalLayout_7;
    QSpinBox *raw_spinbox_row;
    QSpinBox *raw_spinbox_col;
    QSpinBox *analyze_spin_row;
    QSpinBox *analyze_spin_col;
    QLabel *label_14;
    QLabel *label_13;
    QListWidget *listWidget_values;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_12;
    QWidget *tab_10;
    QGridLayout *gridLayout_11;
    QVBoxLayout *verticalLayout_3;
    QTreeWidget *treeWidget_symptom;
    QTreeWidget *treeWidget_results;
    QGridLayout *gridLayout_12;
    QPushButton *add_resultnodes;
    QPushButton *add_symptom;
    QListWidget *listWidget_2;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *remove_symptom;
    QPushButton *remove_result_node;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QPushButton *export_nodes;
    QPushButton *Import_nodes;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QPushButton *next_to_linkcolumn;
    QWidget *tab_9;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_8;
    QPushButton *savesymptoms;
    QCheckBox *checkBox_duplicate;
    QTableWidget *tableWidget_symptoms;
    QVBoxLayout *verticalLayout_10;
    QVBoxLayout *verticalLayout_11;
    QPushButton *importLinkedxml;
    QPushButton *ExportLinkedXml;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QPushButton *next_to_analyze_or_results;
    QWidget *tab_7;
    QGridLayout *gridLayout_14;
    QGridLayout *gridLayout_13;
    QTreeWidget *treeWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_value_boundary;
    QPushButton *pushButton_exportxml;
    QPushButton *pushButton_importxml;
    QVBoxLayout *verticalLayout_2;
    QComboBox *comboBox_values;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QPushButton *pushButton_boundary;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_sympt;
    QLabel *label_value;
    QFrame *frame_4;
    QFrame *frame;
    QPushButton *next_to_resultscolumn;
    QWidget *tab_12;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_18;
    QTreeWidget *treeWidget_finaleresultnodes;
    QListWidget *listWidget_3;
    QTreeWidget *treeWidget_finalesymps;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *frame_3;
    QGridLayout *gridLayout_17;
    QLabel *label_33;
    QPushButton *prepare_analyze;
    QTextBrowser *configStatus_analyze;
    QProgressBar *progressBar;
    QWidget *tab;
    QGridLayout *gridLayout_19;
    QTableView *tableView_resultdata;
    QPushButton *convertSmiledataToCSV;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1240, 707);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setMovable(false);
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        gridLayout = new QGridLayout(tab_5);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame_2 = new QFrame(tab_5);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setMinimumSize(QSize(0, 50));
        frame_2->setFrameShape(QFrame::NoFrame);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_2->setLineWidth(0);
        gridLayout_6 = new QGridLayout(frame_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_32 = new QLabel(frame_2);
        label_32->setObjectName(QStringLiteral("label_32"));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        label_32->setFont(font);
        label_32->setMargin(-8);

        gridLayout_6->addWidget(label_32, 1, 0, 1, 1);

        configStatus = new QTextBrowser(frame_2);
        configStatus->setObjectName(QStringLiteral("configStatus"));

        gridLayout_6->addWidget(configStatus, 0, 4, 3, 1);


        gridLayout->addWidget(frame_2, 1, 0, 1, 1);

        tabWidget_2 = new QTabWidget(tab_5);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        gridLayout_7 = new QGridLayout(tab_6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        listWidget = new QListWidget(tab_6);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        gridLayout_2->addWidget(listWidget, 1, 1, 1, 1);

        import_genie = new QPushButton(tab_6);
        import_genie->setObjectName(QStringLiteral("import_genie"));

        gridLayout_2->addWidget(import_genie, 0, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_2, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        next_analysedata = new QPushButton(tab_6);
        next_analysedata->setObjectName(QStringLiteral("next_analysedata"));
        QPalette palette;
        QBrush brush(QColor(177, 177, 177, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        next_analysedata->setPalette(palette);

        verticalLayout->addWidget(next_analysedata);


        gridLayout_7->addLayout(verticalLayout, 1, 2, 1, 1);

        tabWidget_2->addTab(tab_6, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        gridLayout_9 = new QGridLayout(tab_8);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        next_to_sort_nodes = new QPushButton(tab_8);
        next_to_sort_nodes->setObjectName(QStringLiteral("next_to_sort_nodes"));

        gridLayout_5->addWidget(next_to_sort_nodes, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        importRawCSV = new QPushButton(tab_8);
        importRawCSV->setObjectName(QStringLiteral("importRawCSV"));

        horizontalLayout->addWidget(importRawCSV);

        importAnalyzeCSV = new QPushButton(tab_8);
        importAnalyzeCSV->setObjectName(QStringLiteral("importAnalyzeCSV"));

        horizontalLayout->addWidget(importAnalyzeCSV);

        importDatabaseCSV = new QPushButton(tab_8);
        importDatabaseCSV->setObjectName(QStringLiteral("importDatabaseCSV"));

        horizontalLayout->addWidget(importDatabaseCSV);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        raw_spinbox_row = new QSpinBox(tab_8);
        raw_spinbox_row->setObjectName(QStringLiteral("raw_spinbox_row"));
        raw_spinbox_row->setValue(2);

        horizontalLayout_7->addWidget(raw_spinbox_row);

        raw_spinbox_col = new QSpinBox(tab_8);
        raw_spinbox_col->setObjectName(QStringLiteral("raw_spinbox_col"));
        raw_spinbox_col->setValue(2);

        horizontalLayout_7->addWidget(raw_spinbox_col);

        analyze_spin_row = new QSpinBox(tab_8);
        analyze_spin_row->setObjectName(QStringLiteral("analyze_spin_row"));
        analyze_spin_row->setValue(1);

        horizontalLayout_7->addWidget(analyze_spin_row);

        analyze_spin_col = new QSpinBox(tab_8);
        analyze_spin_col->setObjectName(QStringLiteral("analyze_spin_col"));
        analyze_spin_col->setValue(1);

        horizontalLayout_7->addWidget(analyze_spin_col);

        label_14 = new QLabel(tab_8);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_7->addWidget(label_14);

        label_13 = new QLabel(tab_8);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_7->addWidget(label_13);


        gridLayout_5->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        listWidget_values = new QListWidget(tab_8);
        listWidget_values->setObjectName(QStringLiteral("listWidget_values"));

        gridLayout_5->addWidget(listWidget_values, 4, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_4 = new QLabel(tab_8);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_8->addWidget(label_4);

        label_3 = new QLabel(tab_8);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_8->addWidget(label_3);

        label_2 = new QLabel(tab_8);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_8->addWidget(label_2);

        label = new QLabel(tab_8);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_8->addWidget(label);

        label_8 = new QLabel(tab_8);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        label_12 = new QLabel(tab_8);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_8->addWidget(label_12);


        gridLayout_5->addLayout(horizontalLayout_8, 1, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_5, 1, 1, 1, 1);

        tabWidget_2->addTab(tab_8, QString());
        tab_10 = new QWidget();
        tab_10->setObjectName(QStringLiteral("tab_10"));
        gridLayout_11 = new QGridLayout(tab_10);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        treeWidget_symptom = new QTreeWidget(tab_10);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget_symptom->setHeaderItem(__qtreewidgetitem);
        treeWidget_symptom->setObjectName(QStringLiteral("treeWidget_symptom"));

        verticalLayout_3->addWidget(treeWidget_symptom);

        treeWidget_results = new QTreeWidget(tab_10);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget_results->setHeaderItem(__qtreewidgetitem1);
        treeWidget_results->setObjectName(QStringLiteral("treeWidget_results"));

        verticalLayout_3->addWidget(treeWidget_results);


        gridLayout_11->addLayout(verticalLayout_3, 0, 2, 1, 1);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        add_resultnodes = new QPushButton(tab_10);
        add_resultnodes->setObjectName(QStringLiteral("add_resultnodes"));

        gridLayout_12->addWidget(add_resultnodes, 0, 0, 1, 1);

        add_symptom = new QPushButton(tab_10);
        add_symptom->setObjectName(QStringLiteral("add_symptom"));

        gridLayout_12->addWidget(add_symptom, 1, 0, 1, 1);

        listWidget_2 = new QListWidget(tab_10);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));

        gridLayout_12->addWidget(listWidget_2, 2, 0, 1, 1);


        gridLayout_11->addLayout(gridLayout_12, 0, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        remove_symptom = new QPushButton(tab_10);
        remove_symptom->setObjectName(QStringLiteral("remove_symptom"));

        verticalLayout_5->addWidget(remove_symptom);

        remove_result_node = new QPushButton(tab_10);
        remove_result_node->setObjectName(QStringLiteral("remove_result_node"));

        verticalLayout_5->addWidget(remove_result_node);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(tab_10);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);


        verticalLayout_7->addLayout(horizontalLayout_4);

        export_nodes = new QPushButton(tab_10);
        export_nodes->setObjectName(QStringLiteral("export_nodes"));

        verticalLayout_7->addWidget(export_nodes);

        Import_nodes = new QPushButton(tab_10);
        Import_nodes->setObjectName(QStringLiteral("Import_nodes"));

        verticalLayout_7->addWidget(Import_nodes);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_5 = new QLabel(tab_10);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_8->addWidget(label_5);


        verticalLayout_7->addLayout(verticalLayout_8);


        verticalLayout_5->addLayout(verticalLayout_7);


        verticalLayout_4->addLayout(verticalLayout_5);

        next_to_linkcolumn = new QPushButton(tab_10);
        next_to_linkcolumn->setObjectName(QStringLiteral("next_to_linkcolumn"));

        verticalLayout_4->addWidget(next_to_linkcolumn);


        gridLayout_11->addLayout(verticalLayout_4, 0, 6, 1, 1);

        tabWidget_2->addTab(tab_10, QString());
        tab_9 = new QWidget();
        tab_9->setObjectName(QStringLiteral("tab_9"));
        gridLayout_10 = new QGridLayout(tab_9);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        savesymptoms = new QPushButton(tab_9);
        savesymptoms->setObjectName(QStringLiteral("savesymptoms"));

        gridLayout_8->addWidget(savesymptoms, 0, 0, 1, 1);

        checkBox_duplicate = new QCheckBox(tab_9);
        checkBox_duplicate->setObjectName(QStringLiteral("checkBox_duplicate"));
        checkBox_duplicate->setEnabled(true);
        checkBox_duplicate->setChecked(true);
        checkBox_duplicate->setTristate(false);

        gridLayout_8->addWidget(checkBox_duplicate, 0, 1, 1, 1);

        tableWidget_symptoms = new QTableWidget(tab_9);
        if (tableWidget_symptoms->columnCount() < 2)
            tableWidget_symptoms->setColumnCount(2);
        tableWidget_symptoms->setObjectName(QStringLiteral("tableWidget_symptoms"));
        tableWidget_symptoms->setEnabled(true);
        tableWidget_symptoms->setFrameShape(QFrame::StyledPanel);
        tableWidget_symptoms->setFrameShadow(QFrame::Plain);
        tableWidget_symptoms->setLineWidth(2);
        tableWidget_symptoms->setShowGrid(false);
        tableWidget_symptoms->setRowCount(0);
        tableWidget_symptoms->setColumnCount(2);
        tableWidget_symptoms->horizontalHeader()->setDefaultSectionSize(106);

        gridLayout_8->addWidget(tableWidget_symptoms, 1, 0, 1, 1);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        importLinkedxml = new QPushButton(tab_9);
        importLinkedxml->setObjectName(QStringLiteral("importLinkedxml"));

        verticalLayout_11->addWidget(importLinkedxml);

        ExportLinkedXml = new QPushButton(tab_9);
        ExportLinkedXml->setObjectName(QStringLiteral("ExportLinkedXml"));

        verticalLayout_11->addWidget(ExportLinkedXml);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(tab_9);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);


        verticalLayout_11->addLayout(horizontalLayout_3);


        verticalLayout_10->addLayout(verticalLayout_11);

        next_to_analyze_or_results = new QPushButton(tab_9);
        next_to_analyze_or_results->setObjectName(QStringLiteral("next_to_analyze_or_results"));

        verticalLayout_10->addWidget(next_to_analyze_or_results);


        gridLayout_8->addLayout(verticalLayout_10, 1, 1, 1, 1);


        gridLayout_10->addLayout(gridLayout_8, 0, 0, 1, 1);

        tabWidget_2->addTab(tab_9, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        gridLayout_14 = new QGridLayout(tab_7);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QStringLiteral("gridLayout_14"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QStringLiteral("gridLayout_13"));
        treeWidget_2 = new QTreeWidget(tab_7);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QStringLiteral("1"));
        treeWidget_2->setHeaderItem(__qtreewidgetitem2);
        treeWidget_2->setObjectName(QStringLiteral("treeWidget_2"));

        gridLayout_13->addWidget(treeWidget_2, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_value_boundary = new QPushButton(tab_7);
        add_value_boundary->setObjectName(QStringLiteral("add_value_boundary"));

        horizontalLayout_2->addWidget(add_value_boundary);

        pushButton_exportxml = new QPushButton(tab_7);
        pushButton_exportxml->setObjectName(QStringLiteral("pushButton_exportxml"));

        horizontalLayout_2->addWidget(pushButton_exportxml);

        pushButton_importxml = new QPushButton(tab_7);
        pushButton_importxml->setObjectName(QStringLiteral("pushButton_importxml"));

        horizontalLayout_2->addWidget(pushButton_importxml);


        gridLayout_13->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        gridLayout_14->addLayout(gridLayout_13, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        comboBox_values = new QComboBox(tab_7);
        comboBox_values->setObjectName(QStringLiteral("comboBox_values"));

        verticalLayout_2->addWidget(comboBox_values);

        doubleSpinBox = new QDoubleSpinBox(tab_7);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));

        verticalLayout_2->addWidget(doubleSpinBox);

        doubleSpinBox_2 = new QDoubleSpinBox(tab_7);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));

        verticalLayout_2->addWidget(doubleSpinBox_2);

        pushButton_boundary = new QPushButton(tab_7);
        pushButton_boundary->setObjectName(QStringLiteral("pushButton_boundary"));

        verticalLayout_2->addWidget(pushButton_boundary);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_sympt = new QLabel(tab_7);
        label_sympt->setObjectName(QStringLiteral("label_sympt"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        label_sympt->setFont(font1);

        verticalLayout_6->addWidget(label_sympt);

        label_value = new QLabel(tab_7);
        label_value->setObjectName(QStringLiteral("label_value"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_value->setFont(font2);

        verticalLayout_6->addWidget(label_value);

        frame_4 = new QFrame(tab_7);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);

        verticalLayout_6->addWidget(frame_4);

        frame = new QFrame(tab_7);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        verticalLayout_6->addWidget(frame);


        verticalLayout_2->addLayout(verticalLayout_6);


        gridLayout_14->addLayout(verticalLayout_2, 0, 1, 1, 1);

        next_to_resultscolumn = new QPushButton(tab_7);
        next_to_resultscolumn->setObjectName(QStringLiteral("next_to_resultscolumn"));

        gridLayout_14->addWidget(next_to_resultscolumn, 0, 2, 1, 1);

        tabWidget_2->addTab(tab_7, QString());

        gridLayout->addWidget(tabWidget_2, 4, 0, 1, 1);

        tabWidget->addTab(tab_5, QString());
        tab_12 = new QWidget();
        tab_12->setObjectName(QStringLiteral("tab_12"));
        gridLayout_3 = new QGridLayout(tab_12);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_18 = new QGridLayout();
        gridLayout_18->setSpacing(6);
        gridLayout_18->setObjectName(QStringLiteral("gridLayout_18"));
        treeWidget_finaleresultnodes = new QTreeWidget(tab_12);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem();
        __qtreewidgetitem3->setText(0, QStringLiteral("1"));
        treeWidget_finaleresultnodes->setHeaderItem(__qtreewidgetitem3);
        treeWidget_finaleresultnodes->setObjectName(QStringLiteral("treeWidget_finaleresultnodes"));

        gridLayout_18->addWidget(treeWidget_finaleresultnodes, 1, 2, 1, 1);

        listWidget_3 = new QListWidget(tab_12);
        listWidget_3->setObjectName(QStringLiteral("listWidget_3"));

        gridLayout_18->addWidget(listWidget_3, 1, 0, 1, 1);

        treeWidget_finalesymps = new QTreeWidget(tab_12);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem();
        __qtreewidgetitem4->setText(0, QStringLiteral("1"));
        treeWidget_finalesymps->setHeaderItem(__qtreewidgetitem4);
        treeWidget_finalesymps->setObjectName(QStringLiteral("treeWidget_finalesymps"));

        gridLayout_18->addWidget(treeWidget_finalesymps, 1, 1, 1, 1);

        label_9 = new QLabel(tab_12);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font1);

        gridLayout_18->addWidget(label_9, 0, 0, 1, 1);

        label_10 = new QLabel(tab_12);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_18->addWidget(label_10, 0, 1, 1, 1);

        label_11 = new QLabel(tab_12);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_18->addWidget(label_11, 0, 2, 1, 1);


        gridLayout_3->addLayout(gridLayout_18, 1, 0, 1, 1);

        frame_3 = new QFrame(tab_12);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setMinimumSize(QSize(0, 50));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_3->setLineWidth(0);
        gridLayout_17 = new QGridLayout(frame_3);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QStringLiteral("gridLayout_17"));
        label_33 = new QLabel(frame_3);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setFont(font);
        label_33->setMargin(-8);

        gridLayout_17->addWidget(label_33, 1, 0, 1, 1);

        prepare_analyze = new QPushButton(frame_3);
        prepare_analyze->setObjectName(QStringLiteral("prepare_analyze"));

        gridLayout_17->addWidget(prepare_analyze, 2, 0, 1, 1);

        configStatus_analyze = new QTextBrowser(frame_3);
        configStatus_analyze->setObjectName(QStringLiteral("configStatus_analyze"));

        gridLayout_17->addWidget(configStatus_analyze, 0, 4, 5, 1);


        gridLayout_3->addWidget(frame_3, 0, 0, 1, 1);

        progressBar = new QProgressBar(tab_12);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout_3->addWidget(progressBar, 2, 0, 1, 1);

        tabWidget->addTab(tab_12, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_19 = new QGridLayout(tab);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QStringLiteral("gridLayout_19"));
        tableView_resultdata = new QTableView(tab);
        tableView_resultdata->setObjectName(QStringLiteral("tableView_resultdata"));

        gridLayout_19->addWidget(tableView_resultdata, 1, 0, 1, 1);

        convertSmiledataToCSV = new QPushButton(tab);
        convertSmiledataToCSV->setObjectName(QStringLiteral("convertSmiledataToCSV"));

        gridLayout_19->addWidget(convertSmiledataToCSV, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());

        gridLayout_4->addWidget(tabWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1240, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Smile App", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "                               Configuration section                        ", Q_NULLPTR));
        import_genie->setText(QApplication::translate("MainWindow", "Import GeNie model", Q_NULLPTR));
        next_analysedata->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("MainWindow", "GeNie model", Q_NULLPTR));
        next_to_sort_nodes->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        importRawCSV->setText(QApplication::translate("MainWindow", "Import raw values CSV", Q_NULLPTR));
        importAnalyzeCSV->setText(QApplication::translate("MainWindow", "Import rule values CSV", Q_NULLPTR));
        importDatabaseCSV->setText(QApplication::translate("MainWindow", "Import from database", Q_NULLPTR));
        label_14->setText(QString());
        label_13->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "Number of header rows", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Number of Date & time cols", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Number of header rows", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Number of Date & time cols", Q_NULLPTR));
        label_8->setText(QString());
        label_12->setText(QString());
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QApplication::translate("MainWindow", "Values", Q_NULLPTR));
        add_resultnodes->setText(QApplication::translate("MainWindow", "Add Resultnodes", Q_NULLPTR));
        add_symptom->setText(QApplication::translate("MainWindow", "Add Symptom", Q_NULLPTR));
        remove_symptom->setText(QApplication::translate("MainWindow", "Remove Symptom", Q_NULLPTR));
        remove_result_node->setText(QApplication::translate("MainWindow", "Remove result node", Q_NULLPTR));
        label_6->setText(QString());
        export_nodes->setText(QApplication::translate("MainWindow", "Export sorted nodes", Q_NULLPTR));
        Import_nodes->setText(QApplication::translate("MainWindow", "Import sorted nodes", Q_NULLPTR));
        label_5->setText(QString());
        next_to_linkcolumn->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_10), QApplication::translate("MainWindow", "Sort nodes", Q_NULLPTR));
        savesymptoms->setText(QApplication::translate("MainWindow", "Save Symptoms", Q_NULLPTR));
        checkBox_duplicate->setText(QApplication::translate("MainWindow", "Detect duplicate columns", Q_NULLPTR));
        importLinkedxml->setText(QApplication::translate("MainWindow", "Import linked Xml", Q_NULLPTR));
        ExportLinkedXml->setText(QApplication::translate("MainWindow", "Export linked Xml", Q_NULLPTR));
        label_7->setText(QString());
        next_to_analyze_or_results->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_9), QApplication::translate("MainWindow", "Link CSV column to GeNie node", Q_NULLPTR));
        add_value_boundary->setText(QApplication::translate("MainWindow", "Add values", Q_NULLPTR));
        pushButton_exportxml->setText(QApplication::translate("MainWindow", "Export XML", Q_NULLPTR));
        pushButton_importxml->setText(QApplication::translate("MainWindow", "                              Import XMl                        ", Q_NULLPTR));
        comboBox_values->clear();
        comboBox_values->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Constant", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Not Constant", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Equal", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Less than", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Greater than", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Between", Q_NULLPTR)
        );
        pushButton_boundary->setText(QApplication::translate("MainWindow", "                                         save values                                    ", Q_NULLPTR));
        label_sympt->setText(QApplication::translate("MainWindow", "Symptom", Q_NULLPTR));
        label_value->setText(QApplication::translate("MainWindow", "Evidence", Q_NULLPTR));
        next_to_resultscolumn->setText(QApplication::translate("MainWindow", "Next", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("MainWindow", "Analyze data config", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainWindow", "Config", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Genie nodes", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Symptom nodes", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "Result nodes", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "                            Analyze section                        ", Q_NULLPTR));
        prepare_analyze->setText(QApplication::translate("MainWindow", "Start analyzing", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_12), QApplication::translate("MainWindow", "Analyze", Q_NULLPTR));
        convertSmiledataToCSV->setText(QApplication::translate("MainWindow", "Export to CSV", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Result", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
