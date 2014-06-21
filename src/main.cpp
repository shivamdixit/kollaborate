#include "mainwindow.h"
#include "initialdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Kollaborate Inc.");
    QCoreApplication::setOrganizationDomain("kollaborate.co.in");
    QCoreApplication::setApplicationName("Kollaborate");

    InitialDialog initSettings;

    if (initSettings.exec()) {
        MainWindow w;
        w.show();
        return a.exec();
    } else {
        a.quit();
    }

}
