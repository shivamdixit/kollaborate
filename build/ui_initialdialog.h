/********************************************************************************
** Form generated from reading UI file 'initialdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIALDIALOG_H
#define UI_INITIALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitialDialog
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *username_line;
    QLabel *label_2;
    QLineEdit *pin_line;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *InitialDialog)
    {
        if (InitialDialog->objectName().isEmpty())
            InitialDialog->setObjectName(QStringLiteral("InitialDialog"));
        InitialDialog->resize(254, 142);
        InitialDialog->setMinimumSize(QSize(254, 142));
        InitialDialog->setMaximumSize(QSize(254, 142));
        InitialDialog->setModal(true);
        layoutWidget = new QWidget(InitialDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(22, 26, 205, 85));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        username_line = new QLineEdit(layoutWidget);
        username_line->setObjectName(QStringLiteral("username_line"));
        username_line->setMaxLength(8);

        gridLayout->addWidget(username_line, 0, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        pin_line = new QLineEdit(layoutWidget);
        pin_line->setObjectName(QStringLiteral("pin_line"));
        pin_line->setMaxLength(4);
        pin_line->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(pin_line, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addLayout(horizontalLayout, 2, 1, 1, 2);

        QWidget::setTabOrder(pushButton, pushButton_2);
        QWidget::setTabOrder(pushButton_2, username_line);
        QWidget::setTabOrder(username_line, pin_line);

        retranslateUi(InitialDialog);

        QMetaObject::connectSlotsByName(InitialDialog);
    } // setupUi

    void retranslateUi(QDialog *InitialDialog)
    {
        InitialDialog->setWindowTitle(QApplication::translate("InitialDialog", "Settings", 0));
#ifndef QT_NO_TOOLTIP
        label->setToolTip(QApplication::translate("InitialDialog", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("InitialDialog", "Username", 0));
#ifndef QT_NO_TOOLTIP
        username_line->setToolTip(QApplication::translate("InitialDialog", "<html><head/><body><p>Enter a username to identify yourself (max 8 characters)</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("InitialDialog", "<html><head/><body><p><br/></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("InitialDialog", "PIN", 0));
#ifndef QT_NO_TOOLTIP
        pin_line->setToolTip(QApplication::translate("InitialDialog", "<html><head/><body><p>Enter a 4 digit PIN to specify your group</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QApplication::translate("InitialDialog", "OK", 0));
        pushButton_2->setText(QApplication::translate("InitialDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class InitialDialog: public Ui_InitialDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIALDIALOG_H
