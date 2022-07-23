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
	ifstream ifs(_F_PARAM); // ���뷽ʽ���ļ�

	char buf[1024] = { 0 };

	ifs.getline(buf, sizeof(buf)); // �ѱ�ͷ������
	ifs.getline(buf, sizeof(buf)); // ��ȡһ��

	char *sst = strtok(buf, "|"); // �ԡ�|���и�
	if (sst != NULL)
	{
		msg.shape  = atoi(sst); // ��һ����״�����Ķ�ȡ
	}
	else
	{
		ifs.close(); //�ر��ļ�
		TRACE("\nû��⵽���в���\n");
		return;
	}
	sst = strtok(NULL, "|");
	msg.lengthOrRad = atoi(sst);//�߳���뾶

	sst = strtok(NULL, "|");
	msg.x = atoi(sst);	//x

	sst = strtok(NULL, "|");
	msg.y = atoi(sst);	//y

	sst = strtok(NULL, "|");
	msg.speed = atoi(sst);	//�ٶ�

	ifs.close(); //�ر��ļ�
}

void CInfoFile::SaveInfo()
{
	ofstream ofs(_F_PARAM);//�����ʽ���ļ�
	ofs << "��״|�߳���뾶|X|Y|�ٶ�" << endl; //д���ͷ
	ofs << msg.shape << "|";
	ofs << msg.lengthOrRad << "|";
	ofs << msg.x << "|";
	ofs << msg.y << "|";
	ofs << msg.speed << endl;

	ofs.close();
}
