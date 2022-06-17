/********************************************************************************
** Form generated from reading UI file 'CodeAutoBuild.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEAUTOBUILD_H
#define UI_CODEAUTOBUILD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myprogressbar.h"

QT_BEGIN_NAMESPACE

class Ui_CodeAutoBuild
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *SuiteLineEdit;
    QTextEdit *textEdit;
    QLineEdit *DisplayLineEdit;
    QPushButton *runpushButton;
    QPushButton *chooseDisplay;
    QComboBox *planecomboBox;
    QPushButton *vsDisplaybtn;
    QLineEdit *vsDisplayEdit;
    QLineEdit *vsSuiteEdit;
    QPushButton *chooseSuite;
    QPushButton *vsSuitebtn;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *progressText;
    MyProgressBar *progresswidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CodeAutoBuild)
    {
        if (CodeAutoBuild->objectName().isEmpty())
            CodeAutoBuild->setObjectName(QString::fromUtf8("CodeAutoBuild"));
        CodeAutoBuild->resize(800, 558);
        centralwidget = new QWidget(CodeAutoBuild);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        SuiteLineEdit = new QLineEdit(centralwidget);
        SuiteLineEdit->setObjectName(QString::fromUtf8("SuiteLineEdit"));
        SuiteLineEdit->setMinimumSize(QSize(500, 0));

        gridLayout->addWidget(SuiteLineEdit, 2, 0, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMinimumSize(QSize(700, 0));
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        font.setWeight(50);
        textEdit->setFont(font);

        gridLayout->addWidget(textEdit, 7, 0, 1, 2);

        DisplayLineEdit = new QLineEdit(centralwidget);
        DisplayLineEdit->setObjectName(QString::fromUtf8("DisplayLineEdit"));
        DisplayLineEdit->setMinimumSize(QSize(500, 0));

        gridLayout->addWidget(DisplayLineEdit, 1, 0, 1, 1);

        runpushButton = new QPushButton(centralwidget);
        runpushButton->setObjectName(QString::fromUtf8("runpushButton"));
        runpushButton->setEnabled(false);
        runpushButton->setMinimumSize(QSize(700, 60));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(14);
        runpushButton->setFont(font1);

        gridLayout->addWidget(runpushButton, 8, 0, 1, 2);

        chooseDisplay = new QPushButton(centralwidget);
        chooseDisplay->setObjectName(QString::fromUtf8("chooseDisplay"));
        chooseDisplay->setMinimumSize(QSize(250, 0));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/openfold.png"), QSize(), QIcon::Normal, QIcon::Off);
        chooseDisplay->setIcon(icon);

        gridLayout->addWidget(chooseDisplay, 1, 1, 1, 1);

        planecomboBox = new QComboBox(centralwidget);
        planecomboBox->addItem(QString());
        planecomboBox->addItem(QString());
        planecomboBox->addItem(QString());
        planecomboBox->addItem(QString());
        planecomboBox->setObjectName(QString::fromUtf8("planecomboBox"));

        gridLayout->addWidget(planecomboBox, 0, 0, 1, 1);

        vsDisplaybtn = new QPushButton(centralwidget);
        vsDisplaybtn->setObjectName(QString::fromUtf8("vsDisplaybtn"));
        vsDisplaybtn->setMinimumSize(QSize(200, 0));
        vsDisplaybtn->setIcon(icon);

        gridLayout->addWidget(vsDisplaybtn, 4, 1, 2, 1);

        vsDisplayEdit = new QLineEdit(centralwidget);
        vsDisplayEdit->setObjectName(QString::fromUtf8("vsDisplayEdit"));
        vsDisplayEdit->setMinimumSize(QSize(500, 0));

        gridLayout->addWidget(vsDisplayEdit, 3, 0, 2, 1);

        vsSuiteEdit = new QLineEdit(centralwidget);
        vsSuiteEdit->setObjectName(QString::fromUtf8("vsSuiteEdit"));
        vsSuiteEdit->setMinimumSize(QSize(500, 0));

        gridLayout->addWidget(vsSuiteEdit, 5, 0, 2, 1);

        chooseSuite = new QPushButton(centralwidget);
        chooseSuite->setObjectName(QString::fromUtf8("chooseSuite"));
        chooseSuite->setMinimumSize(QSize(200, 0));
        chooseSuite->setIcon(icon);

        gridLayout->addWidget(chooseSuite, 2, 1, 2, 1);

        vsSuitebtn = new QPushButton(centralwidget);
        vsSuitebtn->setObjectName(QString::fromUtf8("vsSuitebtn"));
        vsSuitebtn->setMinimumSize(QSize(200, 0));
        vsSuitebtn->setIcon(icon);

        gridLayout->addWidget(vsSuitebtn, 6, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 25));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        progressText = new QLabel(frame);
        progressText->setObjectName(QString::fromUtf8("progressText"));
        progressText->setMinimumSize(QSize(150, 0));
        progressText->setMaximumSize(QSize(150, 16777215));
        progressText->setFont(font1);
        progressText->setTextFormat(Qt::AutoText);
        progressText->setScaledContents(false);

        horizontalLayout->addWidget(progressText);

        progresswidget = new MyProgressBar(frame);
        progresswidget->setObjectName(QString::fromUtf8("progresswidget"));
        progresswidget->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(progresswidget);


        verticalLayout->addWidget(frame);

        CodeAutoBuild->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CodeAutoBuild);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        CodeAutoBuild->setMenuBar(menubar);
        statusbar = new QStatusBar(CodeAutoBuild);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CodeAutoBuild->setStatusBar(statusbar);

        retranslateUi(CodeAutoBuild);

        QMetaObject::connectSlotsByName(CodeAutoBuild);
    } // setupUi

    void retranslateUi(QMainWindow *CodeAutoBuild)
    {
        CodeAutoBuild->setWindowTitle(QCoreApplication::translate("CodeAutoBuild", "CodeAutoBuild", nullptr));
        runpushButton->setText(QCoreApplication::translate("CodeAutoBuild", "\344\270\200\351\224\256\347\224\237\346\210\220\345\217\257\346\211\247\350\241\214\347\250\213\345\272\217", nullptr));
        chooseDisplay->setText(QCoreApplication::translate("CodeAutoBuild", "\351\200\211\346\213\251Display\346\226\207\344\273\266\345\244\271", nullptr));
        planecomboBox->setItemText(0, QCoreApplication::translate("CodeAutoBuild", "\346\234\272\345\236\213\351\200\211\346\213\251", nullptr));
        planecomboBox->setItemText(1, QCoreApplication::translate("CodeAutoBuild", "F-35", nullptr));
        planecomboBox->setItemText(2, QCoreApplication::translate("CodeAutoBuild", "F-22", nullptr));
        planecomboBox->setItemText(3, QCoreApplication::translate("CodeAutoBuild", "F-18", nullptr));

        vsDisplaybtn->setText(QCoreApplication::translate("CodeAutoBuild", "\351\200\211\346\213\251VS\345\267\245\347\250\213Display\346\226\207\344\273\266\345\244\271", nullptr));
        chooseSuite->setText(QCoreApplication::translate("CodeAutoBuild", "\351\200\211\346\213\251Suite\346\226\207\344\273\266\345\244\271", nullptr));
        vsSuitebtn->setText(QCoreApplication::translate("CodeAutoBuild", "\351\200\211\346\213\251VS\345\267\245\347\250\213Suite\346\226\207\344\273\266\345\244\271", nullptr));
        progressText->setText(QCoreApplication::translate("CodeAutoBuild", "\347\250\213\345\272\217\350\277\233\350\241\214\344\270\255\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeAutoBuild: public Ui_CodeAutoBuild {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEAUTOBUILD_H
