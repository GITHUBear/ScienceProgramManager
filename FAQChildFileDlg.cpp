// FAQChildFileDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildFileDlg.h"
#include "afxdialogex.h"


// CFAQChildFileDlg 对话框

IMPLEMENT_DYNAMIC(CFAQChildFileDlg, CDialogEx)

CFAQChildFileDlg::CFAQChildFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFAQChildFileDlg::IDD, pParent)
{

}

CFAQChildFileDlg::~CFAQChildFileDlg()
{
}

void CFAQChildFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFAQChildFileDlg, CDialogEx)
END_MESSAGE_MAP()


// CFAQChildFileDlg 消息处理程序


BOOL CFAQChildFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pListCtrl->InsertColumn(0,_T("功能选项"),0,120);
	pListCtrl->InsertColumn(1,_T("功能说明"),0,630);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListCtrl->InsertItem(0,_T("文件打开"));
	pListCtrl->SetItemText(0,1,_T("采用手动输入文件路径的方式(程序自动识别文件所属的表格),提供文件\r\n的安全检查,以及错误路径提示等安全功能"));
	pListCtrl->InsertItem(1,_T("文件重置"));
	pListCtrl->SetItemText(1,1,_T("清空工作界面和物理内存,清空前提空保存询问"));
	pListCtrl->InsertItem(2,_T("保存文件及全部保存"));
	pListCtrl->SetItemText(2,1,_T("采用windows常用的用户文件保存交互界面(支持单独保存和全部保存),功能解释权属于Microsoft"));
	pListCtrl->InsertItem(3,_T("链表生成及清空"));
	pListCtrl->SetItemText(3,1,_T("Release版已无需用户手动管理内存,开发者较懒将此功能予以保留"));
	pListCtrl->InsertItem(4,_T("Debug"));
	pListCtrl->SetItemText(4,1,_T("开发者用于显示内存状况的功能,用户无须在意"));
	pListCtrl->InsertItem(5,_T("退出"));
	pListCtrl->SetItemText(5,1,_T("顾名思义,提供关闭保存询问"));
	return TRUE;
}
