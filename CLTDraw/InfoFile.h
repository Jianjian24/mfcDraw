#pragma once

#include <fstream>
#include <iostream>
#include <string>

#define CIRCLE 0
#define RECTANGLE 1
#define _F_PARAM "./param.txt"

using namespace std;

typedef struct
{
	UINT shape; // ��״ Բ 0 ������ 1 ��: CIRCLE 0 RECTANGLE 1
	UINT lengthOrRad; // �߳���뾶
	UINT x; // ���ĵ� x
	UINT y; // ���ĵ� y
	UINT speed; // �ٶ�
}Msg;

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	// ���ز�������
	void LoadInfo();

	// ����ǰ�������ñ��浽�ļ���
	void SaveInfo();

	// ���ڱ������������Ϣ
	Msg msg;
};

