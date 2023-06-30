/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *bigWidget;
    QGridLayout *gridLayout;
    QToolButton *pauseBtn;
    QWidget *unitWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QToolButton *warriorBtn;
    QToolButton *minerBtn;
    QToolButton *shieldBtn;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QToolButton *archerBtn;
    QToolButton *catapultBtn;
    QToolButton *flyWarriorBtn;
    QTextBrowser *infoWidget;
    QLabel *label;
    QProgressBar *progressBar;
    QSpacerItem *spacer;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(659, 709);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(Widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        bigWidget = new QWidget(Widget);
        bigWidget->setObjectName(QStringLiteral("bigWidget"));
        bigWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        gridLayout = new QGridLayout(bigWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pauseBtn = new QToolButton(bigWidget);
        pauseBtn->setObjectName(QStringLiteral("pauseBtn"));
        pauseBtn->setMinimumSize(QSize(50, 50));
        pauseBtn->setMaximumSize(QSize(50, 50));
        pauseBtn->setLayoutDirection(Qt::LeftToRight);
        pauseBtn->setStyleSheet(QStringLiteral("border-image: url(:/Interface/pauseicon.png);"));

        gridLayout->addWidget(pauseBtn, 0, 1, 1, 1);

        unitWidget = new QWidget(bigWidget);
        unitWidget->setObjectName(QStringLiteral("unitWidget"));
        unitWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        horizontalLayout_2 = new QHBoxLayout(unitWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        widget = new QWidget(unitWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        warriorBtn = new QToolButton(widget);
        warriorBtn->setObjectName(QStringLiteral("warriorBtn"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(warriorBtn->sizePolicy().hasHeightForWidth());
        warriorBtn->setSizePolicy(sizePolicy1);
        warriorBtn->setMinimumSize(QSize(100, 100));
        warriorBtn->setMaximumSize(QSize(100, 100));
        warriorBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"font: 1000 9pt \"Arial\";\n"
"border-image: url(:/Units/melee_1.png);\n"
"}"));

        verticalLayout->addWidget(warriorBtn);

        minerBtn = new QToolButton(widget);
        minerBtn->setObjectName(QStringLiteral("minerBtn"));
        sizePolicy1.setHeightForWidth(minerBtn->sizePolicy().hasHeightForWidth());
        minerBtn->setSizePolicy(sizePolicy1);
        minerBtn->setMinimumSize(QSize(100, 100));
        minerBtn->setMaximumSize(QSize(100, 100));
        minerBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"	font: 1000 9pt \"Arial\";\n"
"	border-image: url(:/Units/miner_1.png);\n"
"}"));

        verticalLayout->addWidget(minerBtn);

        shieldBtn = new QToolButton(widget);
        shieldBtn->setObjectName(QStringLiteral("shieldBtn"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(100);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(shieldBtn->sizePolicy().hasHeightForWidth());
        shieldBtn->setSizePolicy(sizePolicy2);
        shieldBtn->setMinimumSize(QSize(100, 100));
        shieldBtn->setMaximumSize(QSize(100, 100));
        shieldBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"	font: 1000 9pt \"Arial\";\n"
"	border-image: url(:/Units/shield_1.png);\n"
"}"));

        verticalLayout->addWidget(shieldBtn);


        horizontalLayout_2->addWidget(widget);

        widget_2 = new QWidget(unitWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        archerBtn = new QToolButton(widget_2);
        archerBtn->setObjectName(QStringLiteral("archerBtn"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(archerBtn->sizePolicy().hasHeightForWidth());
        archerBtn->setSizePolicy(sizePolicy3);
        archerBtn->setMinimumSize(QSize(100, 100));
        archerBtn->setMaximumSize(QSize(100, 100));
        archerBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"	font: 1000 9pt \"Arial\";\n"
"	border-image: url(:/Units/range_1.png);\n"
"}"));

        verticalLayout_2->addWidget(archerBtn);

        catapultBtn = new QToolButton(widget_2);
        catapultBtn->setObjectName(QStringLiteral("catapultBtn"));
        sizePolicy3.setHeightForWidth(catapultBtn->sizePolicy().hasHeightForWidth());
        catapultBtn->setSizePolicy(sizePolicy3);
        catapultBtn->setMinimumSize(QSize(100, 100));
        catapultBtn->setMaximumSize(QSize(100, 100));
        catapultBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"	font: 1000 9pt \"Arial\";\n"
"	border-image: url(:/Units/catapult_1.png);\n"
"}"));

        verticalLayout_2->addWidget(catapultBtn);

        flyWarriorBtn = new QToolButton(widget_2);
        flyWarriorBtn->setObjectName(QStringLiteral("flyWarriorBtn"));
        sizePolicy3.setHeightForWidth(flyWarriorBtn->sizePolicy().hasHeightForWidth());
        flyWarriorBtn->setSizePolicy(sizePolicy3);
        flyWarriorBtn->setMinimumSize(QSize(100, 100));
        flyWarriorBtn->setMaximumSize(QSize(100, 100));
        flyWarriorBtn->setStyleSheet(QLatin1String("QToolButton\n"
"{\n"
"	font: 1000 9pt \"Arial\";\n"
"	border-image: url(:/Units/flywarrior_1.png);\n"
"}"));

        verticalLayout_2->addWidget(flyWarriorBtn);


        horizontalLayout_2->addWidget(widget_2);


        gridLayout->addWidget(unitWidget, 1, 0, 1, 2);

        infoWidget = new QTextBrowser(bigWidget);
        infoWidget->setObjectName(QStringLiteral("infoWidget"));
        sizePolicy3.setHeightForWidth(infoWidget->sizePolicy().hasHeightForWidth());
        infoWidget->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(infoWidget, 2, 0, 1, 2);

        label = new QLabel(bigWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\347\220\245\347\217\200"));
        font.setPointSize(10);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 3, 0, 1, 1);

        progressBar = new QProgressBar(bigWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        sizePolicy3.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy3);
        progressBar->setStyleSheet(QLatin1String("QProgressBar{\n"
"	font:9pt;\n"
"	border-radius:5px;\n"
"	text-align:center;\n"
"	font: 500 10pt \"Arial\";\n"
"	border:1px solid #E8EDF2;\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-color: rgb(180, 180, 180);\n"
"}\n"
"QProgressBar:chunk{\n"
"	border-radius:5px;\n"
"	background-color:#1ABC9C;\n"
"}\n"
""));
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 4, 0, 1, 2);

        spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(spacer, 5, 0, 1, 2);


        horizontalLayout->addWidget(bigWidget);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        pauseBtn->setText(QString());
        warriorBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\346\210\230\345\243\253  100", Q_NULLPTR));
        minerBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\n"
"\347\237\277\345\267\245  100", Q_NULLPTR));
        shieldBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\n"
"\347\233\276\347\211\214   125", Q_NULLPTR));
        archerBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\345\274\223\347\256\255\346\211\213  100", Q_NULLPTR));
        catapultBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\n"
"\346\212\225\347\237\263\350\275\246  200", Q_NULLPTR));
        flyWarriorBtn->setText(QApplication::translate("Widget", "\n"
"\n"
"\n"
"\n"
"\351\243\236\350\241\214\346\210\230\345\243\253 125", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "\350\277\233\346\224\273\350\277\233\345\272\246", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
