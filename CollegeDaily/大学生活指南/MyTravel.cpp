// MyTravel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "MyTravel.h"
#include "afxdialogex.h"
#include "ADO.h"

// CMyTravel �Ի���

IMPLEMENT_DYNAMIC(CMyTravel, CDialogEx)

CMyTravel::CMyTravel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyTravel::IDD, pParent)
{

}

CMyTravel::~CMyTravel()
{
}

void CMyTravel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_travelTree);
}


BEGIN_MESSAGE_MAP(CMyTravel, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CMyTravel::OnDblclkTree)
END_MESSAGE_MAP()


// CMyTravel ��Ϣ�������


BOOL CMyTravel::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString quxian_name;
	CString scenic_name;
	int count = 0;

	ADO sql;
	_bstr_t sql_DDL_GroupList = "select * from �������� order by ID";        //sql���
	sql.OnInitADOConn();                                                 //��ʼ�����ݿ�����
	sql.initRecordset();                                                 //������¼��ʵ��
	sql.m_pReset->Open(sql_DDL_GroupList,sql.m_pConn.GetInterfacePtr(),    \
		adOpenDynamic,adLockOptimistic,adCmdText);
	while (!sql.m_pReset->adoEOF)                                         //����¼��ָ�벻����ĩβ��ִ��ѭ��
	{                                                                     //����Ҫ�Ȳ������з���	
	    quxian_name = (LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("������");
		temp_quxian[count] = m_travelTree.InsertItem(quxian_name); 
		count++;
		sql.m_pReset->MoveNext();                                         //��¼������һλ
	}
	sql.CloseRecordset();                                                 //�رռ�¼��                   
	_bstr_t sql_DDL_PersonInfo = "select * from ���� order by ID";  //SQL���
	sql.m_pReset->Open(sql_DDL_PersonInfo,sql.m_pConn.GetInterfacePtr(),   \
		adOpenDynamic,adLockOptimistic,adCmdText);
	while (!sql.m_pReset->adoEOF)                                         //��¼��ָ�벻����ĩβʱִ��ѭ��
	{
		quxian_name = (char*)(_bstr_t)sql.m_pReset->GetCollect("������");
	    scenic_name = (char*)(_bstr_t)sql.m_pReset->GetCollect("������"); 
		for (int i = 0; i < count; ++i)                                  //ѭ�����������
		{
			if (m_travelTree.GetItemText(temp_quxian[i]) == quxian_name) 
			{
				m_travelTree.InsertItem(scenic_name,temp_quxian[i]);                     
				break;                                //�������ܿ���һ��Ҫbreakһ�£���Ȼ�������ѭ��
			}
		}
		sql.m_pReset->MoveNext();                                       //��¼����
	}
	sql.CloseConn();   //�Ͽ����ݿ�����
	return TRUE;
}

void CMyTravel::OnDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HTREEITEM CurrentFocus = m_travelTree.GetSelectedItem();
	if (!m_travelTree.ItemHasChildren(CurrentFocus) && \
		!m_travelTree.GetItemText(m_travelTree.GetParentItem(CurrentFocus)).IsEmpty())  
	{
		CString senic_name = m_travelTree.GetItemText(CurrentFocus);
		CString ticket;
		CString transport;
		CString info;
		ADO sql;
		sql.OnInitADOConn();
		sql.initRecordset();
		CString sql_DDL;
		sql_DDL.Format(_T("select * from ���� where ������ = '%s'"),senic_name);
		sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),\
			                    adOpenDynamic,adLockOptimistic,adCmdText); 
		ticket = (char*)(_bstr_t)sql.m_pReset->GetCollect("��Ʊ��Ϣ");
		transport = (char*)(_bstr_t)sql.m_pReset->GetCollect("��ͨ·��");
		info = (char*)(_bstr_t)sql.m_pReset->GetCollect("�������");
		sql.CloseConn();
		SetDlgItemText(IDC_READ_TICKET,ticket);
		SetDlgItemText(IDC_READ_TRANS,transport);
		SetDlgItemText(IDC_READ_INFO,info);
	}
}
