#pragma once
#include "afxwin.h"


// CAlterPerson �Ի���

class CAlterPerson : public CDialogEx
{
	DECLARE_DYNAMIC(CAlterPerson)

public:
	CAlterPerson(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAlterPerson();

// �Ի�������
	enum { IDD = IDD_ALTER_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedEnsureAlter();
	CString Alter_Name;
	CString Alter_Sex;
	CString Alter_Tel;
	CString Alter_Email;
	CButton Boy_Selected;
//	CButton Girl_Selected;
	virtual BOOL OnInitDialog();     //��ӵĶԻ����ʼ���麯��
	CEdit CEdit_Name;
	CEdit CEdit_Tel;
	CEdit CEdit_Email;
	CButton Girl_Selected;
};
