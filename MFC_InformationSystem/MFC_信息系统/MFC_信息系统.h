
// MFC_ѧ����Ϣ����ϵͳ.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_MainApp:
// �йش����ʵ�֣������ MFC_ѧ����Ϣ����ϵͳ.cpp
//

class CMFC_MainApp : public CWinApp
{
public:
	CMFC_MainApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_MainApp theApp;