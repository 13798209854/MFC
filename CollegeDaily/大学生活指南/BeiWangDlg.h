#pragma once
#include "afxcmn.h"


// CBeiWangDlg �Ի���

class CBeiWangDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBeiWangDlg)

public:
	CBeiWangDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBeiWangDlg();

// �Ի�������
	enum { IDD = IDD_BEIWANG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTreeCtrl m_beiwangTree;
	afx_msg void OnClickedSave();

	CString title;
	CString m_beiwang;
	
	afx_msg void OnDblclkTreeBeiwang(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedRemove();
	afx_msg void OnClickedClear();
};
