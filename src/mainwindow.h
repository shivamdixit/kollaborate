#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "clipboarditem.h"

#include <QMainWindow>
#include <QUdpSocket>
#include <QClipboard>
#include <QMimeData>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readPendingDatagrams();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_actionAbout_triggered();

    void on_startShareScreenButton_clicked();

    void on_stopShareScreenButton_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;
    const qint16 udpPort;
    QProcess *ffmpeg;
    QList<ClipboardItem*> allClipboardItems;

    void removeScreenCastButtonBy(QString data);
};

#endif // MAINWINDOW_H
