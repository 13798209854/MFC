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
	enum { IDD = IDD_SELECT_PERSON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton Boy_Select;
	CButton Girl_Select;
	afx_msg void OnClickedSelectOk();
	CString Select_Name;
	CString Select_Sex;
	CString Select_Tel;
	CString Select_Email;
};
