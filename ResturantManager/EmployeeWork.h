#pragma once


// CEmployeeWork �Ի���

class CEmployeeWork : public CDialogEx
{
	DECLARE_DYNAMIC(CEmployeeWork)

public:
	CEmployeeWork(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEmployeeWork();

// �Ի�������
	enum { IDD = IDD_EMPLOY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	_RecordsetPtr m_ptr;

	virtual BOOL OnInitDialog();
};
