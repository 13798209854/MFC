#pragma once
#include "afxwin.h"


// CReWrite �Ի���

class CReWrite : public CDialogEx
{
	DECLARE_DYNAMIC(CReWrite)

public:
	CReWrite(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReWrite();

// �Ի�������
	enum { IDD = IDD_REWRITE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedRewrite();
	CEdit CEdit_Name;
	CButton Boy_Selected;
	CButton Girl_Selected;
	CEdit CEdit_Tel;
	CEdit CEdit_Email;

	CString Alter_Name;
	CString Alter_Sex;
	CString Alter_Tel;
	CString Alter_Email;
	virtual BOOL OnInitDialog();
};
