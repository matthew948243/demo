
#pragma once
#include "code.h"

code::code()
{

  
}

//遍历文件中的C文件
int code::findfileAndPushbackVector(string dir )
{
    fiepath = dir;
    m_vector.clear();
    int m = 0;
    std::string inPath =dir+"/*.c" ;//遍历文件夹下的所有.MP3文件,支持输入路径，支持通配符*等
    /*ofstream outfile("d:\\out.txt", ios::app); //写追加模式,路径与名字可以自定义*/																			//用于查找的句柄
    intptr_t handle;
    struct _finddata_t fileinfo;
    //第一次查找
    handle = _findfirst(inPath.c_str(), &fileinfo);

    if (handle == -1)
    {
        m = 0;
        return m;
    }

    do
    {
        //找到的文件的文件名
        /*outfile << fileinfo.name;*/
        ifstream ifs;

        /*outfile << endl;*/
        m++;
        m_vector.push_back(fileinfo.name);

    } while (!_findnext(handle, &fileinfo));

    _findclose(handle);

    return m;
}
void code::textchangefunc(string filepath, string findstr, string addstr,string addbehind)
{

    ifstream ifs;
    /*string str{};*/
    ifs.open(filepath, ios::in);
    ofstream ofs;
    string newpath = filepath + "01";
    ofs.open(newpath, ios::out | ios::trunc);
    ofs.clear();
    int flag = -1;
    int ret = -1;
    string buffer = {};

    while (getline(ifs,buffer))//while (!ifs.eof())||while(ifs>>str)//遇到空格和tab就中断//用这种方式会忽略空格等
    {
        /*ifs >> str;*///遇到空格和tab就中断//用这种方式会忽略空格等

        ret = buffer.find(findstr, 0);
        if (ret != -1)
        {
            QString str = QString("查找的字符串：") + QString::fromStdString(findstr);
            emit sendFileLog(str);
            flag = 1;
        }
        if (flag == 1)
        {
            int ret1 = buffer.find(addbehind, 0);
            if (ret1 != -1)
            {
				QString str = QString("查找的标识字符串：") + QString::fromStdString(addbehind);
				emit sendFileLog(str);
                buffer += addstr;
                flag = -1;
            }

        }

        ofs << buffer << endl;
    }
    ifs.close();
    ofs.close();
    remove(filepath.c_str());//remove中的函数是char*;所以需要转为c_str；//如果出现不明确的函数，可以尝试改变语言标准
    int fileret = rename(newpath.c_str(), filepath.c_str());
 
}

