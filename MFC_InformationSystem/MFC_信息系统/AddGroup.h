#pragma once


// CAddGroup �Ի���

class CAddGroup : public CDialogEx
{
	DECLARE_DYNAMIC(CAddGroup)

public:
	CAddGroup(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddGroup();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedAddGroup();
};
