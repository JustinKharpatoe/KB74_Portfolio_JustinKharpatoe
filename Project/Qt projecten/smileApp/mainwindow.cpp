#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QtCore>
#include <QDateTime>
#include <QFileDialog>
#include <QFile>
#include <QtXml>
#include <iostream>
#include <QListWidgetItem>
#include <QList>
#include <QMap>
#include <QMapIterator>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QComboBox>
#include <iostream>
//#include <QtAlgorithms>
#include <algorithm>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    Window_ConnectDatabase = new windowConnectDatabase();
    ui->setupUi(this);
    //ui->tab_8->setEnabled(false);
    ui->tableWidget_symptoms->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_symptoms->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_symptoms->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_symptoms->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView_resultdata->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_resultdata->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_resultdata->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_resultdata->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // disable button and tabs
    ui->next_analysedata->setEnabled(false);
    ui->next_to_sort_nodes->setEnabled(false);
    ui->next_to_linkcolumn->setEnabled(false);
    ui->next_to_analyze_or_results->setEnabled(false);
    ui->next_to_resultscolumn->setEnabled(false);

    ui->pushButton_exportxml->setEnabled(false);
    ui->ExportLinkedXml->setEnabled(false);

    this->setEnabled_tab2(false);
    this->setEnabled_tab3(false);
    this->setEnabled_tab4(false);
    this->setEnabled_tab5(false);
    this->setEnabled_tab5_part2(false);
    this->setEnabled_tab6(false);

    //info log
    this->new_logConfig_entry("Please import a Genie file");
    this->new_logConfig_entry("Welcome to Smile analyzer");


    rawCSV=false;
    readyCSV=false;
    readyCSVDatabase=false;
    dataLogger = new Logger(0, "LogMain.txt");
}



MainWindow::~MainWindow()
{
    delete ui;
}

//////// new gui v2/////////
bool MainWindow::addChild(QTreeWidgetItem *nodeparent, QString name)
{
    ///this is for the QtreeWidget
    QTreeWidgetItem *childNode = new QTreeWidgetItem();
    childNode->setText(0,name);
    nodeparent->addChild(childNode);
}

QMap<QString,evidence*> MainWindow::getAllEvidence(QString name)
{
    QMap<QString,evidence*> list;
    for(unsigned int k=0;k<datamap[name].size();k++){
        list.insert(datamap[name][k], new evidence(datamap[name][k],k));
    }
    return list;
}

// Function Logconfig logs everything on display
void MainWindow::new_logConfig_entry(QString newline)
{
    textSmile = QTime::currentTime().toString() + "\t" + newline + "\n" + textSmile;
    ui->configStatus->setText(textSmile);
}

void MainWindow::new_logConfigAnalyze_entry(QString newline)
{
    textSmile = QTime::currentTime().toString() + "\t" + newline + "\n" + textSmile;
    ui->configStatus_analyze->setText(textSmile);

}


//enable ui and disable ui

void MainWindow::setEnabled_tab2(bool status)
{
    ui->importAnalyzeCSV->setEnabled(status);
    ui->importRawCSV->setEnabled(status);
    ui->importDatabaseCSV->setEnabled(status);
    ui->listWidget_values->setEnabled(status);
    ui->raw_spinbox_col->setEnabled(status);
    ui->raw_spinbox_row->setEnabled(status);
    ui->analyze_spin_col->setEnabled(status);
    ui->analyze_spin_row->setEnabled(status);
}

void MainWindow::setEnabled_tab3(bool status)
{
    ui->add_resultnodes->setEnabled(status);
    ui->add_symptom->setEnabled(status);
    ui->listWidget_2->setEnabled(status);
    ui->treeWidget_results->setEnabled(status);
    ui->treeWidget_symptom->setEnabled(status);
    ui->remove_result_node->setEnabled(status);
    ui->remove_symptom->setEnabled(status);
    ui->export_nodes->setEnabled(status);
    ui->Import_nodes->setEnabled(status);

}

void MainWindow::setEnabled_tab4(bool status)
{
    //ui->pushButton_clear->setEnabled(status);
    ui->savesymptoms->setEnabled(status);
    ui->tableWidget_symptoms->setEnabled(status);
    ui->importLinkedxml->setEnabled(status);
    //ui->ExportLinkedXml->setEnabled(status);

}

void MainWindow::setEnabled_tab5(bool status)
{
    ui->add_value_boundary->setEnabled(status);
    //ui->pushButton_exportxml->setEnabled(status);
    ui->pushButton_importxml->setEnabled(status);
    ui->treeWidget_2->setEnabled(status);

}

void MainWindow::setEnabled_tab5_part2(bool status)
{
    ui->doubleSpinBox->setEnabled(status);
    ui->doubleSpinBox_2->setEnabled(status);
    ui->comboBox_values->setEnabled(status);
    ui->pushButton_boundary->setEnabled(status);

}

void MainWindow::setEnabled_tab6(bool status)
{
//    ui->pushButton_resultnodes->setEnabled(status);
//    ui->pushButton_deleteresults->setEnabled(status);
//    ui->treeWidget_resultsfinale->setEnabled(status);

}

void MainWindow::resetAll()
{
    ui->listWidget->clear();
    ui->tableWidget_symptoms->clear();
    ui->treeWidget_symptom->clear();
    ui->treeWidget_results->clear();
    ui->treeWidget_2->clear();
    ui->listWidget_2->clear();
    ui->listWidget_values->clear();

    this->setEnabled_tab2(false);
    this->setEnabled_tab3(false);
    this->setEnabled_tab4(false);
    this->setEnabled_tab5(false);
    this->setEnabled_tab5_part2(false);
    this->setEnabled_tab6(false);
    ui->tabWidget_2->setCurrentWidget(ui->tab_6);

    ui->next_analysedata->setEnabled(false);
    ui->next_to_sort_nodes->setEnabled(false);
    ui->next_to_linkcolumn->setEnabled(false);
    ui->next_to_analyze_or_results->setEnabled(false);
    ui->next_to_resultscolumn->setEnabled(false);
}


void MainWindow::on_next_analysedata_clicked()
{
     ui->tabWidget_2->setCurrentWidget(ui->tab_8);
     this->setEnabled_tab2(true);

}

void MainWindow::on_next_to_sort_nodes_clicked()
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_10);
    this->setEnabled_tab3(true);

}

void MainWindow::on_next_to_linkcolumn_clicked()
{
    ui->tabWidget_2->setCurrentWidget(ui->tab_9);
    this->linkSymptomToNode();
    this->saveResultnode();
    this->setEnabled_tab4(true);

}

void MainWindow::on_next_to_analyze_or_results_clicked()
{
    if(rawCSV && (!readyCSV)){
        this->addSymptomstoWidget();
        ui->tabWidget_2->setCurrentWidget(ui->tab_7);
        this->setEnabled_tab5(true);
    }else{
       ui->tabWidget->setCurrentWidget(ui->tab_12);
    }

}

void MainWindow::on_next_to_resultscolumn_clicked()
{
   ui->tabWidget->setCurrentWidget(ui->tab_12);
}


void MainWindow::on_import_genie_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a .xdsl file"), "C://", ".xdsl files (*.xdsl))");

    // clear datamap when new file will add and clear listwidge
    datamap.clear();
    ui->listWidget->clear();

    if(importData.readSmileFile(filename,datamap)){

        QMapIterator<QString, vector<QString> > i(datamap);
        while (i.hasNext()) {
            i.next();
            ui->listWidget->addItem(i.key());
            ui->listWidget_2->addItem(i.key());
        }

     this->new_logConfig_entry("--------------------------");
     this->new_logConfig_entry("Smile Analyzer received Genie file correctly");
     ui->next_analysedata->setEnabled(true);
     this->new_logConfig_entry("--------------------------");
     this->new_logConfig_entry("Please click on Next");


    }else{

     this->new_logConfig_entry("--------------------------");
     this->new_logConfig_entry("Something when wrong, Please try again");


    }


}

void MainWindow::on_importRawCSV_clicked()
{
    rawCSV=true;
    readyCSV=false;
    readyCSVDatabase=false;

    vector<vector<QString> > colnames;
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a .csv file"), "C://", ".csv files (*.csv))");

     QColor clearColor( 255,255,255,255 );
     QPalette clearPalette( ui->raw_spinbox_row->palette() );
     clearPalette.setColor(QPalette::Active, QPalette::Base, clearColor);
     ui->raw_spinbox_row->setPalette(clearPalette);

     ui->listWidget_values->clear();
     ui->listWidget_3->clear();
     int spinboxRow = ui->raw_spinbox_row->value();
     int spinboxCol = ui->raw_spinbox_col->value();
     if(!spinboxRow){
         this->new_logConfig_entry("--------------------------");
         this->new_logConfig_entry("Row header can't be zero(0)");
         QColor myColor( 255,0,0,255 );
         QPalette myPalette( ui->raw_spinbox_row->palette() );
         myPalette.setColor(QPalette::Active, QPalette::Base, myColor);
         ui->raw_spinbox_row->setPalette(myPalette);
         return;
     }
    if(importData.readCsvFile(filename,",",spinboxRow,spinboxCol,true,false)){
        colnames = importData.getHeaderData();
        for(unsigned int k = 0; k <colnames[0].size(); k++ ){
                if(spinboxRow==1){
                    ui->listWidget_values->addItem(colnames[0][k]);
                    //this is in tab analyze
                    ui->listWidget_3->addItem(colnames[0][k]);
                }else{
                    ui->listWidget_values->addItem(colnames[0][k] +" - "+colnames[1][k]);
                    //this is in tab analyze
                    ui->listWidget_3->addItem(colnames[0][k] +" - "+colnames[1][k]);
                }
        }
        tableCol=colnames[0].size();
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Smile analyzer received Raw CSV correctly");
        ui->next_to_sort_nodes->setEnabled(true);
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Please click on Next");
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Something when wrong, Please try again");
    }
}

void MainWindow::on_importAnalyzeCSV_clicked()
{
    rawCSV=false;
    readyCSV=true;
    readyCSVDatabase=false;

    vector<vector<QString> > colnames;
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a .csv file"), "C://", ".csv files (*.csv))");

    QColor clearColor( 255,255,255,255 );
    QPalette clearPalette( ui->analyze_spin_row->palette() );
    clearPalette.setColor(QPalette::Active, QPalette::Base, clearColor);
    ui->analyze_spin_row->setPalette(clearPalette);

    ui->listWidget_values->clear();
    ui->listWidget_3->clear();
    int spinboxRow = ui->analyze_spin_row->value();
    int spinboxCol = ui->analyze_spin_col->value();
    if(!spinboxRow){
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Row header can't be zero(0)");
        QColor myColor( 255,0,0,255 );
        QPalette myPalette( ui->analyze_spin_row->palette() );
        myPalette.setColor(QPalette::Active, QPalette::Base, myColor);
        ui->analyze_spin_row->setPalette(myPalette);
        return;
    }

    if(importData.readCsvFile(filename,",",spinboxRow,spinboxCol,true,true)){
        colnames = importData.getHeaderData();
        for(unsigned int k = 0; k <colnames[0].size(); k++ ){

            if(spinboxRow==1){
                ui->listWidget_values->addItem(colnames[0][k]);
                //this is in tab analyze
                ui->listWidget_3->addItem(colnames[0][k]);
            }else{
                ui->listWidget_values->addItem(colnames[0][k] +" - "+colnames[1][k]);
                //this is in tab analyze
                ui->listWidget_3->addItem(colnames[0][k] +" - "+colnames[1][k]);
            }

        }
        tableCol=colnames[0].size();
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Smile analyzer received Analyze CSV correctly");
        ui->next_to_sort_nodes->setEnabled(true);
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Please click on Next");


    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Something when wrong, Please try again");
    }

    dataLogger->write(QString("Total data size: " + QString::number(importData.getTotalData().size())));
    dataLogger->write(QString("Total data size 0: " + QString::number(importData.getTotalData()[0].size())));
}


void MainWindow::on_importDatabaseCSV_clicked()
{
    if(Window_ConnectDatabase->exec()) {

        rawCSV=false;
        readyCSV=true;
        readyCSVDatabase=true;
        vector< vector<QString> > data,
                                  newData,
                                  //colnames,
                                  newColumn,
                                  timeData;
        vector< vector<float> > newSensorData;

        newColumn.push_back({"High_flow", "Low_flow", "Flow_frozen", "Flow_while_PIR_0", "High_CO2", "Low_CO2", "CO2_frozen", "CO2_neighbours_non_identical", "PIR_NaN"});

        convertData databaseToRule;

        QColor clearColor( 255,255,255,255 );
        QPalette clearPalette( ui->analyze_spin_row->palette() );
        clearPalette.setColor(QPalette::Active, QPalette::Base, clearColor);
        ui->analyze_spin_row->setPalette(clearPalette);

        ui->listWidget_values->clear();
        ui->listWidget_3->clear();


        data = Window_ConnectDatabase->getDatabaseData();

        dataLogger->write("Starting readCsvDatabase");
        if(importData.readCsvDatabase(data, 2, 2, true))
        {
            //colnames = importData.getHeaderData();
            //newData = databaseToRule.convertDataDatabase(importData.getTotalData(), importData.getHeaderData()[0], newColumn, Window_ConnectDatabase->getTimeSlot());
            newSensorData = databaseToRule.convertDataDatabase(this->transposeData(importData.getSensorData()), importData.getHeaderData()[0], newColumn, Window_ConnectDatabase->getTimeSlot());
            newData = databaseToRule.convertDataDatabase(this->transposeData(importData.getTotalData()), importData.getHeaderData()[0], newColumn, Window_ConnectDatabase->getTimeSlot());
            if(newSensorData.empty() || newData.empty())
            {
                /*QMessageBox* warning = new QMessageBox();
                warning->warning(0, "Warning!", "Vector is leeg!");
                delete warning;*/
                return;
            }

            newColumn[0].insert(newColumn[0].begin(), QString("Tijd"));                 // Plaats: begin + 1
            newColumn[0].insert(newColumn[0].begin(), QString("Datum en tijd (uur)"));  // Plaats: begin
            for(unsigned int k = 0; k < newColumn[0].size(); k++ )
            {
                ui->listWidget_values->addItem(newColumn[0][k]);
                //this is in tab analyze
                ui->listWidget_3->addItem(newColumn[0][k]);
            }
            tableCol=newColumn[0].size();

            this->new_logConfig_entry("Data recieved and converted succesfully");

            importData.setTotalData(newData);
            importData.setSensorData(newSensorData);
            importData.setHeaderData(newColumn);
//            timeData = importData.getTimeData();
//            timeData.erase(timeData.begin()+1);
//            importData.setTimeData(timeData);

            QMessageBox* saveRuleCSV = new QMessageBox("Save new rule CSV", "De rule values opslaan?", QMessageBox::Question,
                                                                                                       QMessageBox::Yes | QMessageBox::Default,
                                                                                                       QMessageBox::No | QMessageBox::Escape,
                                                                                                       QMessageBox::NoButton);
            if(saveRuleCSV->exec() == QMessageBox::Yes)
            {
                QString filename = QFileDialog::getSaveFileName(0, QObject::tr("Selecteer een .csv bestand om de rule values op te slaan."), ("C://"), QObject::tr(".csv files (*.csv)"));
                if(!(exportData.saveDataBaseCsv(this->transposeData(importData.getSensorData()), importData.getHeaderData(), importData.getTimeData(), filename, QString(";"))))
                {
                    dataLogger->write(QString("Rule values van database data kunnen niet worden opgeslagen in een CSV."));
                    saveRuleCSV->warning(0, "Warning!", "Kan CSV niet opslaan!", QMessageBox::Ok);
                }
            }
            delete saveRuleCSV;

            ui->next_to_sort_nodes->setEnabled(true);
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Please click on Next");
        }
    }
    else {
        dataLogger->write(QString("windowConnectDatabase kan niet worden opgestart."));
        this->new_logConfig_entry("De database connectie window kan niet worden opgestart");
    }

    this->new_logConfig_entry("--------------------------");
}


void MainWindow::on_add_symptom_clicked()
{
    ////// add Symptom nodes//////
    QListWidgetItem *currentdata = ui->listWidget_2->currentItem();
    if(currentdata != NULL){
        ui->treeWidget_symptom->setColumnCount(1);
        ui->treeWidget_finalesymps->setColumnCount(1);

        QTreeWidgetItem *resultnode = new QTreeWidgetItem(ui->treeWidget_symptom);
        QTreeWidgetItem *sympsfinalenode = new QTreeWidgetItem(ui->treeWidget_finalesymps);
        resultnode->setText(0,currentdata->text());
        sympsfinalenode->setText(0,currentdata->text());

        if(datamap.contains(currentdata->text()) && datamap[currentdata->text()].size()){
            for(unsigned int k =0; k<datamap[currentdata->text()].size();k++){
                addChild(resultnode,datamap[currentdata->text()][k]);
                addChild(sympsfinalenode,datamap[currentdata->text()][k]);
            }
             currentdata->~QListWidgetItem();
             if(ui->treeWidget_symptom->topLevelItemCount() && ui->treeWidget_results->topLevelItemCount()){
                 ui->next_to_linkcolumn->setEnabled(true);
             }
            ui->treeWidget_symptom->addTopLevelItem(resultnode);
            ui->treeWidget_finalesymps->addTopLevelItem(resultnode);

            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Added Symptom node");
        }else{
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Something when wrong, Please try again");
        }
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
        return;

    }

}

void MainWindow::on_add_resultnodes_clicked()
{
    ////// add result nodes//////
    QListWidgetItem *currentdata = ui->listWidget_2->currentItem();
    //currentdata->setHidden(true);
    if(currentdata != NULL){
    ui->treeWidget_results->setColumnCount(1);
    ui->treeWidget_finaleresultnodes->setColumnCount(1);

    QTreeWidgetItem *resultnode = new QTreeWidgetItem(ui->treeWidget_results);
     QTreeWidgetItem *resultfinalenode = new QTreeWidgetItem(ui->treeWidget_finaleresultnodes);
    resultnode->setText(0,currentdata->text());
    resultfinalenode->setText(0,currentdata->text());
    if(datamap.contains(currentdata->text()) && datamap[currentdata->text()].size()){
        for(unsigned int k =0; k<datamap[currentdata->text()].size();k++){
            addChild(resultnode,datamap[currentdata->text()][k]);
            addChild(resultfinalenode,datamap[currentdata->text()][k]);
        }
        currentdata->~QListWidgetItem();
        if(ui->treeWidget_symptom->topLevelItemCount()&& ui->treeWidget_results->topLevelItemCount()){
            ui->next_to_linkcolumn->setEnabled(true);
        }
        ui->treeWidget_results->addTopLevelItem(resultnode);
        ui->treeWidget_results->addTopLevelItem(resultfinalenode);
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Added Result node");
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Something when wrong, Please try again");
    }
   }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
        return;
    }
}

void MainWindow::on_remove_symptom_clicked()
{
    QTreeWidgetItem *currentdata = ui->treeWidget_symptom->currentItem();
    if(currentdata != NULL){
        if(currentdata->childCount()){
            ui->listWidget_2->addItem(currentdata->text(0));
            currentdata->~QTreeWidgetItem();
        }else{
            ui->listWidget_2->addItem(currentdata->parent()->text(0));
            currentdata->parent()->~QTreeWidgetItem();
        }
        ui->next_to_linkcolumn->setEnabled(false);
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
        return;
    }
}

void MainWindow::on_remove_result_node_clicked()
{
    QTreeWidgetItem *currentdata = ui->treeWidget_results->currentItem();
    if(currentdata != NULL){
        if(currentdata->childCount()){
            ui->listWidget_2->addItem(currentdata->text(0));
            currentdata->~QTreeWidgetItem();
        }else{
            ui->listWidget_2->addItem(currentdata->parent()->text(0));
            currentdata->parent()->~QTreeWidgetItem();
        }
        ui->next_to_linkcolumn->setEnabled(false);
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
        return;
    }
}

void MainWindow::on_Import_nodes_clicked()
{
    if(!ui->treeWidget_symptom->topLevelItemCount() && !ui->treeWidget_results->topLevelItemCount()){
        QString filename = QFileDialog::getOpenFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");
        QMap<QString,int> sortedsymps;
        QMap<QString,int> sortedresults;
        importData.readXmlSortedNodes(filename,sortedsymps,sortedresults);
        // Compare Xmlnodes and add Evidence values to Sympnodes
        if(!sortedresults.empty()|| !sortedsymps.empty()){
            int totalNodes= ui->listWidget_2->count();
            vector<QString> containNames;
            for(int c = 0; c<totalNodes;c++){
                QListWidgetItem *currentdata = ui->listWidget_2->item(c);
                QString nameNode= currentdata->text();
                //int countchild= currentdata->childCount();
                bool fond =false;
                QMap<QString,int>::iterator i;
                for (i = sortedsymps.begin(); i != sortedsymps.end(); ++i){
                    if(!nameNode.compare(i.key())){
                        ui->treeWidget_symptom->setColumnCount(1);
                        ui->treeWidget_finalesymps->setColumnCount(1);

                        QTreeWidgetItem *resultnode = new QTreeWidgetItem(ui->treeWidget_symptom);
                        QTreeWidgetItem *sympsfinalenode = new QTreeWidgetItem(ui->treeWidget_finalesymps);
                        resultnode->setText(0,currentdata->text());
                        sympsfinalenode->setText(0,currentdata->text());
                        containNames.push_back(nameNode);
                        if(datamap.contains(currentdata->text()) && datamap[currentdata->text()].size()==i.value()){
                            for(unsigned int k =0; k<datamap[currentdata->text()].size();k++){
                                addChild(resultnode,datamap[currentdata->text()][k]);
                                addChild(sympsfinalenode,datamap[currentdata->text()][k]);
                            }

                            if(!ui->listWidget_2->count()){
                                ui->next_to_linkcolumn->setEnabled(true);
                            }
                            fond=true;
                            ui->treeWidget_symptom->addTopLevelItem(resultnode);
                            ui->treeWidget_finalesymps->addTopLevelItem(resultnode);

                            this->new_logConfig_entry("--------------------------");
                            this->new_logConfig_entry("Added Symptom node");
                        }
                    }
                }
                if(!fond){
                    QMap<QString,int>::iterator n;
                    for(n=sortedresults.begin(); n!=sortedresults.end();++n){
                        if(!nameNode.compare(n.key())){
                            ui->treeWidget_results->setColumnCount(1);
                            ui->treeWidget_finaleresultnodes->setColumnCount(1);

                            QTreeWidgetItem *resultnode2 = new QTreeWidgetItem(ui->treeWidget_results);
                            QTreeWidgetItem *resultfinalenode2 = new QTreeWidgetItem(ui->treeWidget_finaleresultnodes);
                            resultnode2->setText(0,currentdata->text());
                            resultfinalenode2->setText(0,currentdata->text());
                            containNames.push_back(nameNode);
                            if(datamap.contains(currentdata->text()) && datamap[currentdata->text()].size()==n.value()){
                                for(unsigned int k =0; k<datamap[currentdata->text()].size();k++){
                                    addChild(resultnode2,datamap[currentdata->text()][k]);
                                    addChild(resultfinalenode2,datamap[currentdata->text()][k]);
                                }

                                if(!ui->listWidget_2->count()){
                                    ui->next_to_linkcolumn->setEnabled(true);
                                }
                                ui->treeWidget_results->addTopLevelItem(resultnode2);
                                ui->treeWidget_results->addTopLevelItem(resultfinalenode2);
                                this->new_logConfig_entry("--------------------------");
                                this->new_logConfig_entry("Added Result node");
                            }else{
                                this->new_logConfig_entry("--------------------------");
                                this->new_logConfig_entry("Something when wrong, Please try again");
                            }

                        }

                    }
                }
            }
            for(unsigned int c = 0; c<containNames.size();c++){

                for(int t=0;t<ui->listWidget_2->count();t++){
                    QListWidgetItem *current = ui->listWidget_2->item(t);
                    if(!current->text().compare(containNames[c])){
                        current->~QListWidgetItem();
                        break;
                    }
                }
            }
            if(!ui->listWidget_2->count()){
                ui->next_to_linkcolumn->setEnabled(true);
            }

        }else{
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("No Sorted nodes found!");
        }
    }

}

void MainWindow::on_export_nodes_clicked()
{
    if(!ui->listWidget_2->count()){
        QString filename = QFileDialog::getSaveFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");
        QDomDocument smileXml;
        QFile f(filename);
        if (!f.open(QIODevice::ReadOnly )){
            if ( f.open( QIODevice::WriteOnly )){
                QTextStream TextStream(&f);
                TextStream << "<?xml version='1.0'?><smilenodes></smilenodes>" ;
                this->new_logConfig_entry("--------------------------");
                this->new_logConfig_entry("No XML file!");
                f.close();
            }else{
                return;
            }
        }
        else{
            f.close();
        }
        if (!f.open(QIODevice::ReadWrite )){
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("No XML file!");
        }else{
            smileXml.setContent(&f);
            f.close();

            QDomDocument xmlNew;
            QString insert;
            int totalsympsItems= ui->treeWidget_symptom->topLevelItemCount();
            QDomElement symptom = xmlNew.createElement(QString("symptomnodes"));
            for(int k=0;k<totalsympsItems;k++){
                QTreeWidgetItem *currentdata = ui->treeWidget_symptom->topLevelItem(k);

                QDomElement symptomElement;
                symptomElement = xmlNew.createElement(QString("symptom"));
                symptomElement.setAttribute("name",currentdata->text(0));
                symptomElement.setAttribute("child",currentdata->childCount());
                symptom.appendChild( symptomElement);
            }

            int totalresultsItems= ui->treeWidget_results->topLevelItemCount();
            QDomElement result = xmlNew.createElement(QString("resultnodes"));
            for(int k=0;k<totalresultsItems;k++){
                QTreeWidgetItem *currentdata = ui->treeWidget_results->topLevelItem(k);

                QDomElement resultElement;
                resultElement = xmlNew.createElement(QString("result"));
                resultElement.setAttribute("name",currentdata->text(0));
                resultElement.setAttribute("child",currentdata->childCount());
                result.appendChild( resultElement);
            }
            QDomElement root=smileXml.documentElement();
            root.appendChild(symptom);
            root.appendChild(result);

            QFile File(filename);
            if ( File.open( QIODevice::WriteOnly ) ){
                QTextStream TextStream(&File);
                TextStream <<smileXml.toString();
                File.close();
                this->new_logConfig_entry("--------------------------");
                this->new_logConfig_entry("Process is done");
                this->new_logConfig_entry("Xml is saved");
            }
        }

    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
    }
}

void MainWindow::linkSymptomToNode()
{
    int totalItems= ui->treeWidget_symptom->topLevelItemCount();
    ui->tableWidget_symptoms->removeColumn(0);
    ui->tableWidget_symptoms->removeColumn(1);
    int newRow=0;
    ui->tableWidget_symptoms->setRowCount(0);
    for(int t=0;t< totalItems;t++){
        QMap<QString, int > colwithID;
        vector<vector<QString> > colnames;
        QTreeWidgetItem *currentdata = ui->treeWidget_symptom->topLevelItem(t);

        ui->tableWidget_symptoms->setColumnCount(2);
        QTableWidgetItem *tet = new QTableWidgetItem(currentdata->text(0));
        QComboBox *dropdown= new QComboBox(ui->tableWidget_symptoms);
        colnames = importData.getHeaderData();
        if(rawCSV && (!readyCSV)){
            for(unsigned int k = 2; k <colnames[0].size(); k++ ){
                dropdown->addItem(colnames[0][k] +" - "+colnames[1][k]);
            }
        }else{
            if(readyCSVDatabase) {
                for(unsigned int k = 0; k <colnames[0].size(); k++ ){
                    dropdown->addItem(colnames[0][k]);
                }
            } else {
                for(unsigned int k = 1; k <colnames[0].size(); k++ ){
                    dropdown->addItem(colnames[0][k]);
                }
            }
        }

       //int newRow = ui->tableWidget_symptoms->rowCount();
       ui->tableWidget_symptoms->insertRow(newRow);
       ui->tableWidget_symptoms->setItem(newRow,0, tet);
       ui->tableWidget_symptoms->setCellWidget(newRow,1,dropdown);
       ui->tableWidget_symptoms->resizeColumnsToContents();
       newRow++;

    }
}

void MainWindow::saveResultnode()
{
    for(int k=0; k < ui->treeWidget_results->topLevelItemCount();k++){
        QTreeWidgetItem *result =  ui->treeWidget_results->topLevelItem(k);
        resultsNodemap.insert(result->text(0),datamap.value(result->text(0)));
    }

}

void MainWindow::addSymptomstoWidget()
{

    int totalItems= ui->treeWidget_symptom->topLevelItemCount();
    for(int t=0;t< totalItems;t++){

        QTreeWidgetItem *currentdata = ui->treeWidget_symptom->topLevelItem(t);
        ui->treeWidget_2->setColumnCount(1);

        QTreeWidgetItem *resultnode = new QTreeWidgetItem(ui->treeWidget_2);
        resultnode->setText(0,currentdata->text(0));
        if(datamap.contains(currentdata->text(0)) && datamap[currentdata->text(0)].size()){
            for(unsigned int k =0; k<datamap[currentdata->text(0)].size();k++){
                addChild(resultnode,datamap[currentdata->text(0)][k]);
            }
            ui->treeWidget_2->addTopLevelItem(resultnode);
        }

    }

    greenCount= 0;
    totalchilds=this->allChildHasValues();
}

void MainWindow::on_importLinkedxml_clicked()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");
    QMap<QString,QString> linkedNodes;
    importData.readXmllinkedNodes(filename,linkedNodes);
    QComboBox *DataRate;

    for(int k =0; k < ui->tableWidget_symptoms->rowCount();k++){
        QMap<QString,QString>::iterator i;
        for (i = linkedNodes.begin(); i != linkedNodes.end(); ++i){
            QString test1= ui->tableWidget_symptoms->item(k,0)->text();
            QString test2 =i.key();
            if(!(ui->tableWidget_symptoms->item(k,0)->text().compare(i.key()))){
                QWidget *Widget =ui->tableWidget_symptoms->cellWidget(k,1);
                DataRate= qobject_cast<QComboBox*>(Widget);
                for(int c=0; c<DataRate->count();c++){
                    DataRate->setCurrentIndex(c);
                    QString linkedValue =i.value();
                    linkedValue.replace("\r","");
                    QString comboxText= DataRate->currentText();
                    comboxText.replace("\r","");
                    if(!(linkedValue.compare(comboxText))){
                        DataRate->setStyleSheet("QComboBox {background-color: green; color:white;}");
                        break;
                    }
                }
            }
        }
    }
    this->new_logConfig_entry("--------------------------");
    this->new_logConfig_entry("Imported Xml succesfull");
}

void MainWindow::on_ExportLinkedXml_clicked()
{

    if(!ui->listWidget_2->count()){
        QString filename = QFileDialog::getSaveFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");
        QDomDocument smileXml;
        QFile f(filename);
        if (!f.open(QIODevice::ReadOnly )){
            if ( f.open( QIODevice::WriteOnly )){
                QTextStream TextStream(&f);
                TextStream << "<?xml version='1.0'?><smilenodes></smilenodes>" ;
                f.close();
            }else{
                return;
            }
        }
        else{
            f.close();
        }
        if (!f.open(QIODevice::ReadWrite )){
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("No XML file!");
        }else{
            smileXml.setContent(&f);
            f.close();

            QDomDocument xmlNew;
            QString insert;
             QComboBox *DataRate;

            int totalsympsItems= ui->tableWidget_symptoms->rowCount();
            QDomElement symptom = xmlNew.createElement(QString("symptomnodes"));
            for(int k=0;k<totalsympsItems;k++){

                QWidget *Widget =ui->tableWidget_symptoms->cellWidget(k,1);
                DataRate= qobject_cast<QComboBox*>(Widget);
                QDomElement symptomElement;
                symptomElement = xmlNew.createElement(QString("symptom"));
                symptomElement.setAttribute("name",ui->tableWidget_symptoms->item(k,0)->text());
                QString comboboxtext =DataRate->currentText();
                comboboxtext.replace("\r","");
                symptomElement.setAttribute("linktocol",comboboxtext);
                symptom.appendChild( symptomElement);
            }

            QDomElement root=smileXml.documentElement();
            root.appendChild(symptom);

            QFile File(filename);
            if ( File.open( QIODevice::WriteOnly ) ){
                QTextStream TextStream(&File);
                TextStream <<smileXml.toString();
                File.close();
                this->new_logConfig_entry("--------------------------");
                this->new_logConfig_entry("Process is done");
                this->new_logConfig_entry("Xml is saved");
            }
        }
    }else{
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("List is empty!");
    }
}


void MainWindow::on_savesymptoms_clicked()
{

    QMap<int,QString> symps;
    QComboBox *DataRate;
    vector<evidence> evidenceList;
    QMap<QString,evidence*> evidmapList;

    ui->tableWidget_symptoms->insertColumn(2);
    int rowtotal= ui->tableWidget_symptoms->rowCount();
    int added=0;
   if(ui->checkBox_duplicate->isChecked()){
     for(int k =0; k < ui->tableWidget_symptoms->rowCount();k++){
        QWidget *Widget =ui->tableWidget_symptoms->cellWidget(k,1);
        DataRate= qobject_cast<QComboBox*>(Widget);
        QTableWidgetItem *state = new QTableWidgetItem("Added");

        if(!symps.contains(DataRate->currentIndex())){
            evidmapList= getAllEvidence(ui->tableWidget_symptoms->item(k,0)->text());
            SympsNodesMap.insert(ui->tableWidget_symptoms->item(k,0)->text(),new symptom(evidmapList,ui->tableWidget_symptoms->item(k,0)->text(),DataRate->currentIndex()));
            ui->tableWidget_symptoms->setItem(k,2, state);
            ui->tableWidget_symptoms->item(k,2)->setBackground(Qt::green);
            QTableWidgetItem *name =ui->tableWidget_symptoms->item(k,0);
            symps[DataRate->currentIndex()]= name->text();
            added++;
        }else{
            state->setText("Duplicate");
            ui->tableWidget_symptoms->setItem(k,2, state);
            ui->tableWidget_symptoms->item(k,2)->setBackground(Qt::red);
        }
    }

    if(added==rowtotal){
         ui->ExportLinkedXml->setEnabled(true);
        ui->next_to_analyze_or_results->setEnabled(true);
    }
     }else{
       for(int k =0; k < ui->tableWidget_symptoms->rowCount();k++){
           QWidget *Widget2 =ui->tableWidget_symptoms->cellWidget(k,1);
           DataRate= qobject_cast<QComboBox*>(Widget2);
           QTableWidgetItem *state2 = new QTableWidgetItem("Added");
           if(!symps.contains(DataRate->currentIndex())){
               evidmapList= getAllEvidence(ui->tableWidget_symptoms->item(k,0)->text());
               SympsNodesMap.insert(ui->tableWidget_symptoms->item(k,0)->text(),new symptom(evidmapList,ui->tableWidget_symptoms->item(k,0)->text(),DataRate->currentIndex()));
               ui->tableWidget_symptoms->setItem(k,2, state2);
               ui->tableWidget_symptoms->item(k,2)->setBackground(Qt::green);
               QTableWidgetItem *name =ui->tableWidget_symptoms->item(k,0);
               symps[DataRate->currentIndex()]= name->text();

           }else{
               evidmapList= getAllEvidence(ui->tableWidget_symptoms->item(k,0)->text());
               SympsNodesMap.insert(ui->tableWidget_symptoms->item(k,0)->text(),new symptom(evidmapList,ui->tableWidget_symptoms->item(k,0)->text(),DataRate->currentIndex()));
               QTableWidgetItem *name =ui->tableWidget_symptoms->item(k,0);
               symps[DataRate->currentIndex()]= name->text();
               state2->setText("Duplicate");
               ui->tableWidget_symptoms->setItem(k,2, state2);
               ui->tableWidget_symptoms->item(k,2)->setBackground(Qt::yellow);
           }
       }
           ui->ExportLinkedXml->setEnabled(true);
           ui->next_to_analyze_or_results->setEnabled(true);
   }

}



void MainWindow::on_add_value_boundary_clicked()
{
    if(!ui->treeWidget_2->currentItem()->parent()){
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry("Can't add value to Symptom. Please select a evidence of the Symptom");

    }else{
        this->setEnabled_tab5_part2(true);
        QTreeWidgetItem *parentNode = ui->treeWidget_2->currentItem()->parent();
        QString parentText =  parentNode->text(0);
        symptom *sympParent = SympsNodesMap.value(parentText);
        QMap<QString,evidence*> SympsEvidence = sympParent->getEvidencelist();
        ui->label_sympt->setText(parentText);
        ui->label_value->setText(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getName());
        ui->doubleSpinBox->setMaximum(5000);
        ui->doubleSpinBox_2->setMaximum(5000);
        if(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getValuesSize()){
            if(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getop()!=5){
                ui->comboBox_values->setCurrentIndex(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getop());
                int currentOp = SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getop();
                if(currentOp ==0 || currentOp ==1){
                    ui->doubleSpinBox_2->setValue(0);
                    ui->doubleSpinBox_2->setEnabled(false);
                    ui->doubleSpinBox->setValue(0);
                    ui->doubleSpinBox->setEnabled(false);
                }else{
                    ui->doubleSpinBox->setValue(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getOnevalue(0));
                    ui->doubleSpinBox_2->setValue(0);
                    ui->doubleSpinBox_2->setEnabled(false);
                }

            }else{
                ui->comboBox_values->setCurrentIndex(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getop());
                ui->doubleSpinBox->setValue(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getOnevalue(0));
                ui->doubleSpinBox_2->setValue(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getOnevalue(1));
            }
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Evidence: "+ parentText +" "+ QString::number(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getIndex()) + " Name " +SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getName());

        }else{
            ui->comboBox_values->setCurrentIndex(0);
            ui->doubleSpinBox->setValue(0);
            ui->doubleSpinBox_2->setValue(0);
            ui->doubleSpinBox->setEnabled(false);
            ui->doubleSpinBox_2->setEnabled(false);
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Evidence: "+ parentText +" "+ QString::number(SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getIndex()) + " Name: " +SympsEvidence[ui->treeWidget_2->currentItem()->text(0)]->getName());

        }

    }

}

void MainWindow::on_pushButton_boundary_clicked()
{
    QString sympName =ui->label_sympt->text();
    QString evidenceName = ui->label_value->text();
    QMap<QString,evidence*> SympsEvidence = SympsNodesMap[sympName]->getEvidencelist();
    QVector<float> values;

    // van hoog naar laag
    //constant
    //niet constant
    //gelijk aan
    //kleiner dan
    //groter dan
    //tussen

    if(ui->comboBox_values->currentIndex() == 5){
        values.push_back((float) ui->doubleSpinBox->value());
        values.push_back((float) ui->doubleSpinBox_2->value());
    }else{
        values.push_back((float) ui->doubleSpinBox->value());
    }

    ui->comboBox_values->currentIndex();
    SympsEvidence[evidenceName]->setvalues(values);
    SympsEvidence[evidenceName]->setop(ui->comboBox_values->currentIndex());
    QColor test = ui->treeWidget_2->currentItem()->backgroundColor(0);

    if(!QString::compare(test.name(),"#000000", Qt::CaseInsensitive)){

        ui->treeWidget_2->currentItem()->setBackgroundColor(0,Qt::green);
        greenCount++;
    }
    if(greenCount==totalchilds){
        ui->pushButton_exportxml->setEnabled(true);

    }
    this->new_logConfig_entry("--------------------------");
    this->new_logConfig_entry("Saved value");
    this->setEnabled_tab5_part2(false);
    SympsEvidence.clear();
    values.clear();
}

void MainWindow::on_pushButton_exportxml_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");

    QDomDocument smileXml;
    //check als alles is ingevuld van die symptoms
    // if not dan moet de gebruiker alles invullen
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly )){
        if ( f.open( QIODevice::WriteOnly )){
            QTextStream TextStream(&f);
            TextStream << "<?xml version='1.0'?><smilenodes></smilenodes>" ;
            f.close();
            //this->new_logExpert_entry("New XML created");
        }else{
            // this->new_logExpert_entry("Unable to create XML file. Is target read-only?");
            return;
        }
    }
    else{
        f.close();
    }

    if (!f.open(QIODevice::ReadWrite )){
        //std::cerr << "Error while loading file" << std::endl;
        //this->new_logExpert_entry("No XML file");
    }else{
        smileXml.setContent(&f);
        f.close();

        QDomDocument xmlNew;
        QString insert;
        QMap<QString,symptom*>::iterator i;
        for (i = SympsNodesMap.begin(); i != SympsNodesMap.end(); ++i){
            QTreeWidgetItem *symps = new QTreeWidgetItem(ui->treeWidget_2);
            // symps->setText(0,i.value()->getName());
            QDomElement symptom = xmlNew.createElement(QString("symptom"));
            symptom.setAttribute("name",i.value()->getName());
            QMap<QString,evidence*> SympsEvidence =i.value()->getEvidencelist();
            QDomElement evidenceElement;
            QMap<QString, evidence*>::iterator k;
            for (k = SympsEvidence.begin(); k != SympsEvidence.end(); ++k){
                //addChild(symps,k.value()->getName());
                evidenceElement = xmlNew.createElement(QString("evidence"));

                if(k.value()->getop()==5){
                    evidenceElement.setAttribute("value1",k.value()->getOnevalue(0));
                    evidenceElement.setAttribute("value2",k.value()->getOnevalue(1));
                }else{
                    evidenceElement.setAttribute("value1",k.value()->getOnevalue(0));
                }
                evidenceElement.setAttribute("smileindex",k.value()->getIndex());
                evidenceElement.setAttribute("operationtype",k.value()->getop());
                evidenceElement.setAttribute("name",k.value()->getName());


                symptom.appendChild( evidenceElement);

            }

            QDomElement root=smileXml.documentElement();
            root.appendChild(symptom);

        }
        QFile File(filename);
        if ( File.open( QIODevice::WriteOnly ) ){
            QTextStream TextStream(&File);
            TextStream <<smileXml.toString();
            File.close();
            //this->new_logExpert_entry("New situation added: "+ui->lineSituationName->text());
        }
    }
}


void MainWindow::on_pushButton_importxml_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Select a .xml file"), "C://", ".xml files (*.xml))");
    QMap<QString,symptom*> importedNodes;
    importData.readXmlFile(filename,importedNodes);
    // Compare Xmlnodes and add Evidence values to Sympnodes
    int indexCounter =0;
    QMap<QString,symptom*>::iterator i;
    for (i = SympsNodesMap.begin(); i != SympsNodesMap.end(); ++i){
        QMap<QString,symptom*>::iterator k;
        for(k=importedNodes.begin();k!= importedNodes.end();++k){

            if(!i.key().compare(k.key())){

                QMap<QString, evidence*> emptyEvidenceList = i.value()->getEvidencelist();

                QMap<QString,evidence*>::iterator n;
                int childcounter=0;
                for(n=emptyEvidenceList.begin(); n!=emptyEvidenceList.end();++n){
                    QMap<QString, evidence*> emptyXmlEvidenceList = k.value()->getEvidencelist();

                    QMap<QString,evidence*>::iterator d;
                    for(d=emptyXmlEvidenceList.begin(); d!=emptyXmlEvidenceList.end();++d){
                       if(!(n.value()->getName().compare(d.value()->getName()))&& (n.value()->getIndex()==n.value()->getIndex())){

                         n.value()->setop(d.value()->getop());
                         n.value()->setvalues(d.value()->getvalues());

                         QTreeWidgetItem *fondItem= ui->treeWidget_2->topLevelItem(indexCounter);
                         fondItem->child(childcounter)->setBackground(0,Qt::green);
                         childcounter++;
                         greenCount++;
                       }
                    }

                }
            }


        }

    indexCounter++;
    }

    if(greenCount==totalchilds){
        ui->pushButton_exportxml->setEnabled(true);
        ui->next_to_resultscolumn->setEnabled(true);

    }
    this->new_logConfigAnalyze_entry("--------------------------");
    this->new_logConfigAnalyze_entry("Done value");



}

int MainWindow::allChildHasValues()
{
    int totalItems= ui->treeWidget_2->topLevelItemCount();
    int total=0;
    for(int t=0;t< totalItems;t++){
        QTreeWidgetItem *currentdata = ui->treeWidget_2->topLevelItem(t);
        int childs = currentdata->childCount();
        total = total + childs;
    }
    return total;
}

void MainWindow::on_prepare_analyze_clicked()
{
    if(rawCSV && !(readyCSV)){
        QMap<QString, QVector<int> > list;
        ui->progressBar->setValue(10);
        list =genEvidence->calculateEvidence(importData.getSensorData(),SympsNodesMap);
        ui->progressBar->setValue(20);
        //save data
        exportData.saveEvidenceCsvlist(list);
        ui->progressBar->setValue(30);
        exportData.saveSymptomsCSV(SympsNodesMap);
        ui->progressBar->setValue(40);
        exportData.saveResultNodeCSV(resultsNodemap);
        ui->progressBar->setValue(50);

        QString visualstudioname = "smileLab/smileoffi.exe";
        myProcess = new QProcess(this);
        myProcess->setWorkingDirectory("smileLab");
        QString workbench = myProcess->workingDirectory();
        //cout<<workbench<<endl;
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry(workbench);


        myProcess->start(visualstudioname);
            if(myProcess->waitForFinished()){
                this->new_logConfig_entry("--------------------------");
                this->new_logConfig_entry("Visual studio is done");
                importData.readSmileResultData("smileLab/resultdata.csv",",",SmileResultdata);
                QStandardItemModel *tableSmileData = new QStandardItemModel(SmileResultdata.size(),SmileResultdata[0].size(),this);

                for (unsigned int i = 0; i < SmileResultdata.size(); i++){
                    for (unsigned int j = 0; j < SmileResultdata[i].size(); j++){
                        QStandardItem *firstRow = new QStandardItem(SmileResultdata[i][j]);
                            tableSmileData->setItem(i,j,firstRow);
                    }
                    ui->tableView_resultdata->setRowHeight(i,20);
                }

                ui->tableView_resultdata->setModel(tableSmileData);

            }else{
                this->new_logConfig_entry("--------------------------");
                this->new_logConfig_entry("Something when wrong, please try again");
            }

        this->new_logConfigAnalyze_entry("--------------------------");
        this->new_logConfigAnalyze_entry("Done value");
        ui->progressBar->setValue(100);
        ui->tabWidget->setCurrentWidget(ui->tab);
        this->resetAll();
    }else{
        exportData.saveSymptomsCSV(SympsNodesMap);
        ui->progressBar->setValue(30);
        exportData.saveResultNodeCSV(resultsNodemap);
        ui->progressBar->setValue(60);

        if(readyCSVDatabase) {
            exportData.savePrepDataCsv(importData.getSensorData(), SympsNodesMap, importData.getTimeData().size());
        } else {
            exportData.savePrepDataCsv(importData.getTotalData(),SympsNodesMap);
        }
        ui->progressBar->setValue(80);

        //Analyze data
        QString visualstudioname = "smileLab/smileoffi.exe";
        myProcess = new QProcess(this);
        myProcess->setWorkingDirectory("smileLab");
        QString workbench = myProcess->workingDirectory();
        //cout<<workbench<<endl;
        this->new_logConfig_entry("--------------------------");
        this->new_logConfig_entry(workbench);

        myProcess->start(visualstudioname);
        ui->progressBar->setValue(90);
        QCoreApplication::processEvents();

        if(myProcess->waitForFinished()){
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Visual studio is done");

            importData.readSmileResultData("smileLab/resultdata.csv",",",SmileResultdata);

            dataLogger->write(QString("Smile size: " + QString::number(SmileResultdata.size())));
            dataLogger->write(QString("Smile 1 size: " + QString::number(SmileResultdata[1].size())));

            QStandardItemModel *tableSmileData = new QStandardItemModel(SmileResultdata.size(),SmileResultdata[0].size(),this);

            for (unsigned int i = 0; i < SmileResultdata.size(); i++){
                for (unsigned int j = 0; j < SmileResultdata[i].size(); j++){
                    QStandardItem *firstRow = new QStandardItem(SmileResultdata[i][j]);
                        tableSmileData->setItem(i,j,firstRow);
                }
                ui->tableView_resultdata->setRowHeight(i,20);
            }

            ui->tableView_resultdata->setModel(tableSmileData);

        } else{
            this->new_logConfig_entry("--------------------------");
            this->new_logConfig_entry("Something when wrong, please try again");
        }

        this->new_logConfigAnalyze_entry("--------------------------");
        this->new_logConfigAnalyze_entry("Done value");
        ui->progressBar->setValue(100);
        ui->tabWidget->setCurrentWidget(ui->tab);
        this->resetAll();
    }

}

void MainWindow::on_convertSmiledataToCSV_clicked()
{
    if(!SmileResultdata.empty()){
        QString filepath = QFileDialog::getSaveFileName(this, tr("Select a .csv file"), "C://", ".csv files (*.csv))");
        exportData.saveSmileresultdata(filepath,SmileResultdata);
    }
}

void MainWindow::on_comboBox_values_currentIndexChanged(int index)
{
    if(index != 0 || index !=1){
        if(index ==5){
          ui->doubleSpinBox->setEnabled(true);
          ui->doubleSpinBox_2->setEnabled(true);
        }else{
          ui->doubleSpinBox->setEnabled(true);
          ui->doubleSpinBox_2->setEnabled(false);
        }
    }else{
        ui->doubleSpinBox_2->setEnabled(false);
        ui->doubleSpinBox->setEnabled(false);
    }
}


template<class T> std::vector< std::vector<T> > MainWindow::transposeData(std::vector< std::vector<T> > oldData)
{
    std::vector< std::vector<T> > newDataTrans(oldData[0].size(), std::vector<T>(oldData.size()));

    for (size_t i = 0; i < oldData.size(); ++i)
        for (size_t j = 0; j < oldData[0].size(); ++j)
            newDataTrans[j][i] = oldData[i][j];

    return newDataTrans;
}
