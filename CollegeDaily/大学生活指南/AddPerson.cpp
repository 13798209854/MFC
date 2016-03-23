// AddPerson.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ѧ����ָ��.h"
#include "AddPerson.h"
#include "afxdialogex.h"
#include "ADO.h"
#include "PersonInfo.h"
#include "MyFriend.h"

// CAddPerson �Ի���

IMPLEMENT_DYNAMIC(CAddPerson, CDialogEx)

CAddPerson::CAddPerson(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPerson::IDD, pParent)
{

}

CAddPerson::~CAddPerson()
{
}

void CAddPerson::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOY, Boy_ADD);
	DDX_Control(pDX, IDC_GIRL, Girl_ADD);
}


BEGIN_MESSAGE_MAP(CAddPerson, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &CAddPerson::OnClickedAdd)
END_MESSAGE_MAP()


// CAddPerson ��Ϣ�������


void CAddPerson::OnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PersonInfo m_person;                                                     //����һ��PersonInfo����
	CMyFriend *p = (CMyFriend*)this->GetParent();
	GetDlgItemText(IDC_EDIT_NAME,p->str_Name);                               //�������б�ؼ�(TreeControl)ָ���ȡTextBox�༭������Name
	GetDlgItemText(IDC_EDIT_NAME,m_person.per_Name);                         //����ϸ��Ϣ�ؼ�(ListControl)ָ���ȡTextBox�༭������Name
	GetDlgItemText(IDC_EDIT_TEL,m_person.per_Tel);                           //��ȡTextBox�༭�ĵ绰Tel
	GetDlgItemText(IDC_EDIT_EMAIL,m_person.per_Email);                       //��ȡTextBox�༭������Email
	if (m_person.per_Name.IsEmpty())
	{
		MessageBox(_T("���ֲ���Ϊ��Ӵ~"),_T("��Ӻ��ѳ�����"),MB_OK|MB_ICONERROR);
		return;
	}
	if (m_person.per_Tel.IsEmpty())
	{
		m_person.per_Tel = _T("δ֪");
	}
	if (m_person.per_Email.IsEmpty())
	{
		m_person.per_Email = _T("δ֪");
	}
	if (Boy_ADD.GetCheck() == 1)			//�ж��Ƿ�ѡ����
	{
		m_person.per_Sex = "��";
	}
	if (Girl_ADD.GetCheck() == 1)			//�ж��Ƿ�ѡ��Ů
	{
		m_person.per_Sex = "Ů";
	}
	if (p->m_Tree.GetSelectedItem() == NULL)                  //�ж�ѡ�е��ĸ�����
	{
		p->m_CurrentFocus = p->m_DefalutFocus;                       //����û��ѡ������"�ҵĺ���"�б������
		m_person.per_Group = p->m_Tree.GetItemText(p->m_CurrentFocus);                     
	}
	else
	{
		p->m_CurrentFocus = p->m_Tree.GetSelectedItem();
		m_person.per_Group = p->m_Tree.GetItemText(p->m_CurrentFocus);   //��ȡ��ѡ�еķ��������
	}

	try           //���������ļ��
	{
		ADO sql;
		sql.OnInitADOConn();
		sql.initRecordset();
		CString sql_DDL_ensure;
		sql_DDL_ensure.Format(_T("select * from PersonInfo where ����='%s'"),m_person.per_Name);//��֤sql���,����޸ĺ��������������ֹ�޸�
		sql.m_pReset->Open((_bstr_t)sql_DDL_ensure,sql.m_pConn.GetInterfacePtr(),\
			adOpenStatic,adLockOptimistic,adCmdText);//����֤sql����ҵ��ļ�¼��,ע�������Ǿ�̬��,
													 //���������������ado����ڿͻ���ʹ�õ�ǰ��ֻ���α꣬
													 //���޷����ؽ������������ֻ�ܷ��أ�1
		if (sql.m_pReset->GetRecordCount() != 0)	 //�ж�sql������ü�¼���Ƿ��м�¼
		{
			MessageBox(_T("�������Ѵ���,Ϊ�����Ϻ�׺���ǲ����ѡ��ӴO(��_��)O"),_T("�޸ĺ�����Ϣ"),
				MB_OK|MB_ICONERROR);
			sql.CloseConn();
			return;
		}
	}
	catch(...)
	{
		MessageBox(_T("������ӵ����Ѿ�������~(���n��),ΪTA��ӵ��׺���ְ�~"),_T("��Ӻ���"),
			MB_OK|MB_ICONERROR);
		return;
	}

	p->m_Tree.InsertItem(p->str_Name,p->m_CurrentFocus);      //������б�ѡ�еķ���������������

	try
	{	
		ADO sql2;
		sql2.OnInitADOConn();               //��ʼ�����ݿ�����
		sql2.initRecordset();               //������¼��ʵ��
		_bstr_t sql_DDL = "select * from PersonInfo";							//sql���
		sql2.m_pReset->Open(sql_DDL,sql2.m_pConn.GetInterfacePtr(),\
			adOpenDynamic,adLockOptimistic,adCmdText);     //��PersonInfo���ݼ�
		sql2.m_pReset->AddNew();                                           //���ݿ������
		sql2.m_pReset->PutCollect("����",(_bstr_t)m_person.per_Name);      //���������в�������
		sql2.m_pReset->PutCollect("�Ա�",(_bstr_t)m_person.per_Sex);       //���Ա����в����Ա�
		sql2.m_pReset->PutCollect("�绰",(_bstr_t)m_person.per_Tel);       //��绰���������绰
		sql2.m_pReset->PutCollect("����",(_bstr_t)m_person.per_Email);     //���������в�������
		sql2.m_pReset->PutCollect("���ڷ���",(_bstr_t)m_person.per_Group); //�����ڷ������в������ڷ���
		sql2.m_pReset->Update();                                           //�������ݱ�
		sql2.CloseConn();												  //�ر�����
	}
	catch(...)
	{
		MessageBox(_T("��ӳ�����!(���n��)"));
		return;
	}
	p->m_List.DeleteAllItems();                                  //ɾ����CListControl����������������¸���,Ϊ�˷�ֹ���һ��
	p->ShowAllPerson();                                              //����ʾ
	CAddPerson::OnCancel();        
	
}
