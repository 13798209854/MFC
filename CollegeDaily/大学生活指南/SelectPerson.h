#pragma once
#include "afxwin.h"


// CSelectPerson �Ի���

class CSelectPerson : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectPerson)

public:
	CSelectPerson(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSelectPerson();

// �Ի�������
	enum { IDD = IDD_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedFind();
	CButton Girl_Select;
	CButton Boy_Select;

	CString Select_Name;
	CString Select_Sex;
	CString Select_Tel;
	CString Select_Email;
};
