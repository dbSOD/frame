
// ConsoleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Console.h"
#include "ConsoleDlg.h"
#include "afxdialogex.h"
#include "utils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConsoleDlg 对话框



CConsoleDlg::CConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConsoleDlg::IDD, pParent)
	, m_curSelTab(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	
}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtl);
}

BEGIN_MESSAGE_MAP(CConsoleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CConsoleDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CConsoleDlg 消息处理程序

BOOL CConsoleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	//初始化表单配置
	if (!initDlg())
	{
		return FALSE;
	}

	//防止控制台多开


		HANDLE hMutex = CreateMutex(NULL, FALSE, _T("ArwenApp"));
		if (GetLastError() == ERROR_ALREADY_EXISTS){ //如果已经存在同名的Mutex会得到这个错误.
			CloseHandle(hMutex);
			AfxMessageBox("请勿重复打开窗口！");
			//退出窗口
			exit(1);
		}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConsoleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConsoleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConsoleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConsoleDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	int sel = m_tabCtl.GetCurSel();
	for (int i = 0; i < m_tabCtl.GetItemCount(); i++)
	{
		m_pDialog[i]->ShowWindow(i == sel ? SW_SHOW : SW_HIDE);
	}

	*pResult = 0;
}

bool CConsoleDlg::initDlg()
{
	//为tab添加两个页面
	m_tabCtl.InsertItem(0, "账号");
	m_tabCtl.InsertItem(1, "配置");

	SetWindowText("游戏控制台框架：QQ424002200");

	//创建两个对话框
	m_accountDlg.Create(IDD_DLGACCOUNT , &m_tabCtl);
	m_configDlg.Create(IDD_DLGCONFIG, &m_tabCtl);
	m_accountDlg.SetParent(&m_tabCtl);
	m_configDlg.SetParent(&m_tabCtl);
	//设定在tab内的显示范围
	CRect rc;
	m_tabCtl.GetClientRect(rc);
	rc.top += 20;
	rc.bottom -= 0;
	rc.left += 0;
	rc.right -= 0;
	m_accountDlg.MoveWindow(&rc);
	m_configDlg.MoveWindow(&rc);

	//保存对话框的指针
	m_pDialog[0] = &m_accountDlg;
	m_pDialog[1] = &m_configDlg;
	
	m_curSelTab = 0;

	m_pDialog[0]->ShowWindow(SW_SHOW);
	m_pDialog[1]->ShowWindow(SW_HIDE);

	return true;
}


