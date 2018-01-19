#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QVector>
#include <QThread>
#include <QProcess>

#include "windowconnectdatabase.h"
#include "datacenter/import.h"
#include "datacenter/exportfiles.h"
#include "datacenter/logger.h"
#include "nodes/evidence.h"
#include "nodes/evidencecomparators.h"
#include "nodes/symptom.h"
#include "nodes/generateevidence.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void new_logConfig_entry(QString newline);
    void new_logConfigAnalyze_entry(QString newline);
    ~MainWindow();

private slots:
    void on_pushButton_importxml_clicked();
    void on_pushButton_exportxml_clicked();
    void on_importLinkedxml_clicked();
    void on_ExportLinkedXml_clicked();
    void on_import_genie_clicked();
    void on_importRawCSV_clicked();
    void on_importAnalyzeCSV_clicked();
    void on_add_symptom_clicked();
    void on_add_resultnodes_clicked();
    void on_remove_symptom_clicked();
    void on_remove_result_node_clicked();
    void on_savesymptoms_clicked();
    void on_add_value_boundary_clicked();
    void on_pushButton_boundary_clicked();
    void on_prepare_analyze_clicked();
    void on_convertSmiledataToCSV_clicked();
    void on_Import_nodes_clicked();
    void on_export_nodes_clicked();
    void on_next_analysedata_clicked();
    void on_next_to_sort_nodes_clicked();
    void on_next_to_linkcolumn_clicked();
    void on_next_to_analyze_or_results_clicked();
    void on_next_to_resultscolumn_clicked();

    void on_comboBox_values_currentIndexChanged(int index);

    void on_importDatabaseCSV_clicked();

private:
    Ui::MainWindow *ui;
    windowConnectDatabase *Window_ConnectDatabase;
    import importData;
    Exportfiles exportData;
    Logger *dataLogger;

    int tableRow;
    int tableCol;

    template<class T> static std::vector< std::vector<T> > transposeData(std::vector< std::vector<T> > oldData);
    bool makeHighAirflowMap();

    std::map<QString, std::pair<unsigned int, unsigned int> > HighAirflow;
    /// is from the Xml file
    QMap<QString, vector<QString> > datamap;
    QMap<QString, vector<QString> > resultsNodemap;
    vector<vector<QString> > SmileResultdata;
    vector<symptom> symptomNodes;
    QMap<QString,symptom*> SympsNodesMap;
    generateEvidence *genEvidence;

    //// function///
    bool addChild(QTreeWidgetItem *nodeparent, QString name);
    QMap<QString, evidence *> getAllEvidence(QString name);
   // bool compareEvidence(evidence* one, evidence* two);
    void linkSymptomToNode();
    void saveResultnode();
    void addSymptomstoWidget();
    int  allChildHasValues();

   // varible
    QString textSmile;
    bool rawCSV;
    bool readyCSV;
    bool readyCSVDatabase;
    int greenCount;
    int totalchilds;
    QProcess *myProcess;

    // functions to enable ui
    void setEnabled_tab2(bool status);
    void setEnabled_tab3(bool status);
    void setEnabled_tab4(bool status);
    void setEnabled_tab5(bool status);
    void setEnabled_tab5_part2(bool status);
    void setEnabled_tab6(bool status);

    void resetAll();

};

#endif // MAINWINDOW_H
