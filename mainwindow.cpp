#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    groupAddress("239.255.0.1"),
    udpPort(6789)
{
//    top = new QHBoxLayout;
//    mainLayout = new QVBoxLayout(this);
//    mainLayout->addLayout(top);
//    this->centralWidget()->setLayout(mainLayout);


    udpSocket = new QUdpSocket(this);
    ui->setupUi(this);

    udpSocket->bind(QHostAddress::AnyIPv4, udpPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);
    QObject::connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readPendingDatagrams()
{

    QLabel *label = new QLabel(this);
//    QPushButton *label= new QPushButton(this);

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        QString data;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);
        data = QString::fromUtf8(datagram);
        ui->horizontalLayout->addWidget(label);
        label->setText(data);
        //qDebug() << data;
    }
}

void MainWindow::on_pushButton_clicked()
{
    QClipboard *sysClipboard = QApplication::clipboard();
    QString stringHtml("html");
    QString stringPlain("plain");

    QString message = sysClipboard->mimeData()->hasHtml() ? sysClipboard->text(stringHtml) : sysClipboard->text(stringPlain);
    QByteArray msgB = message.toUtf8();

    //qDebug() << message;
    udpSocket->writeDatagram(msgB, groupAddress, udpPort);
}
