#include "CodeAutoBuild.h"
#include <QFileDialog>
#include <iostream>
#include <QDebug>
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
#include <QDesktopServices>
#include "code.h"
using namespace std;
#pragma execution_character_set("utf-8")
CodeAutoBuild::CodeAutoBuild(QWidget* parent)
	: QMainWindow(parent), ui(new Ui::CodeAutoBuild)
{
	
	ui->setupUi(this);
	setWindowTitle("自动布局插件");
	this->InitDir();
	this->doVsThread = new DoVsThread(this);
	ui->chooseDisplay->setIcon(QIcon(":/src/openfold.png"));
	ui->chooseSuite->setIcon(QIcon(":/src/openfold.png"));
	ui->vsDisplaybtn->setIcon(QIcon(":/src/openfold.png"));
	ui->vsSuitebtn->setIcon(QIcon(":/src/openfold.png"));

	ui->DisplayLineEdit->setCursorPosition(0);
	ui->SuiteLineEdit->setCursorPosition(0);
	ui->vsDisplayEdit->setCursorPosition(0);
	ui->vsSuiteEdit->setCursorPosition(0);

	ui->progressText->setText("程序未开始......");
/*	ui->textEdit->setEnabled(false);*/
	ui->textEdit->setReadOnly(true);
	ui->textEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);//不换行


	QIcon ico(":/bitbug.ico");
	setWindowIcon(ico);

	
	connect(ui->chooseDisplay, &QPushButton::clicked, this, [=]() {
		QString templateDisplayPath = ui->DisplayLineEdit->text();
		displayPath = QFileDialog::getExistingDirectory(this, "文件路径", "E:\\SCADE_Project\\R2020_SDY_Integration\\KCG_ORIGN\\DISPLAY");
		if (templateDisplayPath != displayPath)
		{
			ui->DisplayLineEdit->clear();
			//点击后必须选择文件夹，清除了m_vector
			ui->DisplayLineEdit->setText(displayPath);
		}
		});


	//选择Suite路径
	connect(ui->chooseSuite, &QPushButton::clicked, this, [=]() {

		QString templateSuitePath = ui->SuiteLineEdit->text();

		suitePath = QFileDialog::getExistingDirectory(this, "文件路径", "E:\\SCADE_Project\\R2020_SDY_Integration\\KCG_ORIGN\\SUITE");

		if (templateSuitePath != suitePath)
		{
			ui->SuiteLineEdit->clear();
			ui->SuiteLineEdit->setText(suitePath);

		}
		});
	//选择VSdisplay文件
	connect(ui->vsDisplaybtn, &QPushButton::clicked, this, [=]() {
		QString templateDislayPath = ui->vsSuiteEdit->text();

		vsDisplayPath = QFileDialog::getExistingDirectory(this, "KCG文件路径", "E:\\SCADE_Project\\R2020_SDY_Integration\\R2020_SDY_Integration\\KCG\\Display");

		if (templateDislayPath != vsDisplayPath)
		{
			ui->vsDisplayEdit->clear();
			ui->vsDisplayEdit->setText(vsDisplayPath);

			setvsProjectConfigFilePath(vsDisplayPath);

		}
		});

	//选择vsSuite文件夹
	connect(ui->vsSuitebtn, &QPushButton::clicked, this, [=]() {

		QString templatevsSuitePath = ui->vsSuiteEdit->text();
		QString vsSuitePath = QFileDialog::getExistingDirectory(this, "KCG文件路径", "E:\\SCADE_Project\\R2020_SDY_Integration\\R2020_SDY_Integration\\KCG\\Suite");

		if (templatevsSuitePath != vsSuitePath)
		{
			ui->vsSuiteEdit->clear();
			ui->vsSuiteEdit->setText(vsSuitePath);
		}

		});

	//点击生成按钮以后，线程启动。此时发送给线程相关的数据。触发display ,suite,vsdisplay,vssuite,scade路径的信号。
	connect(this, &CodeAutoBuild::readytorun, doVsThread, [=](QString _displayPath, QString _suitePath, QString _vsdisplayPath, QString _vsSuitePath,QString _FilePathInPlatform) {

		doVsThread->recPath(_displayPath, _suitePath, _vsdisplayPath, _vsSuitePath,_FilePathInPlatform);
		ui->progressText->setText("程序正在运行:");
		ui->runpushButton->setEnabled(false);
		ui->planecomboBox->setEnabled(false);
		ui->progresswidget->timer->start(100);
		ui->progresswidget->show();
		});

	//日志记录
	connect(doVsThread, &DoVsThread::sendLog, this, [=](QString str) {
		
		ui->textEdit->append(str);
		if (str=="程序已经执行完毕......")
		{
			ui->progressText->setText("程序已结束......");
			ui->runpushButton->setEnabled(true);
			ui->planecomboBox->setEnabled(true);
			ui->progresswidget->timer->stop();
			ui->progresswidget->hide();
		}
		});



	//错误对话框
	connect(doVsThread, &DoVsThread::sendMessagebox, this, [=](QString str) {

		QMessageBox::critical(this, "线程提示框", str);
		});
	//开始执行程序。线程启动
	connect(ui->runpushButton, &QPushButton::clicked, this, [=]() {

		ui->textEdit->clear();
	
		ui->textEdit->append("disPlay的路径为：" + displayPath + "\n");
		ui->textEdit->append("suite的路径为：" + suitePath + "\n");
		ui->textEdit->append("display的工程路径为：" + vsDisplayPath + "\n");
		ui->textEdit->append("suite的工程路径为：" + vssuitePath + "\n");
		ui->textEdit->append("vsProjectConfigFilePath的路径为：" + vsProjectConfigFilePath + "\n\n");

		ui->textEdit->append("请等待复制文件......");
		emit readytorun(displayPath,suitePath,vsDisplayPath,vssuitePath, FilePathInPlatform);
		doVsThread->start();
		});
	//关闭事件
	connect(this, &CodeAutoBuild::closedWidget, this, [=]() {
		
		doVsThread->quit();
		doVsThread->wait();
		doVsThread->deleteLater();
		});
}

CodeAutoBuild::~CodeAutoBuild()
{
	delete ui;

}
//初始化xml配置文件中路径给lineEdit
void CodeAutoBuild::InitDir()
{
	
	QFile file(":/src/DirConfig.xml");
	file.open(QIODevice::Text | QIODevice::ReadOnly);

	QDomDocument doc;
	doc.setContent(&file);

	QDomElement root = doc.firstChildElement("root");
	QDomElement AirCraftType;
	switch (ui->planecomboBox->currentIndex())
	{
	case DoVsThread::F35:

		AirCraftType = root.firstChildElement("F35");
		break;
	case DoVsThread::F22 :
		AirCraftType = root.firstChildElement("F22");
		break;
	case DoVsThread::F18:
		AirCraftType = root.firstChildElement("F18");
		break;
	default:
		break;
	}
	//读取Display生成的文件路径
	QDomElement DisplayPath_Ele = AirCraftType.firstChildElement("DisplayPath");
	ui->DisplayLineEdit->setText(DisplayPath_Ele.text());
	displayPath = ui->DisplayLineEdit->text();
	ui->textEdit->append("disPlay的路径为：" + displayPath+"\n");
	//读取Suite生成的文件路径
	QDomElement SuitePath_Ele = AirCraftType.firstChildElement("SuitePath");
	ui->SuiteLineEdit->setText(SuitePath_Ele.text());
	suitePath = ui->SuiteLineEdit->text();
	ui->textEdit->append("suite的路径为："  + suitePath+"\n");

	//读取VS中display的工程路径
	QDomElement VsConfig;
	if (ui->planecomboBox->currentIndex()!=0)
	{
		VsConfig = root.firstChildElement("VsConfig");
	}
	auto vsDisplay_Path_Ele = VsConfig.firstChildElement("vsDisplay_Path");
	ui->vsDisplayEdit->setText(vsDisplay_Path_Ele.text());
	vsDisplayPath = ui->vsDisplayEdit->text();
	ui->textEdit->append("VS中display的工程路径为：" + vsDisplayPath+"\n");

	//读取VS中vsProjectConfigFilePath的路径
	auto vsSuite_Path_Ele = VsConfig.firstChildElement("vsSuite_Path");
	ui->vsSuiteEdit->setText(vsSuite_Path_Ele.text());
	vssuitePath = ui->vsSuiteEdit->text();
	ui->textEdit->append("VS中suite的工程路径为：" + vssuitePath + "\n");

	//VS中vsProjectConfigFilePath的路径
	setvsProjectConfigFilePath(ui->vsDisplayEdit->text());
	ui->textEdit->append("VS中vsProjectConfigFilePath的路径为：" + vsProjectConfigFilePath + "\n\n");

	//平台中scade的路径
	QDomElement filepathinplatform = root.firstChildElement("FilePathInPlatform");
	auto _scadePath = filepathinplatform.firstChildElement("scadePath");
	FilePathInPlatform = filepathinplatform.text();
	ui->textEdit->append("平台中scade的路径为：" + FilePathInPlatform + "\n");

	file.close();
}
//根据DisPlay路径减去\\KCG\\DISPLAYR2020_SDY_Integration.vcxproj的路径
void CodeAutoBuild::setvsProjectConfigFilePath(QString dir)
{
	int num = dir.lastIndexOf("\\KCG\\DISPLAY", -1, Qt::CaseInsensitive);//忽略大小写
	this->vsProjectConfigFilePath = dir.left(num + 1);
	if (ui->planecomboBox->currentIndex()!=0)
	{
		this->vsProjectConfigFilePath += "R2020_SDY_Integration\\R2020_SDY_Integration.vcxproj";
	}
	else
	{
		this->vsProjectConfigFilePath = "";
	}

}

void CodeAutoBuild::closeEvent(QCloseEvent* event)
{
	emit closedWidget();
}

void CodeAutoBuild::on_planecomboBox_currentIndexChanged(int index)
{
	ui->textEdit->clear();
	InitDir();
	if (index==0)
	{
		ui->runpushButton->setEnabled(false);
		ui->runpushButton->setText("请点击上面选择机型");
	}
	else
	{
		ui->runpushButton->setEnabled(true);
		ui->runpushButton->setText("一键生成可执行程序"); 
	}
	this->doVsThread->recvPlaneFlag(index);
}

