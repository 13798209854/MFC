#pragma once
#include "afxwin.h"


// CAddPersonDlg �Ի���

class CAddPersonDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPersonDlg)

public:
	CAddPersonDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddPersonDlg();

// �Ի�������
	enum { IDD = IDD_ADDPERSON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedAddOk();
	CButton Boy_ADD;
	CButton Girl_ADD;
};
