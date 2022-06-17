#pragma once
#pragma execution_character_set("utf-8")
#include <QObject>
#include <QThread>
#include <cstdio>
#include <stdio.h>
#include <io.h>
#include <string>
#include<fstream>
#include <QTextStream>
#include <QtXml>
#include <QDebug>
#include <QMessageBox>
#include <QDomNode>
#include <QFileInfoList>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileInfo>
#include <QMainWindow>
#include <QDialog>
#include "code.h"
class DoVsThread : public QThread
{
	Q_OBJECT
public:
	enum MyEnum
	{
		F35 = 1,
		F22,
		F18
	};
public:
	DoVsThread(QObject* parent);
	~DoVsThread();
	void SRC_Init();
signals:
	void finishedCopy(QString fileName);
	void sendLog(QString log);
	void compileFinished();
	void sendMessagebox(QString mesg);
protected:
	void run() override;
public:
	//向文件夹中复制文件夹
	void copy_ANSYSCode_to_VS();
	void recPath(QString _displayPath, QString _suitePath, QString _vsdisplayPath, QString _vsSuitePath, QString _FilePathInPlatform);
	bool deleteFiles(QString toDir);
	bool copyFiles(QString fromDir, QString toDir);
	void vsconfigFunc();
	void vsFilterConfig();
	void vscodeF35contentChange();
	void vscodeF22contentChange();
	void vscodeF18contentChange();
	void vscodecontentChange();
	void VSCompile();
	void recvPlaneFlag(int flag);
	//向平台中复制文件R2020_SDY_Integration.exe
	void copyScadeToPlatform();
protected:
	QString displayPath;
	QString suitePath;
	QString vsDisplayPath;
	QString vsSuitePath;
	QString vsProjectConfigFilePath;
	QString FilePathInPlatform;
	code displayCode;
	code suiteCode;
	vector<string> m_src;
	int PlaneFlag;

};
