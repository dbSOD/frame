
// ConsoleDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "AccountDlg.h"
#include "ConfigDlg.h"
#include "shareMemorySer.h"
#include <memory>
#include <thread>
// CConsoleDlg 对话框
class CConsoleDlg : public CDialogEx
{
// 构造
public:
	CConsoleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONSOLE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabCtl;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	CAccountDlg m_accountDlg;
	CConfigDlg m_configDlg;
	CDialogEx*  m_pDialog[2];


private:
	bool initDlg();

public:
	int m_curSelTab;
};
