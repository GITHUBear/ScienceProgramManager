
// SciPgM.cpp : ����Ӧ�ó��������Ϊ��
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


// CSciPgMApp ����

CSciPgMApp::CSciPgMApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSciPgMApp ����

CSciPgMApp theApp;


// CSciPgMApp ��ʼ��

BOOL CSciPgMApp::InitInstance()
{
	CSciPgMDlg sciPgMDlg;
	int nresponse = sciPgMDlg.DoModal();
	return FALSE;
}

