// ShowInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_ѧ����Ϣ����ϵͳ.h"
#include "ShowInfo.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "MFC_MainDlg.h"

// CShowInfo �Ի���

IMPLEMENT_DYNAMIC(CShowInfo, CDialogEx)

CShowInfo::CShowInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShowInfo::IDD, pParent)
{

}

CShowInfo::~CShowInfo()
{
}

void CShowInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CShowInfo, CDialogEx)
END_MESSAGE_MAP()


// CShowInfo ��Ϣ�������


BOOL CShowInfo::OnInitDialog()          //�����麯��_�Ի����ʼ������
{
	CDialogEx::OnInitDialog();

	CMFC_MainDlg *p = (CMFC_MainDlg*)AfxGetApp()->m_pMainWnd; //��ȡ���Ի���Ӧ��ʵ��
	CString Target_Person = p->m_TreeControl.GetItemText(p->m_TreeControl.GetSelectedItem()); //��ȡѡ�к��ѵ��ı�(����)
	try
	{
		ADO sql;
		sql.OnInitADOConn();         //��ʼ�����ݿ�����
		sql.initRecordset();		 //�������ݼ�ʵ��
		CString sql_DDL;
		sql_DDL.Format(_T("select * from PersonInfo where ����='%s'"),Target_Person);  //��ѯѡ�еĺ�����Ϣ
		sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),\
			                                adOpenDynamic,adLockOptimistic,adCmdText); //�����ü�¼��
		Show_Name = (char*)(_bstr_t)sql.m_pReset->GetCollect("����");       //�õ�������Ϣ
		Show_Sex = (char*)(_bstr_t)sql.m_pReset->GetCollect("�Ա�");		//�õ��Ա���Ϣ
		Show_Tel = (char*)(_bstr_t)sql.m_pReset->GetCollect("�绰");		//�õ��绰��Ϣ
		Show_Email = (char*)(_bstr_t)sql.m_pReset->GetCollect("����");		//�õ�������Ϣ
		SetDlgItemText(IDC_SHOW_NAME,Show_Name);        //������ʾ����
		SetDlgItemText(IDC_SHOW_SEX,Show_Sex);			//������ʾ�Ա�
		SetDlgItemText(IDC_SHOW_TEL,Show_Tel);			//������ʾ�绰
		SetDlgItemText(IDC_SHOW_EMAIL,Show_Email);		//������ʾ����
		sql.CloseConn();		    //�ر����ݿ�����
	}
	catch(...)
	{
		MessageBox(_T("˫����ʾ������Ϣʱ������.�ѩn�� "),_T("��ʾ������Ϣ"),MB_OK|MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}
