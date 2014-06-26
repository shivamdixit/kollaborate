#-------------------------------------------------
#
# Project created by QtCreator 2014-04-12T13:51:51
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kollaborate
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/initialdialog.cpp \
    src/clipboarditem.cpp

HEADERS  += src/mainwindow.h \
    src/initialdialog.h \
    src/clipboarditem.h

FORMS    += ui/mainwindow.ui \
    ui/initialdialog.ui

target.path = /usr/local/bin/
INSTALLS += target
