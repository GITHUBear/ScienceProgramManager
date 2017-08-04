// FAQChildDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildDataDlg.h"
#include "afxdialogex.h"


// CFAQChildDataDlg 对话框

IMPLEMENT_DYNAMIC(CFAQChildDataDlg, CDialogEx)

CFAQChildDataDlg::CFAQChildDataDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFAQChildDataDlg::IDD, pParent)
{

}

CFAQChildDataDlg::~CFAQChildDataDlg()
{
}

void CFAQChildDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFAQChildDataDlg, CDialogEx)
END_MESSAGE_MAP()


// CFAQChildDataDlg 消息处理程序


BOOL CFAQChildDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pListCtrl->InsertColumn(0,_T("功能选项"),0,150);
	pListCtrl->InsertColumn(1,_T("功能说明"),0,630);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListCtrl->InsertItem(0,_T("数据统计"));
	pListCtrl->SetItemText(0,1,_T("显示课程设计要求的几个统计"));
	pListCtrl->InsertItem(1,_T("数据查找"));
	pListCtrl->SetItemText(1,1,_T("ComboBox的交互界面,提供用户多种搜索模式,且都支持模糊查找,同时对于查找出来的数据用户可以轻松地进行删改"));
	return TRUE;
}
