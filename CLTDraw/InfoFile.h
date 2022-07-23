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
	UINT shape; // 形状 圆 0 正方形 1 宏: CIRCLE 0 RECTANGLE 1
	UINT lengthOrRad; // 边长或半径
	UINT x; // 中心点 x
	UINT y; // 中心点 y
	UINT speed; // 速度
}Msg;

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	// 加载参数配置
	void LoadInfo();

	// 将当前参数配置保存到文件里
	void SaveInfo();

	// 用于保存参数配置信息
	Msg msg;
};

