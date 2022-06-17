/********************************************************************************
** Form generated from reading UI file 'MyProgressBar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYPROGRESSBAR_H
#define UI_MYPROGRESSBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyProgressBar
{
public:
    QGridLayout *gridLayout;

    void setupUi(QWidget *MyProgressBar)
    {
        if (MyProgressBar->objectName().isEmpty())
            MyProgressBar->setObjectName(QString::fromUtf8("MyProgressBar"));
        MyProgressBar->resize(400, 300);
        gridLayout = new QGridLayout(MyProgressBar);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        retranslateUi(MyProgressBar);

        QMetaObject::connectSlotsByName(MyProgressBar);
    } // setupUi

    void retranslateUi(QWidget *MyProgressBar)
    {
        MyProgressBar->setWindowTitle(QCoreApplication::translate("MyProgressBar", "MyProgressBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyProgressBar: public Ui_MyProgressBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYPROGRESSBAR_H
