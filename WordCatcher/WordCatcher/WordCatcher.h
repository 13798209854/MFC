
// ���������ҵ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CStringCatcherApp:
// �йش����ʵ�֣������ ���������ҵ.cpp
//

class CStringCatcherApp : public CWinApp
{
public:
	CStringCatcherApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStringCatcherApp theApp;