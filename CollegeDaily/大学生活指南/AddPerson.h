#pragma once
#include "afxwin.h"


// CAddPerson �Ի���

class CAddPerson : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPerson)

public:
	CAddPerson(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddPerson();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedAdd();
	CButton Boy_ADD;
	CButton Girl_ADD;
	
};
