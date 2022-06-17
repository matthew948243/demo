#include "codeThread.h"

DoVsThread::DoVsThread(QObject* parent)
{
	this->PlaneFlag = -1;
	connect(&displayCode, &code::sendFileLog, this, [=](QString str) {
		emit sendLog(str);
		});

	connect(&suiteCode, &code::sendFileLog, this, [=](QString str) {
		emit sendLog(str);
		 });

}

DoVsThread::~DoVsThread()
{
		
}

void DoVsThread::SRC_Init()
{
	m_src.clear();
	m_src.push_back("..\\SRC\\animation.c");
	switch (PlaneFlag)
	{
		case F35 :
		{
			m_src.push_back("..\\SRC\\DisplayData_F35.c");
		}
		break;
		case F22:
		{
			m_src.push_back("..\\SRC\\DisplayData_F22.c");
		}
		break;
		case F18:
		{
			m_src.push_back("..\\SRC\\DisplayData_F18.c");
		}
		break;
	default:
		break;
	}
	m_src.push_back("..\\SRC\\log.c");
	m_src.push_back("..\\SRC\\main_glut.c");
	m_src.push_back("..\\SRC\\manage_errors.c");
	m_src.push_back("..\\SRC\\picture.c");
	m_src.push_back("..\\SRC\\SCADE_ChineseFont.c");
	m_src.push_back("..\\SRC\\Socket.c");
	m_src.push_back("..\\SRC\\specific.c");
	m_src.push_back("..\\SRC\\split.c");
	m_src.push_back("..\\Utils\\oglxLoadBinaryFonts.c");
	m_src.push_back("..\\Utils\\oglxReadBinaryFonts.c");
	m_src.push_back("..\\Utils\\oglxReadErrors.c");





}

void DoVsThread::run()
{
	this->SRC_Init();

	this->copy_ANSYSCode_to_VS();

	vsconfigFunc();

	vsFilterConfig();

	vscodecontentChange();

	VSCompile();

	copyScadeToPlatform();

	



}

void DoVsThread::copy_ANSYSCode_to_VS()
{
	emit sendLog("*********************************************\n");
	

	emit sendLog("display中的文件开始复制\n");
	copyFiles(displayPath, vsDisplayPath);

	emit sendLog("*********************************************\n");
	emit sendLog("suite中的文件开始复制\n");

	copyFiles(suitePath, vsSuitePath);

}

void DoVsThread::recPath(QString _displayPath, QString _suitePath, QString _vsdisplayPath, QString _vsSuitePath, QString _FilePathInPlatform)
{
	displayPath = _displayPath;
	suitePath = _suitePath;
	vsDisplayPath = _vsdisplayPath;
	vsSuitePath = _vsSuitePath;
	FilePathInPlatform = _FilePathInPlatform;
	displayCode.findfileAndPushbackVector(displayPath.toStdString());

	if (displayCode.m_vector.size()<1)
	{
		sendMessagebox("display的工程文件有问题，请检查");
		sendLog("display的工程文件有问题，请检查");
		this->quit();
		return;
	}

	suiteCode.findfileAndPushbackVector(suitePath.toStdString());

	if (displayCode.m_vector.size() < 1)
	{
		sendMessagebox("suite的工程文件有问题，请检查");
		sendLog("suite的工程文件有问题，请检查");
		this->quit();
		return;
	}


	int num = vsDisplayPath.lastIndexOf("\\KCG\\DISPLAY", -1, Qt::CaseInsensitive);

	vsProjectConfigFilePath = vsDisplayPath.left(num + 1);
	vsProjectConfigFilePath += "R2020_SDY_Integration";

}

bool DoVsThread::deleteFiles(QString toDir)
{
	QFileInfo toDirInfo(toDir);
	QDir targetDir(toDir);

	QFileInfoList fileInfoList = targetDir.entryInfoList();

	for each (QFileInfo fileInfo in fileInfoList)
	{
		targetDir.remove(fileInfo.fileName());

		emit sendLog(fileInfo.fileName());
	}

	return true;

}

bool DoVsThread::copyFiles(QString fromDir, QString toDir)
{
	deleteFiles(toDir);
	QDir sourceDir(fromDir);
	QFileInfoList fileInfoList = sourceDir.entryInfoList();
	for each (QFileInfo fileInfo in fileInfoList)
	{
		
		if (fileInfo.isFile()&&(fileInfo.suffix()=='c'|| fileInfo.suffix() == 'h'))
		{
			QString des = toDir + "\\" + fileInfo.fileName();
			QString src = fileInfo.path() + "\\" + fileInfo.fileName();

			QFile::copy(src, des);

			emit sendLog(fileInfo.fileName());
		}

	}
	return true;
}

void DoVsThread::vsconfigFunc()
{

	QString strPath = vsProjectConfigFilePath + "\\R2020_SDY_Integration.xml";
	QFile Config_xml(strPath);
	Config_xml.open(QIODevice::Text | QIODevice::ReadOnly);// | QFile::Truncate//QIODevice::ReadOnly???
 
	QDomDocument doc;
	doc.setContent(&Config_xml);
	Config_xml.close();//后面再次打开，再写
	
	


	QDomElement root = doc.documentElement();//返回根节点

	QDomElement Project = doc.firstChildElement("Project");
	bool flag = false;
	auto ItemGroup = Project.firstChildElement("ItemGroup");

	while (!ItemGroup.isNull())
	{

		auto ClCompile = ItemGroup.firstChildElement("ClCompile");

		if (!ClCompile.isNull())
		{
			flag = true;
			QDomNodeList nodelist = ItemGroup.childNodes();
			int num = nodelist.count();

			while (nodelist.size() > 0)
			{
				ItemGroup.removeChild(nodelist.at(0));
			}
	
			  //修改display的工程配置文件
			for (size_t i = 0; i < displayCode.m_vector.size(); i++)
			{
				//排除"kcg_consts.c"和"kcg_types.c"
				if ((displayCode.m_vector[i] == "kcg_consts.c") || (displayCode.m_vector[i] == "kcg_types.c"))
				{
					continue;
				}
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += "..\\KCG\\DISPLAY\\";
				str += displayCode.m_vector[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);
			}
			//修改suite的工程配置文件
			for (size_t i = 0; i < suiteCode.m_vector.size(); i++)
			{
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += "..\\KCG\\SUITE\\";
				str += suiteCode.m_vector[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);
			}
			//修改src工程配置文件
			for (size_t i = 0; i < m_src.size(); i++)
			{
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += m_src[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);
			}

		}

		ItemGroup = ItemGroup.nextSiblingElement("ItemGroup");//nextSibling()
	}

	//如果最终都没有发现则表明工程有问题
	if (!flag)
	{
		emit sendLog("工程源文件有问题");
	}

	strPath = vsProjectConfigFilePath + "\\R2020_SDY_Integration.vcxproj";
	QFile xml(strPath);
	xml.open(QIODevice::Text |QIODevice::Truncate| QIODevice::WriteOnly);
	QTextStream outfile(&xml);

	outfile.reset();
	outfile.setCodec("UTF - 8");
	doc.save(outfile, 2);//VS中的缩进是2//是编码格式的问题

	xml.close();
	
}

void DoVsThread::vsFilterConfig()
{

	QFile Config_xml(vsProjectConfigFilePath + "\\R2020_SDY_Integration.filters.xml");
	Config_xml.open(QIODevice::Text | QIODevice::ReadOnly);

	QDomDocument doc;
	doc.setContent(&Config_xml);
	Config_xml.close();//后面再次打开，再写




	QDomElement root = doc.documentElement();//返回根节点

	QDomElement Project = doc.firstChildElement("Project");
	bool flag = false;
	auto ItemGroup = Project.firstChildElement("ItemGroup");

	while (!ItemGroup.isNull())
	{

		auto ClCompile = ItemGroup.firstChildElement("ClCompile");

		if (!ClCompile.isNull())
		{
			flag = true;
			QDomNodeList nodelist = ItemGroup.childNodes();
			int num = nodelist.count();

			while (nodelist.size() > 0)
			{
				ItemGroup.removeChild(nodelist.at(0));
			}

			//修改display的Filter
			for (size_t i = 0; i < displayCode.m_vector.size(); i++)
			{
				//排除"kcg_consts.c"和"kcg_types.c"
				if ((displayCode.m_vector[i] == "kcg_consts.c") || (displayCode.m_vector[i] == "kcg_types.c"))
				{
					continue;
				}
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += "..\\KCG\\DISPLAY\\";
				str += displayCode.m_vector[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);

				//Filter

				QDomElement Filter = doc.createElement("Filter");

				Filter.appendChild(doc.createTextNode("kcg\\Display"));

				ClCompile.appendChild(Filter);
			}
			
			//修改suite的工程配置文件
			for (size_t i = 0; i < suiteCode.m_vector.size(); i++)
			{
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += "..\\KCG\\SUITE\\";
				str += suiteCode.m_vector[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);



				//Filter

				QDomElement Filter = doc.createElement("Filter");

				Filter.appendChild(doc.createTextNode("kcg\\Suite"));

				ClCompile.appendChild(Filter);

			}


		
			//修改src工程配置文件
			for (size_t i = 0; i < m_src.size(); i++)
			{
				QDomElement ClCompile = doc.createElement("ClCompile");
				string str = "";
				str += m_src[i];
				ClCompile.setAttribute("Include", QString::fromStdString(str));
				ItemGroup.appendChild(ClCompile);


				//Filter

				QDomElement Filter = doc.createElement("Filter");

				if ((m_src.at(i)=="..\\Utils\\oglxLoadBinaryFonts.c")|| (m_src.at(i) == "..\\Utils\\oglxReadBinaryFonts.c")
					|| (m_src.at(i) == "..\\Utils\\oglxReadErrors.c"))
				{

					Filter.appendChild(doc.createTextNode("Utils"));
				}
				else
				{
					Filter.appendChild(doc.createTextNode("SRC"));
				}


				ClCompile.appendChild(Filter);

			}

		}

		ItemGroup = ItemGroup.nextSiblingElement("ItemGroup");//nextSibling()
	}

	//如果最终都没有发现则表明工程有问题
	if (!flag)
	{
		emit sendLog("工程配置文件有问题");
	}


	QFile xml(vsProjectConfigFilePath + "\\R2020_SDY_Integration.vcxproj.filters");
	xml.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly);
	QTextStream outfile(&xml);

	outfile.reset();
	outfile.setCodec("UTF - 8");
	doc.save(outfile, 2);//VS中的缩进是2//是编码格式的问题

	xml.close();
}

void DoVsThread::vscodeF35contentChange()
{

	string filepath0, filepath;
	filepath0 = vsDisplayPath.toStdString();


	filepath = filepath0 + "\\aol_ASR_Full.c";
	displayCode.textchangefunc(filepath, "(aol_ASR_Full_G_ASR_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(1);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_ASR_Exto.c";
	displayCode.textchangefunc(filepath, "(aol_ASR_Exto_G_ASR_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(1);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_ASR_Tripple_Up.c";
	displayCode.textchangefunc(filepath, "(aol_ASR_Tripple_Up_G_ASR_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(1);\n", "sglEnd()");


	filepath = filepath0 + "\\aol_SRCH_Full.c";
	displayCode.textchangefunc(filepath, "(aol_SRCH_Full_G_SRCH_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(2);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_SRCH_Exto.c";
	displayCode.textchangefunc(filepath, "(aol_SRCH_Exto_G_SRCH_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(2);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_SRCH_Tripple_Up.c";
	displayCode.textchangefunc(filepath, "(aol_SRCH_Tripple_Up_G_SRCH_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(2);\n", "sglEnd()");


	filepath = filepath0 + "\\aol_TSD1_Full.c";
	displayCode.textchangefunc(filepath, "(aol_TSD1_Full_G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_TSD1_Exto_.c";
	displayCode.textchangefunc(filepath, "(aol_TSD1_Exto__G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_TSD1_Tripple_Up.c";
	displayCode.textchangefunc(filepath, "(aol_TSD1_Tripple_Up_G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");

	filepath = filepath0 + "\\aol_Up_Screen.c";
	displayCode.textchangefunc(filepath, "(aol_Up_Screen_G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");

	//F_35Logic_display_adaptor.c文件中添加DisplayStepFunc();

	string f_logic =vsSuitePath.toStdString();
	f_logic += "\\F_35Logic_display_adaptor.c";
	suiteCode.textchangefunc(f_logic, "Step(void)", "\nDisplayStepFunc();\n", "ConnectSuiteToDisplay()");

	emit sendLog("*********************************************\n");


	/*#include "DisplayData_F35.h"
	aol_typ_symbology_layer * p_symbology_layer_ctx;*/
	ofstream ofs;
	filepath = filepath0 + "\\aol_symbology_layer.h";
	ofs.open(filepath, ios::out | ios::app);
	ofs << "\n\n#include \"DisplayData_F35.h\"" << endl
		<< "extern aol_typ_symbology_layer * p_symbology_layer_ctx;\n" << endl;
	ofs.close();
	
}

void DoVsThread::vscodeF22contentChange()
{

	string filepath0, filepath;
	filepath0 = vsDisplayPath.toStdString();


	filepath = filepath0 + "\\aol_ASR_Full.c";
	displayCode.textchangefunc(filepath, "(aol_ASR_Full_G_ASR_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(1);\n", "sglEnd()");



	filepath = filepath0 + "\\aol_SRCH_Full.c";
	displayCode.textchangefunc(filepath, "(aol_SRCH_Full_G_SRCH_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(2);\n", "sglEnd()");


	filepath = filepath0 + "\\aol_TSD1_Full.c";
	displayCode.textchangefunc(filepath, "(aol_TSD1_Full_G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");



	//F_35Logic_display_adaptor.c文件中添加DisplayStepFunc();

	string f_logic = vsSuitePath.toStdString();
	f_logic += "\\HMI_Logic_display_adaptor.c";
	suiteCode.textchangefunc(f_logic, "Step(void)", "\nDisplayStepFunc();\n", "ConnectSuiteToDisplay()");

	emit sendLog("*********************************************\n");


	/*#include "DisplayData_F35.h"
	aol_typ_symbology_layer * p_symbology_layer_ctx;*/



	ofstream ofs;
	filepath = filepath0 + "\\aol_symbology_layer.h";
	ofs.open(filepath, ios::out | ios::app);
	ofs << "\n\n#include \"DisplayData_F22.h\"" << endl
		<< "extern aol_typ_symbology_layer * p_symbology_layer_ctx;\n" << endl;
	ofs.close();
}

void DoVsThread::vscodeF18contentChange()
{

	string filepath0, filepath;
	filepath0 = vsDisplayPath.toStdString();


	filepath = filepath0 + "\\aol_ASR_Full.c";
	displayCode.textchangefunc(filepath, "(aol_ASR_Full_G_ASR_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(1);\n", "sglEnd()");



	filepath = filepath0 + "\\aol_SRCH_Full.c";
	displayCode.textchangefunc(filepath, "(aol_SRCH_Full_G_SRCH_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(2);\n", "sglEnd()");


	filepath = filepath0 + "\\aol_TSD1_Full.c";
	displayCode.textchangefunc(filepath, "(aol_TSD1_Full_G_TSD1_Pic_Visi", "\nsglDisable(SGL_TEXTURE_2D);\nShowPic(3);\n", "sglEnd()");



	//F_35Logic_display_adaptor.c文件中添加DisplayStepFunc();

	string f_logic = vsSuitePath.toStdString();
	f_logic += "\\HMI_Logic_display_adaptor.c";
	suiteCode.textchangefunc(f_logic, "Step(void)", "\nDisplayStepFunc();\n", "ConnectSuiteToDisplay()");

	emit sendLog("*********************************************\n");


	/*#include "DisplayData_F35.h"
	aol_typ_symbology_layer * p_symbology_layer_ctx;*/



	ofstream ofs;
	filepath = filepath0 + "\\aol_symbology_layer.h";
	ofs.open(filepath, ios::out | ios::app);
	ofs << "\n\n#include \"DisplayData_F18.h\"" << endl
		<< "extern aol_typ_symbology_layer * p_symbology_layer_ctx;\n" << endl;
	ofs.close();
}

void DoVsThread::vscodecontentChange()
{

	switch (PlaneFlag)
	{
		case F35 :
		{
			vscodeF35contentChange();
		}
		break;
		case F22:
		{
			vscodeF22contentChange();
		}
		break;
		case F18:
		{
			vscodeF18contentChange();
		}
		break;
	default:
		break;
	}
}

void DoVsThread::VSCompile()
{
	emit sendLog("请等待工程编译......");
	QProcess p(nullptr);
	int num = vsDisplayPath.lastIndexOf("\\KCG\\DISPLAY", -1, Qt::CaseInsensitive);

	QString batPath = vsDisplayPath.left(num + 1);
	p.setWorkingDirectory(batPath);
	QString command = batPath + "\BuildDebug.bat";

	p.start(command);
	p.waitForFinished();

	emit sendLog("程序已经执行完毕......");
	
	QString path = "";
	num = vsDisplayPath.lastIndexOf("\\KCG\\DISPLAY", -1, Qt::CaseInsensitive);
	path = vsDisplayPath.left(num + 1);

	path += "\Debug";

	emit sendLog("*********************************************\n");

	emit sendLog("最终的文件路径为	" + path);


	QString	filePath = "file:///" + path;
	QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));

}

void DoVsThread::recvPlaneFlag(int flag)
{
	this->PlaneFlag = flag;
}

void DoVsThread::copyScadeToPlatform()
{
	QString ExceName = "default.exe";
	switch (PlaneFlag)
	{

	case F35:
	{
		ExceName = "F35.exe";
	}
	break;
	case F22:
	{
		ExceName = "F22.exe";
	}
	break;
	case F18:
	{
		ExceName = "F18.exe";
	}
	break;

	default:
		break;
	}




	QString path = "";
	int num = vsDisplayPath.lastIndexOf("\\KCG\\DISPLAY", -1, Qt::CaseInsensitive);
	path = vsDisplayPath.left(num + 1);

	path += "Debug";


	QDir sourceDir(path);
	QDir targetDir(FilePathInPlatform);

	QString des = FilePathInPlatform + "\\" + ExceName;
	if (targetDir.exists(des))
	{

		targetDir.remove(des);
	}


	QString src = path + "\\" + "R2020_SDY_Integration.exe";

	if (sourceDir.exists(src))
	{
		QFile::copy(src, FilePathInPlatform + "\\" + ExceName);
		emit sendLog("*********************************************\n");

		emit sendLog("已经成功完成exe的生成\n");
	}
}
