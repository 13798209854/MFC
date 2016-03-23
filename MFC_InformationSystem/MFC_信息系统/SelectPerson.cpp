// SelectPerson.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_ѧ����Ϣ����ϵͳ.h"
#include "SelectPerson.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "MFC_MainDlg.h"

// CSelectPerson �Ի���

IMPLEMENT_DYNAMIC(CSelectPerson, CDialogEx)

CSelectPerson::CSelectPerson(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelectPerson::IDD, pParent)
{                                                         
	
}

CSelectPerson::~CSelectPerson()
{
}

void CSelectPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOY, Boy_Select);
	DDX_Control(pDX, IDC_GIRL, Girl_Select);
}


BEGIN_MESSAGE_MAP(CSelectPerson, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT_OK, &CSelectPerson::OnClickedSelectOk)
END_MESSAGE_MAP()


// CSelectPerson ��Ϣ�������


void CSelectPerson::OnClickedSelectOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMFC_MainDlg *p = (CMFC_MainDlg*)AfxGetApp()->m_pMainWnd;    //��ȡ������Ӧ��ʵ��
	CString sql_DDL;  
	GetDlgItemText(IDC_SELECT_NAME,Select_Name);                 //�������������ı�
	GetDlgItemText(IDC_SELECT_TEL,Select_Tel);					 //�������ĵ绰�ı�
	GetDlgItemText(IDC_SELECT_EMAIL,Select_Email);				 //�������������ı�
	if (Boy_Select.GetCheck() == 1)								 //��ѡ���Ա�Ϊ��
	{
		Select_Sex = "��";
	}
	if (Girl_Select.GetCheck() == 1)							 //��ѡ���Ա�ΪŮ
	{
		Select_Sex = "Ů";
	}
	if (Select_Name.IsEmpty() && Select_Sex.IsEmpty() && Select_Tel.IsEmpty() && Select_Email.IsEmpty()) //�ж��Ƿ�ʲô��û������
	{
		MessageBox(_T("ʲô��û������."),_T("��ѯ����"),MB_OK|MB_ICONERROR);
		return;
	}
	ADO sql;
	sql.OnInitADOConn();		//��ʼ�����ݿ�����
	sql.initRecordset();		//������¼��ʵ��
	sql_DDL.Format(_T("select * from PersonInfo where ���� like '%%%s%%' and �Ա� like'%%%s%%'\
					                              and �绰 like'%%%s%%' and ���� like'%%%s%%'"),\
		                                          Select_Name,Select_Sex,Select_Tel,Select_Email);   //ģ����ѯsql���
	try
	{
		sql.m_pReset->Open((_bstr_t)sql_DDL,sql.m_pConn.GetInterfacePtr(),\
			                                adOpenDynamic,adLockOptimistic,adCmdText); //�򿪲��ҽ����¼��
		p->m_ListCtrl.DeleteAllItems();                                                //�����ϸ��Ϣ�б�(ListControl)
		while (!sql.m_pReset->adoEOF)											//����¼��ָ�벻����ĩβ��ִ��ѭ��
		{
			p->m_ListCtrl.InsertItem(0,_T(""));                                                      //������
			p->m_ListCtrl.SetItemText(0,0,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("ID"));       //����ID����Ϣ
			p->m_ListCtrl.SetItemText(0,1,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����"));	 //������������Ϣ
			p->m_ListCtrl.SetItemText(0,2,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("�Ա�"));	 //�����Ա�����Ϣ
			p->m_ListCtrl.SetItemText(0,3,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("�绰"));	 //���õ绰����Ϣ
			p->m_ListCtrl.SetItemText(0,4,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("����"));	 //������������Ϣ
			p->m_ListCtrl.SetItemText(0,5,(LPCTSTR)(_bstr_t)sql.m_pReset->GetCollect("���ڷ���")); //�������ڷ�������Ϣ
			sql.m_pReset->MoveNext();															 //��¼������
		}
		sql.CloseConn();		       //�ر����ݿ�����
		CSelectPerson::OnCancel();     //Ĭ�ϰ���ȡ����ť�����ԹرնԻ���
		CString tempstr;
		p->GetDlgItemText(IDC_MOREINFO,tempstr);  //��ȡ��ǰ������Ϣ��ť�ı������ж��Ƿ񱻵����
		if (tempstr == "��ϸ��Ϣ >>")             //�ж��Ƿ��е����ϸ��Ϣ��ť
		{ 
			p->OnClickedMoreinfo();               //��û�а�����ϸ��Ϣ��ť,Ĭ�ϰ���.û�������ô�����������0-0..
		}
	}
	catch(...)
	{
		MessageBox(_T("���Һ��ѳ�����!(���n��) "),_T("���Һ���"),MB_OK|MB_ICONERROR);
		return;
	}


}
