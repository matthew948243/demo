#ifndef CODEAUTOBUILD_H
#define CODEAUTOBUILD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CodeAutoBuild; }
QT_END_NAMESPACE
#pragma once

#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include "ui_CodeAutoBuild.h"
#include <string>
#include "code.h"
#include "codeThread.h"
#include "MyProgressBar.h"
#pragma execution_character_set("utf-8")
class CodeAutoBuild : public QMainWindow
{
    Q_OBJECT

public:
    CodeAutoBuild(QWidget *parent = Q_NULLPTR);
    ~CodeAutoBuild();
    QString displayPath;
    QString suitePath;
    QString vsProjectConfigFilePath;
    QString vsDisplayPath;
    QString vssuitePath;
    QString FilePathInPlatform;
    DoVsThread* doVsThread;

    //默认初始化文件路径
    void InitDir();
    //通过..KCG//DISPLAY路径查找\R2020_SDY_Integration\R2020_SDY_Integration\R2020_SDY_Integration.vcxproj
    void setvsProjectConfigFilePath(QString dir);

    void closeEvent(QCloseEvent* event);
    
signals:
    void readytorun(QString _displayPath, QString _suitePath, QString _vsdisplayPath, const QString _vsSuitePath,const QString _FilePathInPlatform);
    void closedWidget();
 public slots:
    void on_planecomboBox_currentIndexChanged(int index);
private:
    Ui::CodeAutoBuild *ui;
};

#endif // CODEAUTOBUILD_H
