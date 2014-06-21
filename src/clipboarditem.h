#ifndef CLIPBOARDITEM_H
#define CLIPBOARDITEM_H

#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <QProcess>

class ClipboardItem : public QObject
{
    Q_OBJECT
public:
    explicit ClipboardItem(QObject *parent = 0);
    ~ClipboardItem();

    QPushButton *button;
    QString data;
    QString dataPlain;
    QString mimeType;

signals:

public slots:
    void onButtonClicked();

private slots:
    void vlcClosed();

private:
    QProcess *vlc;

};

#endif // CLIPBOARDITEM_H
