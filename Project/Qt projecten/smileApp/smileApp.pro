#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T02:01:44
#
#-------------------------------------------------

QT       += core gui
QT	 	 +=	xml
QT 	 	 += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = smileApp
TEMPLATE = app
win32:RC_ICONS += graph.ico


SOURCES += main.cpp\
        mainwindow.cpp \
    datacenter/import.cpp \
    nodes/evidence.cpp \
    nodes/symptom.cpp \
    nodes/generateevidence.cpp \
    datacenter/exportfiles.cpp \
    windowconnectdatabase.cpp \
    datacenter/database.cpp \
    datacenter/query.cpp \
    datacenter/convertdata.cpp \
    datacenter/datetimecalc.cpp \
    logger.cpp

HEADERS  += mainwindow.h \
    datacenter/import.h \
    nodes/evidence.h \
    nodes/symptom.h \
    nodes/generateevidence.h \
    nodes/evidencecomparators.h \
    datacenter/exportfiles.h \
    windowconnectdatabase.h \
    datacenter/database.h \
    datacenter/query.h \
    datacenter/convertdata.h \
    datacenter/datetimecalc.h \
    logger.h

FORMS    += mainwindow.ui \
    windowconnectdatabase.ui

DISTFILES +=
