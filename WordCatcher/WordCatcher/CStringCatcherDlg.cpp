
// CStringCatcherDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "���������ҵ.h"
#include "CStringCatcherDlg.h"
#include "afxdialogex.h"
#include "CString"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <map>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CStringCatcherDlg::CStringCatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStringCatcherDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStringCatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStringCatcherDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SCAN, &CStringCatcherDlg::OnBnClickedScan)
	ON_BN_CLICKED(IDC_OPEN, &CStringCatcherDlg::OnBnClickedOpen)
END_MESSAGE_MAP()

// CStringCatcherDlg ��Ϣ�������

BOOL CStringCatcherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SkinH_Attach();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CStringCatcherDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CStringCatcherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStringCatcherDlg::OnBnClickedScan()
{
	//��ø�ѡ���ѡ��״̬
	CButton* pBtn = (CButton*)GetDlgItem(IDC_CHECK);   //��ȡ��ѡ��ָ��
	int state = pBtn->GetCheck();                      //ȡ��ѡ��״̬
	//��ȡ�ļ�
	CString path("");
	GetDlgItemText(IDC_PATH,path);                     //��ñ༭���ı�����·��
	ifstream getword(path);
	string text("");
	map<string,int> WordCatcher ;
	while(getword >> text)                             //��ȡ�ļ��ı�
	{
		if(text != "." && text != "," && text != "\"")
		{
			transform(text.begin(), text.end(), text.begin(), tolower);
			++WordCatcher[text];
		}
	}
	map<string,int>::iterator it = WordCatcher.begin();   //��������ʼλ�ÿ�ǰ
	getword.close();                                   //�ر��ļ��� 
	//�ų����ִ������ǰ10��
	int a[10] = {0};
	int i = 0;
	int temp = 0;
	CString result("");
	CString temp_string("");
	for ( ; i < 10; ++i)
	{
		if (state == 0)
		{
			for (it = WordCatcher.begin() ; it != WordCatcher.end(); ++it)
			{
				temp = it->second;
				if (temp > a[i])
				{
					a[i] = temp;
				}
			}
		}
		if (state ==1)
		{
			for (it = WordCatcher.begin(); it != WordCatcher.end(); ++it)
			{
				temp = it->second;
				if (it->first.compare("am") == 0 ||
					it->first.compare("is") == 0 ||
					it->first.compare("are") == 0 ||
					it->first.compare("i") == 0 ||
					it->first.compare("you") == 0 ||
					it->first.compare("she") == 0 ||
					it->first.compare("he") == 0 ||
					it->first.compare("and") == 0 )
				{
					it->second = 0;
					continue;
				}
				if (temp > a[i])
				{
					a[i] = temp;
				}
			}
		}
		for ( it = WordCatcher.begin(); it != WordCatcher.end(); ++it)
		{
			if (it->second == a[i])
			{
				char *temp_word = const_cast<char*>((it->first).c_str());
				CString temp_first(temp_word);
				temp_string.Format(_T("Top_%d: %s ���ִ���: %d \r\n" ), i+1, temp_first, a[i]);
				result = result + temp_string; //��Ϊ�༭����append,ֻ�б����ϴεĽ���ٴ�ӡ�˨r(�s���t)�q
				SetDlgItemText(IDC_RESULT,result);   //�������ս��
				it->second = 0;                   //���������Ϊ���´α�����ȡ����Ч���ֵ
				break;
			}
		}
	}

}

void CStringCatcherDlg::OnBnClickedOpen()
{
	TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||");
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString FilePath;
	if (IDOK == fileDlg.DoModal())
	{
		FilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_PATH, FilePath);
	}
}






