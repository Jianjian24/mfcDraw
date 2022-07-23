#include "stdafx.h"
#include "InfoFile.h"
#include <iosfwd>


CInfoFile::CInfoFile()
{
}


CInfoFile::~CInfoFile()
{
}

void CInfoFile::LoadInfo()
{
	ifstream ifs(_F_PARAM); // 输入方式打开文件

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); // 把表头给读掉
	ifs.getline(buf, sizeof(buf)); // 读取一行

	char *sst = strtok(buf, "|"); // 以“|”切割
	if (sst != NULL)
	{
		msg.shape  = atoi(sst); // 第一个形状参数的读取
	}
	else
	{
		ifs.close(); //关闭文件
		TRACE("\n没检测到已有参数\n");
		return;
	}
	sst = strtok(NULL, "|");
	msg.lengthOrRad = atoi(sst);//边长或半径

	sst = strtok(NULL, "|");
	msg.x = atoi(sst);	//x

	sst = strtok(NULL, "|");
	msg.y = atoi(sst);	//y

	sst = strtok(NULL, "|");
	msg.speed = atoi(sst);	//速度

	ifs.close(); //关闭文件
}

void CInfoFile::SaveInfo()
{
	ofstream ofs(_F_PARAM);//输出方式打开文件
	ofs << "形状|边长或半径|X|Y|速度" << endl; //写入表头
	ofs << msg.shape << "|";
	ofs << msg.lengthOrRad << "|";
	ofs << msg.x << "|";
	ofs << msg.y << "|";
	ofs << msg.speed << endl;

	ofs.close();
}
