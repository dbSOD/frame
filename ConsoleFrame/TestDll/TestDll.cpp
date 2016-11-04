// TestDll.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "TestDll.h"
#include "TestDlg.h"
#include <thread>
#include <memory>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CTestDllApp

BEGIN_MESSAGE_MAP(CTestDllApp, CWinApp)
END_MESSAGE_MAP()


// CTestDllApp 构造

CTestDllApp::CTestDllApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CTestDllApp 对象

CTestDllApp theApp;


// CTestDllApp 初始化

BOOL CTestDllApp::InitInstance()
{
	CWinApp::InitInstance();

	return init();
}

bool CTestDllApp::init()
{
	//自定义初始化函数
	//这种注入方式，线程会随着this dll卸载退出线程！
	std::thread th(&threadFunc);
	th.detach();
	CloseHandle(::CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(threadFunc), NULL, NULL, NULL));
	return true;
}

//线程函数，用来创建函数窗口
void threadFunc()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hOldRes = AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);
	std::shared_ptr<CTestDlg> pDlg(new CTestDlg); 
	pDlg->DoModal();
	FreeLibraryAndExitThread(theApp.m_hInstance, 1);
	AfxSetResourceHandle(hOldRes);
	return;
}
