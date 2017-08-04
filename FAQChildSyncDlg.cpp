// FAQChildSyncDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildSyncDlg.h"
#include "afxdialogex.h"


// CFAQChildSyncDlg 对话框

IMPLEMENT_DYNAMIC(CFAQChildSyncDlg, CDialogEx)

CFAQChildSyncDlg::CFAQChildSyncDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFAQChildSyncDlg::IDD, pParent)
{

}

CFAQChildSyncDlg::~CFAQChildSyncDlg()
{
}

void CFAQChildSyncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFAQChildSyncDlg, CDialogEx)
END_MESSAGE_MAP()


// CFAQChildSyncDlg 消息处理程序


BOOL CFAQChildSyncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_EDIT2,_T("  同步功能,使得用户在图形界面字符上的编辑可以同步地在内存空间上得到反馈由于开启与禁用同步操作的反复执行,会导致一些无法预计的程序行为,所以开发者已将禁用功能禁用"));
	return TRUE;
}
