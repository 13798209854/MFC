
// ��ѧ����ָ��.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C��ѧ����ָ��App:
// �йش����ʵ�֣������ ��ѧ����ָ��.cpp
//

class C��ѧ����ָ��App : public CWinApp
{
public:
	C��ѧ����ָ��App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C��ѧ����ָ��App theApp;