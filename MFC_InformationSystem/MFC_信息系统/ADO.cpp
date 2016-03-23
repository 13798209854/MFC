#include "stdafx.h"
#include "ADO.h"


ADO::ADO(void)
{
	m_pConn = NULL;
	m_pReset = NULL;
}

ADO::~ADO(void)
{
}

BOOL ADO::OnInitADOConn()
{
	::CoInitialize(NULL);   //  ��ʼ��COM ����
	try 
	{
		m_pConn.CreateInstance(_T("ADODB.Connection"));    //�������Ӷ���ʵ��
		_bstr_t strConn=_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=stu_mdb.mdb;Jet OLEDB:DataBase Password=admin");//�����ַ���
		m_pConn->Open(strConn,"","",adModeUnknown);      //�������ݿ�
		return TRUE;
	}
	catch(_com_error e)      //��ʱ��������Ĵ��Ȳ���e....�뱨�������������e.Description()��e.ErrorMessage();
	{
		CString err = _T("");
		err.Format(_T("���ݿ����ӳ���!"));
		return false;
	}
}

void ADO::initRecordset()   //�����ݼ�
{
	try
	{
		m_pReset.CreateInstance(_T("ADODB.Recordset"));  //������¼��ʵ��
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("�򿪼�¼��ʧ��!"));
		return;
	}
}

void ADO::CloseRecordset()
{
	try
	{
		if (m_pReset->GetState() == adStateOpen)     //�жϼ�¼����״̬�Ƿ�Ϊ��
		{
			m_pReset->Close();                       //�رռ�¼��
		}
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("�رռ�¼������!"));
	}
}
 
void ADO::CloseConn()
{
	if (m_pConn->GetState() == adStateOpen)        //�ж����ݿ������Ƿ�Ϊ��
	{
		m_pConn->Close();						   //�Ͽ����ݿ����� 
	}
	::CoUninitialize();          //�ͷ�COM����
}

