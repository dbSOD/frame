// AccountDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Console.h"
#include "AccountDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <thread>
// CAccountDlg �Ի���

IMPLEMENT_DYNAMIC(CAccountDlg, CDialogEx)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAccountDlg::IDD, pParent)
	, m_userName(_T(""))
	, m_password(_T(""))
{
	m_shareMemSer.reset(new shareMemorySer(MORE_OPEN_NUMBER));
}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTACCOUNT, m_listCtl);
	DDX_Text(pDX, IDC_EDIT1, m_userName);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAccountDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAccountDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAccountDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAccountDlg ��Ϣ��������


// ��ʼ��������Ϣ
bool CAccountDlg::initTables()
{
	//���÷��

	DWORD dwStyle = m_listCtl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// ѡ��ĳ��ʹ���и�����ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_GRIDLINES;// �����ߣ�ֻ������report ����listctrl �� 
	dwStyle |= LVS_EX_CHECKBOXES;//item ǰ����checkbox �ؼ� 
	m_listCtl.SetExtendedStyle(dwStyle); // ������չ��� 

	//��ʼ����ͷ
	int i = 0;
	m_listCtl.InsertColumn(i++, "Pid", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "�û���", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "����", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "��ǰ�ű�", LVCFMT_LEFT, 80);

	//����MORE_OPEN_NUM��

	for (int i= 0; i < MORE_OPEN_NUMBER; i++)
	{
		m_listCtl.InsertItem(i, ""); 
	}

	return true;
}


BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	if (!initTables())
		return FALSE;
	if (!initMem())
		return FALSE;
	auto tthread = std::thread(&CAccountDlg::threadCallBack, this);
	tthread.detach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


bool CAccountDlg::updateDate()
{
	for (int i = 0; i < MORE_OPEN_NUMBER; i++)
	{
		//�������ݵ�������
		std::stringstream ss;
		ss << m_shareMemSer->m_pSMAllData->m_sm_data[i].ndPid;
		m_listCtl.SetItemText(i, 0,ss.str().c_str());
		m_listCtl.SetItemText(i, 1, m_shareMemSer->m_pSMAllData->m_sm_data[i].userName.c_str());
		m_listCtl.SetItemText(i, 2, m_shareMemSer->m_pSMAllData->m_sm_data[i].passWord.c_str());
	}
	return true;
}




void CAccountDlg::OnBnClickedButton1()
{
	// TODO:  �����˺�
	UpdateData(TRUE);
	int index =  m_shareMemSer->findPidEmptyIndex();
	if (index == -1)
	{
		AfxMessageBox("�������Ķ࿪����������������˺ţ���ɾ������������˺ţ�\n");
		return;
	}
	m_shareMemSer->m_pSMAllData->m_sm_data[index].userName = m_userName.GetString();
	m_shareMemSer->m_pSMAllData->m_sm_data[index].passWord = m_password.GetString();
}

bool CAccountDlg::initMem()
{
	return  m_shareMemSer->createShareMemory();
}

void CAccountDlg::threadCallBack()
{
	//ˢ�µ��̻߳ص�����
	while (true)
	{
		updateDate();
		//TRACE("111\n");
		Sleep(1000);
	}
}


void CAccountDlg::OnBnClickedButton2()
{
	// TODO:  ɾ���˺ţ���ɾ����ѡ��ѡ�е��˺���Ϣ



}


void CAccountDlg::OnBnClickedButton3()
{
	// TODO:  ��ʼ�ű�

}