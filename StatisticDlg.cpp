// StatisticDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "StatisticDlg.h"
#include "afxdialogex.h"


// CStatisticDlg 对话框

IMPLEMENT_DYNAMIC(CStatisticDlg, CDialogEx)

CStatisticDlg::CStatisticDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisticDlg::IDD, pParent)
{
	
}

CStatisticDlg::~CStatisticDlg()
{
}

void CStatisticDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, myTabCtrl);
}


BEGIN_MESSAGE_MAP(CStatisticDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CStatisticDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CStatisticDlg 消息处理程序


BOOL CStatisticDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	myTabCtrl.InsertItem(0,_T("报表1"));
	myTabCtrl.InsertItem(1,_T("报表2"));
	myTabCtrl.InsertItem(2,_T("报表3"));
	myTabCtrl.InsertItem(3,_T("报表4"));
	page1.pSciDlg = this->pSciDlg;
	page2.pSciDlg = this->pSciDlg;
	page3.pSciDlg = this->pSciDlg;
	page4.pSciDlg = this->pSciDlg;
	page1.Create(IDD_STATISDIALOG1,&myTabCtrl);
	page2.Create(IDD_STATISDIALOG2,&myTabCtrl);
	page3.Create(IDD_STATISDIALOG3,&myTabCtrl);
	page4.Create(IDD_STATISDIALOG4,&myTabCtrl);
	CRect crect;
	myTabCtrl.GetClientRect(crect);
	crect.top += 20;
	page1.MoveWindow(&crect);
	page2.MoveWindow(&crect);
	page3.MoveWindow(&crect);
	page4.MoveWindow(&crect);
	pDlg[0] = &page1;
	pDlg[1] = &page2;
	pDlg[2] = &page3;
	pDlg[3] = &page4;
	pDlg[0]->ShowWindow(SW_SHOW);
	pDlg[1]->ShowWindow(SW_HIDE);
	pDlg[2]->ShowWindow(SW_HIDE);
	pDlg[3]->ShowWindow(SW_HIDE);
	curentSelTab = 0;
	return TRUE;
}


void CStatisticDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	pDlg[curentSelTab]->ShowWindow(SW_HIDE);
	curentSelTab = myTabCtrl.GetCurSel();
	pDlg[curentSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
	return;
}
