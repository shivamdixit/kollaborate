#ifndef INITIALDIALOG_H
#define INITIALDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class InitialDialog;
}

class InitialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InitialDialog(QWidget *parent = 0);
    ~InitialDialog();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::InitialDialog *ui;
};

#endif // INITIALDIALOG_H
