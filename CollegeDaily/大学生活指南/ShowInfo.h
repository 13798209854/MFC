#pragma once


// CShowInfo �Ի���

class CShowInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CShowInfo)

public:
	CShowInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CShowInfo();

// �Ի�������
	enum { IDD = IDD_SHOWINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


public:
	CString Show_Name;
	CString Show_Sex;
	CString Show_Tel;
	CString Show_Email;
	afx_msg void OnClickedOk();
};
