#-------------------------------------------------
#
# Project created by QtCreator 2014-04-12T13:51:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kollaborate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    initialdialog.cpp \
    clipboarditem.cpp

HEADERS  += mainwindow.h \
    initialdialog.h \
    clipboarditem.h

FORMS    += mainwindow.ui \
    initialdialog.ui
