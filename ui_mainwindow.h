/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *ResetButton;
    QLabel *ScreenLabel;
    QListView *OpsListView;
    QPushButton *GoButton;
    QPushButton *StopButton;
    QPushButton *StepButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLCDNumber *R0_LCD;
    QLabel *label_9;
    QLCDNumber *R4_LCD;
    QLCDNumber *R1_LCD;
    QLCDNumber *R2_LCD;
    QLCDNumber *R3_LCD;
    QLCDNumber *R5_LCD;
    QLCDNumber *R6_LCD;
    QLCDNumber *R7_LCD;
    QGridLayout *gridLayout_4;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_11;
    QLabel *label_15;
    QLCDNumber *ZFlagLCD;
    QLCDNumber *VFlagLCD;
    QLCDNumber *CFlagLCD;
    QLCDNumber *NFlagLCD;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(872, 456);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));
        ResetButton->setGeometry(QRect(20, 300, 121, 41));
        ScreenLabel = new QLabel(centralWidget);
        ScreenLabel->setObjectName(QStringLiteral("ScreenLabel"));
        ScreenLabel->setGeometry(QRect(10, 10, 512, 256));
        OpsListView = new QListView(centralWidget);
        OpsListView->setObjectName(QStringLiteral("OpsListView"));
        OpsListView->setGeometry(QRect(540, 10, 301, 161));
        GoButton = new QPushButton(centralWidget);
        GoButton->setObjectName(QStringLiteral("GoButton"));
        GoButton->setGeometry(QRect(160, 300, 111, 41));
        StopButton = new QPushButton(centralWidget);
        StopButton->setObjectName(QStringLiteral("StopButton"));
        StopButton->setGeometry(QRect(290, 300, 111, 41));
        StepButton = new QPushButton(centralWidget);
        StepButton->setObjectName(QStringLiteral("StepButton"));
        StepButton->setGeometry(QRect(420, 300, 101, 41));
        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(540, 180, 311, 241));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(40);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        label_3 = new QLabel(horizontalLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        label_7 = new QLabel(horizontalLayoutWidget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 5, 0, 1, 1);

        label_8 = new QLabel(horizontalLayoutWidget_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 6, 0, 1, 1);

        R0_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R0_LCD->setObjectName(QStringLiteral("R0_LCD"));
        R0_LCD->setSegmentStyle(QLCDNumber::Flat);
        R0_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R0_LCD, 0, 1, 1, 1);

        label_9 = new QLabel(horizontalLayoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 7, 0, 1, 1);

        R4_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R4_LCD->setObjectName(QStringLiteral("R4_LCD"));
        R4_LCD->setSegmentStyle(QLCDNumber::Flat);
        R4_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R4_LCD, 4, 1, 1, 1);

        R1_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R1_LCD->setObjectName(QStringLiteral("R1_LCD"));
        R1_LCD->setSegmentStyle(QLCDNumber::Flat);
        R1_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R1_LCD, 1, 1, 1, 1);

        R2_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R2_LCD->setObjectName(QStringLiteral("R2_LCD"));
        R2_LCD->setSegmentStyle(QLCDNumber::Flat);
        R2_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R2_LCD, 2, 1, 1, 1);

        R3_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R3_LCD->setObjectName(QStringLiteral("R3_LCD"));
        R3_LCD->setSegmentStyle(QLCDNumber::Flat);
        R3_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R3_LCD, 3, 1, 1, 1);

        R5_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R5_LCD->setObjectName(QStringLiteral("R5_LCD"));
        R5_LCD->setSegmentStyle(QLCDNumber::Flat);
        R5_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R5_LCD, 5, 1, 1, 1);

        R6_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R6_LCD->setObjectName(QStringLiteral("R6_LCD"));
        R6_LCD->setSegmentStyle(QLCDNumber::Flat);
        R6_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R6_LCD, 6, 1, 1, 1);

        R7_LCD = new QLCDNumber(horizontalLayoutWidget_2);
        R7_LCD->setObjectName(QStringLiteral("R7_LCD"));
        R7_LCD->setSegmentStyle(QLCDNumber::Flat);
        R7_LCD->setProperty("value", QVariant(65535));

        gridLayout_2->addWidget(R7_LCD, 7, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_2);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(-1, -1, -1, 100);
        label_10 = new QLabel(horizontalLayoutWidget_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_4->addWidget(label_10, 0, 0, 1, 1);

        label_12 = new QLabel(horizontalLayoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_4->addWidget(label_12, 2, 0, 1, 1);

        label_11 = new QLabel(horizontalLayoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_4->addWidget(label_11, 1, 0, 1, 1);

        label_15 = new QLabel(horizontalLayoutWidget_2);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 3, 0, 1, 1);

        ZFlagLCD = new QLCDNumber(horizontalLayoutWidget_2);
        ZFlagLCD->setObjectName(QStringLiteral("ZFlagLCD"));
        ZFlagLCD->setDigitCount(1);
        ZFlagLCD->setSegmentStyle(QLCDNumber::Flat);
        ZFlagLCD->setProperty("value", QVariant(0));
        ZFlagLCD->setProperty("intValue", QVariant(0));

        gridLayout_4->addWidget(ZFlagLCD, 1, 1, 1, 1);

        VFlagLCD = new QLCDNumber(horizontalLayoutWidget_2);
        VFlagLCD->setObjectName(QStringLiteral("VFlagLCD"));
        VFlagLCD->setDigitCount(1);
        VFlagLCD->setSegmentStyle(QLCDNumber::Flat);
        VFlagLCD->setProperty("value", QVariant(0));
        VFlagLCD->setProperty("intValue", QVariant(0));

        gridLayout_4->addWidget(VFlagLCD, 2, 1, 1, 1);

        CFlagLCD = new QLCDNumber(horizontalLayoutWidget_2);
        CFlagLCD->setObjectName(QStringLiteral("CFlagLCD"));
        CFlagLCD->setDigitCount(1);
        CFlagLCD->setSegmentStyle(QLCDNumber::Flat);
        CFlagLCD->setProperty("value", QVariant(1));
        CFlagLCD->setProperty("intValue", QVariant(1));

        gridLayout_4->addWidget(CFlagLCD, 3, 1, 1, 1);

        NFlagLCD = new QLCDNumber(horizontalLayoutWidget_2);
        NFlagLCD->setObjectName(QStringLiteral("NFlagLCD"));
        NFlagLCD->setDigitCount(1);
        NFlagLCD->setSegmentStyle(QLCDNumber::Flat);
        NFlagLCD->setProperty("value", QVariant(1));
        NFlagLCD->setProperty("intValue", QVariant(1));

        gridLayout_4->addWidget(NFlagLCD, 0, 1, 1, 1);


        horizontalLayout_2->addLayout(gridLayout_4);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        ScreenLabel->setText(QApplication::translate("MainWindow", "Screen here", 0));
        GoButton->setText(QApplication::translate("MainWindow", "Go", 0));
        StopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        StepButton->setText(QApplication::translate("MainWindow", "Step", 0));
        label_2->setText(QApplication::translate("MainWindow", "R0", 0));
        label_5->setText(QApplication::translate("MainWindow", "R3", 0));
        label_3->setText(QApplication::translate("MainWindow", "R1", 0));
        label_4->setText(QApplication::translate("MainWindow", "R2", 0));
        label_6->setText(QApplication::translate("MainWindow", "R4", 0));
        label_7->setText(QApplication::translate("MainWindow", "R5 (FP)", 0));
        label_8->setText(QApplication::translate("MainWindow", "R6 (SP)", 0));
        label_9->setText(QApplication::translate("MainWindow", "R7 (PC)", 0));
        label_10->setText(QApplication::translate("MainWindow", "N", 0));
        label_12->setText(QApplication::translate("MainWindow", "V", 0));
        label_11->setText(QApplication::translate("MainWindow", "Z", 0));
        label_15->setText(QApplication::translate("MainWindow", "C", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
