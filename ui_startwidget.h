/********************************************************************************
** Form generated from reading UI file 'startwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWIDGET_H
#define UI_STARTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWidget
{
public:
    QPushButton *startButton;
    QLabel *label;

    void setupUi(QWidget *StartWidget)
    {
        if (StartWidget->objectName().isEmpty())
            StartWidget->setObjectName(QStringLiteral("StartWidget"));
        StartWidget->resize(796, 589);
        StartWidget->setStyleSheet(QStringLiteral(""));
        startButton = new QPushButton(StartWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(390, 400, 211, 191));
        startButton->setMinimumSize(QSize(211, 191));
        startButton->setMaximumSize(QSize(211, 191));
        startButton->setStyleSheet(QStringLiteral("border-image: url(:/Interface/starticon.png);"));
        label = new QLabel(StartWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 801, 591));
        label->setStyleSheet(QStringLiteral("background-image: url(:/Interface/startinterface.png);"));
        label->raise();
        startButton->raise();

        retranslateUi(StartWidget);

        QMetaObject::connectSlotsByName(StartWidget);
    } // setupUi

    void retranslateUi(QWidget *StartWidget)
    {
        StartWidget->setWindowTitle(QApplication::translate("StartWidget", "Form", Q_NULLPTR));
        startButton->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StartWidget: public Ui_StartWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWIDGET_H
