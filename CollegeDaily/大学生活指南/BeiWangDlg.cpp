// BeiWangDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "BeiWangDlg.h"
#include "afxdialogex.h"
#include "ADO.h"

// CBeiWangDlg �Ի���

IMPLEMENT_DYNAMIC(CBeiWangDlg, CDialogEx)

CBeiWangDlg::CBeiWangDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBeiWangDlg::IDD, pParent)
{

}

CBeiWangDlg::~CBeiWangDlg()
{
}

void CBeiWangDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_BEIWANG, m_beiwangTree);
}


BEGIN_MESSAGE_MAP(CBeiWangDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SAVE, &CBeiWangDlg::OnClickedSave)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE_BEIWANG, &CBeiWangDlg::OnDblclkTreeBeiwang)
	ON_BN_CLICKED(IDC_REMOVE, &CBeiWangDlg::OnClickedRemove)
	ON_BN_CLICKED(IDC_CLEAR, &CBeiWangDlg::OnClickedClear)
END_MESSAGE_MAP()


// CBeiWangDlg ��Ϣ�������


BOOL CBeiWangDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ADO sql;
	_bstr_t sql_DDL_GroupList = "select * from BeiWang order by ID";     //sql���
	sql.OnInitADOConn();                                                 //��ʼ�����ݿ�����
	sql.initRecordset();                                                 //������¼��ʵ��
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(),    \
		adOpenDynamic,adLockOptimistic,adCmdText);
	CString temp;
	while (!sql.m_pReset->adoEOF)                                         //����¼��ָ�벻����ĩβ��ִ��ѭ��
	{   
		temp = (char*)(_bstr_t)sql.m_pReset->GetCollect("����¼��");
		m_beiwangTree.InsertItem(temp);
		sql.m_pReset->MoveNext();                                     //��¼������һλ
	}
	sql.CloseConn();
	return TRUE;
}

void CBeiWangDlg::OnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetDlgItemText(IDC_EDIT_TEXT,m_beiwang);
	GetDlgItemText(IDC_EDIT_BEIWANGNAME,title);
	ADO sql;
	sql.OnInitADOConn();												   //��ʼ�����ݿ�����	
	sql.initRecordset();												   //������¼��ʵ��
	_bstr_t sql_DDL_GroupList = "select * from BeiWang";				   //sql���
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(), \
		adOpenDynamic,adLockOptimistic,adCmdText);   
	try
	{
		sql.m_pReset->AddNew();														 //�������
		sql.m_pReset->PutCollect("����¼��",(char*)(_bstr_t)title);           //����õ��ı��������ݿ�
		sql.m_pReset->PutCollect("����¼",(char*)(_bstr_t)m_beiwang);
		m_beiwangTree.InsertItem(title);                                 
		sql.m_pReset->Update();														 //�������ݿ�
		sql.CloseConn();															 //�ر����ݿ�����
		SetDlgItemText(IDC_EDIT_BEIWANGNAME,_T(""));
		SetDlgItemText(IDC_EDIT_TEXT,_T(""));
	}
	catch(...)
	{
		MessageBox(_T("��ӱ���¼��������(���n��) "));
		return;
	}
}

void CBeiWangDlg::OnDblclkTreeBeiwang(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
 	CString temp_title;
	temp_title = m_beiwangTree.GetItemText(m_beiwangTree.GetSelectedItem());
	ADO sql;
	CString sql_DDL;
	sql_DDL.Format(_T("select * from BeiWang where ����¼�� = '%s'"),temp_title);  //sql���
	sql.OnInitADOConn();                                                 //��ʼ�����ݿ�����
	sql.initRecordset();                                                 //������¼��ʵ��
	sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),    \
		adOpenDynamic,adLockOptimistic,adCmdText);
	SetDlgItemText(IDC_EDIT_BEIWANGNAME,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����¼��"));
	SetDlgItemText(IDC_EDIT_TEXT,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����¼"));
	sql.CloseConn();
}

void CBeiWangDlg::OnClickedRemove()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString Select_name = m_beiwangTree.GetItemText(m_beiwangTree.GetSelectedItem());
	ADO sql;
	sql.OnInitADOConn();                                                             
	sql.initRecordset();
	CString sql_DDL;
	sql_DDL.Format(_T("delete from BeiWang where ����¼�� = '%s'"),Select_name);
	sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),
		adOpenDynamic,adLockOptimistic,adCmdText);
	sql.CloseConn();
	m_beiwangTree.DeleteAllItems();
	SetDlgItemText(IDC_EDIT_BEIWANGNAME,_T(""));
	SetDlgItemText(IDC_EDIT_TEXT,_T(""));
	this->OnInitDialog();
}

void CBeiWangDlg::OnClickedClear()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SetDlgItemText(IDC_EDIT_TEXT,_T(""));
	SetDlgItemText(IDC_EDIT_BEIWANGNAME,_T(""));
}
