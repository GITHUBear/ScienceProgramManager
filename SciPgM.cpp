
// SciPgM.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "SciPgM.h"
#include "SciPgMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSciPgMApp

BEGIN_MESSAGE_MAP(CSciPgMApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSciPgMApp 构造

CSciPgMApp::CSciPgMApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSciPgMApp 对象

CSciPgMApp theApp;


// CSciPgMApp 初始化

BOOL CSciPgMApp::InitInstance()
{
	CSciPgMDlg sciPgMDlg;
	int nresponse = sciPgMDlg.DoModal();
	return FALSE;
}

