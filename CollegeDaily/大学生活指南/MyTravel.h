#pragma once
#include "afxcmn.h"


// CMyTravel �Ի���

class CMyTravel : public CDialogEx
{
	DECLARE_DYNAMIC(CMyTravel)

public:
	CMyTravel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyTravel();

// �Ի�������
	enum { IDD = IDD_MYTRAVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_travelTree;
	virtual BOOL OnInitDialog();

	HTREEITEM quxian;
	HTREEITEM temp_quxian[20];
	HTREEITEM scenic;
	afx_msg void OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
};
