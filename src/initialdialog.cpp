#include "initialdialog.h"
#include "ui_initialdialog.h"

InitialDialog::InitialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InitialDialog)
{
    ui->setupUi(this);
    ui->pin_line->setValidator(new QIntValidator(0, 9999, this));

    QSettings settings;
    ui->username_line->setText(settings.value("username").toString());
    ui->pin_line->setText(settings.value("pin").toString());
}

InitialDialog::~InitialDialog()
{
    delete ui;
}

void InitialDialog::on_pushButton_clicked()
{
    QSettings settings;
    if (!ui->pin_line->text().isEmpty() && !ui->username_line->text().isEmpty()) {
        settings.setValue("username", ui->username_line->text());
        settings.setValue("pin", ui->pin_line->text());
        accept();
    }
}

void InitialDialog::on_pushButton_2_clicked()
{
    reject();
}
