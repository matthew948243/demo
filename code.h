#ifndef CODE_H
#define CODE_H

#include <QWidget>
#pragma once
#include <fstream>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <io.h>
#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;
#pragma execution_character_set("utf-8")
class code: public QWidget
{
    Q_OBJECT
public:

    code();
	//文件的代码修改
//遍历文件夹，并更新vector
	int findfileAndPushbackVector(string dir);
	//更新picture
	void textchangefunc(string filepath, string findstr, string addstr, string addbehind);
	vector<string> m_vector;
	string fiepath;
   
signals:
    void sendFileLog(QString log);
};

#endif // CODE_H
