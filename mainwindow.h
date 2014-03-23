#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QClipboard>
#include <QMimeData>
#include <QHBoxLayout>
#include <QVBoxLayout>

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
    void on_pushButton_clicked();
    void readPendingDatagrams();

private:
    Ui::MainWindow *ui;
    QUdpSocket *udpSocket;
    QHostAddress groupAddress;
    const qint16 udpPort;
    QHBoxLayout *top;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H
