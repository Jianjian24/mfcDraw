
// CLTDraw.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCLTDrawApp: 
// �йش����ʵ�֣������ CLTDraw.cpp
//

class CCLTDrawApp : public CWinApp
{
public:
	CCLTDrawApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCLTDrawApp theApp;