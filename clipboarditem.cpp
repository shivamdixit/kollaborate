#include "clipboarditem.h"

#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <QSettings>

ClipboardItem::ClipboardItem(QObject *parent) :
    QObject(parent),
    vlc(0)
{
    button = new QPushButton;
    button->setMaximumSize(300, 30);
    button->setFocusPolicy(Qt::NoFocus);

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

ClipboardItem::~ClipboardItem()
{
    button->deleteLater();
    if (vlc) {
        vlc->kill();
        vlc->waitForFinished();
        delete vlc;
    }
}

void ClipboardItem::onButtonClicked()
{
    QClipboard *sysClipboard = QApplication::clipboard();
    QMimeData *clipMime = new QMimeData;

    if(mimeType != "screen") {
        if (mimeType == "html") {
            clipMime->setHtml(data);
            clipMime->setText(dataPlain);
        } else if (mimeType == "plain") {
            clipMime->setText(data);
        } else {
            delete clipMime;
            return;
        }
        sysClipboard->setMimeData(clipMime);
    } else {
        QString groupAddress;
        QSettings *settings = new QSettings;
        int pinMod = settings->value("pin").toInt() % 256;
        delete settings;

        groupAddress = "239.255.0." + QString::number(pinMod);

        vlc = new QProcess;
        vlc->start("vlc udp://" + data + "@" + groupAddress + ":12345");
    }
}
