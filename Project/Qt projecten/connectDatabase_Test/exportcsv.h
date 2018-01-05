#ifndef EXPORTCSV_H
#define EXPORTCSV_H

#include <QList>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include <vector>
#include <iostream>

using namespace std;

class exportCSV{
    private:
        vector< vector<QString> > data;
        vector<vector<int> > dataint;
    public:
        exportCSV();
        void prepData(vector<vector<QString> > newData);
        void prepDataInt(vector<vector<int> > newData);

        void saveCSV(QString filename, QString delimiter);
        void saveCSVInt(QString filename, QString delimiter);
};

#endif // EXPORTCSV_H
