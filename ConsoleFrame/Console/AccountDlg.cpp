// AccountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Console.h"
#include "AccountDlg.h"
#include "afxdialogex.h"
#include <sstream>
#include <thread>
#include <windows.h>
#include "exeLoad.h"
// CAccountDlg 对话框


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


// CAccountDlg 消息处理程序


// 初始化表单信息
bool CAccountDlg::initTables()
{
	//设置风格

	DWORD dwStyle = m_listCtl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;// 选中某行使整行高亮（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_GRIDLINES;// 网格线（只适用与report 风格的listctrl ） 
	dwStyle |= LVS_EX_CHECKBOXES;//item 前生成checkbox 控件 
	m_listCtl.SetExtendedStyle(dwStyle); // 设置扩展风格 

	//初始化表头
	int i = 0;
	m_listCtl.InsertColumn(i++, "Pid", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "用户名", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "密码", LVCFMT_LEFT, 80);
	m_listCtl.InsertColumn(i++, "当前脚本", LVCFMT_LEFT, 80);

	//插入MORE_OPEN_NUM行

	for (int i= 0; i < MORE_OPEN_NUMBER; i++)
	{
		m_listCtl.InsertItem(i, ""); 
	}

	return true;
}


BOOL CAccountDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (!initTables())
		return FALSE;
	if (!initMem())
		return FALSE;
	auto tthread = std::thread(&CAccountDlg::threadCallBack, this);
	tthread.detach();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


bool CAccountDlg::updateDate()
{
	for (int i = 0; i < MORE_OPEN_NUMBER; i++)
	{
		//更新数据到表单中
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
	// TODO:  添加账号
	UpdateData(TRUE);
	int index =  m_shareMemSer->findPidEmptyIndex();
	if (index == -1)
	{
		AfxMessageBox("超过最大的多开数量，如果想添加账号，请删除上面的任意账号！\n");
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
	//刷新的线程回调函数
	while (true)
	{
		updateDate();
		//TRACE("111\n");
		Sleep(1000);
	}
}


void CAccountDlg::OnBnClickedButton2()
{
	// TODO:  删除账号，是删除复选框选中的账号信息



}


void CAccountDlg::OnBnClickedButton3()
{
	// TODO:  开始脚本
	//正常情况下，会判断当前复选框是否被选中，只登陆选中的
	for (int i = 0; i < MORE_OPEN_NUMBER; i++)
	{

		exeLoad e("shareMemTest.exe");
	}
	
}
