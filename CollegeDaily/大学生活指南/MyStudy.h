#pragma once
#include "afxcmn.h"


// CMyStudy �Ի���

class CMyStudy : public CDialogEx
{
	DECLARE_DYNAMIC(CMyStudy)

public:
	CMyStudy(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyStudy();

// �Ի�������
	enum { IDD = IDD_MYSTUDY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_studyTree;
//	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit2();
	afx_msg void OnClickedAddStudy();
	afx_msg void OnClickedRemove();
//	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);

	HTREEITEM xueyuan;
	HTREEITEM temp_xuyuan[13];
	HTREEITEM course;

	virtual BOOL OnInitDialog();
};
