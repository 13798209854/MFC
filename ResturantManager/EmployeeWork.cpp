// EmployeeWork.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��������.h"
#include "EmployeeWork.h"
#include "afxdialogex.h"


// CEmployeeWork �Ի���

extern CMyApp theApp;

IMPLEMENT_DYNAMIC(CEmployeeWork, CDialogEx)

CEmployeeWork::CEmployeeWork(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEmployeeWork::IDD, pParent)
{

}

CEmployeeWork::~CEmployeeWork()
{
}

void CEmployeeWork::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEmployeeWork, CDialogEx)
END_MESSAGE_MAP()


// CEmployeeWork ��Ϣ�������




BOOL CEmployeeWork::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString Sql="select * from login";
	//	((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST)).SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_ptr = theApp.m_pCon->Execute((_bstr_t)Sql,NULL,adCmdText);

	((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST))->InsertColumn(0,_T("Ա������"),LVCFMT_CENTER,80);
	((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST))->InsertColumn(1,_T("�������۶�"),LVCFMT_CENTER,120);
	while(!m_ptr->adoEOF)
	{
		((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST))->InsertItem(0,_T(""));
//		TheValue=(char*)(_bstr_t)m_ptr->GetCollect("Uname");
//		TheValue1=(char*)(_bstr_t)m_ptr->GetCollect("�������۶�");
		((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST))->SetItemText(0,0,(char*)(_bstr_t)m_ptr->GetCollect("Uname"));
		((CListCtrl*)GetDlgItem(IDC_EMPLOYEE_LIST))->SetItemText(0,1,(char*)(_bstr_t)m_ptr->GetCollect("�������۶�"));
		m_ptr->MoveNext();
	}
	return TRUE;
}
