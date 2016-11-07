#pragma once
#include "afxcmn.h"
#include <string>
#include "SMstruct.h"
#include "shareMemorySer.h"
// CAccountDlg 对话框

class CAccountDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountDlg();

// 对话框数据
	enum { IDD = IDD_DLGACCOUNT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	bool initMem();
	std::shared_ptr<shareMemorySer>m_shareMemSer;
	void threadCallBack();

public:
	CListCtrl m_listCtl;
	// 初始化表单信息
	bool initTables();

	virtual BOOL OnInitDialog();
	//更新共享内存的数据到表单中
	bool updateDate();

	afx_msg void OnBnClickedButton1();
	CString m_userName;
	CString m_password;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
