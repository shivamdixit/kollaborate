#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clipboarditem.h"

#include <QSettings>
#include <QShortcut>
#include <QTextDocument>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QDesktopWidget>

static const int maxUsernameSize(8);
static const int maxTitleSize(16);
static const int maxMimeSize(8);
static const QString defaultTitle("");
static const QString stringScreenMime("screen");
static const QString stringScreenStopMime("screenS");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    udpPort(6789)
{
    ui->setupUi(this);
    setFixedHeight(600);
    setFixedWidth(400);

    QSettings *settings = new QSettings;
    int pinMod = settings->value("pin").toInt() % 256;
    delete settings;
    groupAddress = "239.255.0." + QString::number(pinMod);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, udpPort, QUdpSocket::ShareAddress);
    udpSocket->joinMulticastGroup(groupAddress);
    QObject::connect(udpSocket, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));

    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(close()));
    new QShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_V), this, SLOT(on_pushButton_clicked()));
    new QShortcut(QKeySequence(Qt::Key_F1), this, SLOT(on_actionAbout_triggered()));
}

MainWindow::~MainWindow()
{
    ClipboardItem *item;
    if (ui->stopShareScreenButton->isEnabled()) {
        on_stopShareScreenButton_clicked();
    }
    foreach (item, allClipboardItems) {
        delete item;
    }
    delete ui;
}

void MainWindow::readPendingDatagrams()
{
    QByteArray datagram;
    QString data;
    datagram.resize(udpSocket->pendingDatagramSize());
    QHostAddress sender;
    quint16 senderPort;

    ClipboardItem *toAdd = new ClipboardItem(this);

    while (udpSocket->hasPendingDatagrams()) {
        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);
        data = QString::fromUtf8(datagram);

        toAdd->mimeType = data.mid(maxUsernameSize + maxTitleSize, maxMimeSize).trimmed();
        toAdd->data = data.mid(maxUsernameSize + maxTitleSize + maxMimeSize);

        if (data.mid(maxUsernameSize + maxTitleSize, maxMimeSize).trimmed() == stringScreenMime) {
            toAdd->button->setText("Screen Cast by " + data.left(maxUsernameSize).trimmed());
        } else if (data.mid(maxUsernameSize + maxTitleSize, maxMimeSize).trimmed() == stringScreenStopMime) {
            removeScreenCastButtonBy(data.mid(maxUsernameSize + maxTitleSize + maxMimeSize));
        } else if (data.mid(maxUsernameSize, maxTitleSize).trimmed() != defaultTitle) {
            toAdd->button->setText("\"" + data.mid(maxUsernameSize, maxTitleSize).trimmed()
                                   + "\" by " + data.left(maxUsernameSize).trimmed());
        } else if (toAdd->mimeType == "html") {
            QTextDocument tempDoc;
            tempDoc.setHtml(toAdd->data);
            toAdd->dataPlain = tempDoc.toPlainText();

            toAdd->button->setText("\"" + tempDoc.toPlainText().left(16).simplified()
                                   + "\"  by " + data.left(maxUsernameSize).trimmed());
        } else {
            toAdd->button->setText(toAdd->data.left(16).simplified()
                                   + "  by " + data.left(maxUsernameSize).trimmed());
        }
    }
    if (data.mid(maxUsernameSize + maxTitleSize, maxMimeSize).trimmed() != stringScreenStopMime) {
        allClipboardItems.append(toAdd);
        ui->gridLayout->addWidget(toAdd->button);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QClipboard *sysClipboard = QApplication::clipboard();
    QString stringHtml("html");
    QString stringPlain("plain");

    QSettings *settings = new QSettings;
    QString message = settings->value("username").toString().leftJustified(maxUsernameSize, ' ');
    delete settings;

    message += ui->titleText->text().leftJustified(maxTitleSize, ' ');
    ui->titleText->setText(defaultTitle);

    if (sysClipboard->mimeData()->hasHtml()) {
        message += stringHtml.leftJustified(maxMimeSize, ' ');
        message += sysClipboard->text(stringHtml);
    } else {
        message += stringPlain.leftJustified(maxMimeSize, ' ');
        message += sysClipboard->text(stringPlain);
    }

    QByteArray msgB = message.toUtf8();
    udpSocket->writeDatagram(msgB, groupAddress, udpPort);
}

void MainWindow::on_pushButton_2_clicked()
{
    ClipboardItem *item;
    foreach (item, allClipboardItems) {
        ui->gridLayout->removeWidget(item->button);
        item->deleteLater();
    }
    allClipboardItems.clear();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About Kollaborate",
                       "This application is created by :\n Ashish Madeti\n Deepak Sharma\n Ritesh Agrawal\n Shivam Dixit");
}

void MainWindow::on_startShareScreenButton_clicked()
{
    QHostAddress localIp;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             localIp = address;
             break;
        }
    }

    QSettings *settings = new QSettings;
    QString message = settings->value("username").toString().leftJustified(maxUsernameSize, ' ');
    delete settings;

    message += QString("").leftJustified(maxTitleSize, ' ');
    message += stringScreenMime.leftJustified(maxMimeSize, ' ');
    message += localIp.toString();

    QByteArray msgB = message.toUtf8();
    udpSocket->writeDatagram(msgB, groupAddress, udpPort);

    QDesktopWidget widget;

    int width = widget.availableGeometry(widget.primaryScreen()).width();
    int height= widget.availableGeometry(widget.primaryScreen()).height();

    //make width and height even
    if (width % 2 != 0)
        width -= 1;
    if (height % 2 != 0)
        height -=1;

    QString resolution = QString::number(width) + "x" + QString::number(height);

    ffmpeg = new QProcess;
    QString ffmpegCommand("ffmpeg -f alsa -ac 2 -ar 48000 -i default -f x11grab -r 30 -s "
                          + resolution
                          + " -i :0.0+0,0 -acodec mp2 -vcodec libx264 -preset ultrafast -threads 0  -f mpegts udp://"
                          + groupAddress.toString() + ":12345");
    ffmpeg->start(ffmpegCommand);

    ui->startShareScreenButton->setEnabled(false);
    ui->stopShareScreenButton->setEnabled(true);
}

void MainWindow::on_stopShareScreenButton_clicked()
{
    ffmpeg->kill();
    ffmpeg->waitForFinished();
    ffmpeg->deleteLater();

    QHostAddress localIp;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost)) {
             localIp = address;
             break;
        }
    }

    QSettings *settings = new QSettings;
    QString message = settings->value("username").toString().leftJustified(maxUsernameSize, ' ');
    delete settings;

    message += QString("").leftJustified(maxTitleSize, ' ');
    message += stringScreenStopMime.leftJustified(maxMimeSize, ' ');
    message += localIp.toString();

    QByteArray msgB = message.toUtf8();
    udpSocket->writeDatagram(msgB, groupAddress, udpPort);

    ui->startShareScreenButton->setEnabled(true);
    ui->stopShareScreenButton->setEnabled(false);
}

void MainWindow::removeScreenCastButtonBy(QString data)
{
    int i = 0;
    ClipboardItem *item;
    foreach (item, allClipboardItems) {
        if (item->mimeType == stringScreenMime && item->data == data) {
            item->deleteLater();
            allClipboardItems.removeAt(i);
        }
        i++;
    }
}
