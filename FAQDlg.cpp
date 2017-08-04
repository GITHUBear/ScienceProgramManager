// FAQDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQDlg.h"
#include "afxdialogex.h"


// CFAQDlg �Ի���

IMPLEMENT_DYNAMIC(CFAQDlg, CDialogEx)

CFAQDlg::CFAQDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFAQDlg::IDD, pParent)
{

}

CFAQDlg::~CFAQDlg()
{
}

void CFAQDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, myFAQTabCtrl);
}


BEGIN_MESSAGE_MAP(CFAQDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CFAQDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CFAQDlg ��Ϣ�������


BOOL CFAQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	myFAQTabCtrl.InsertItem(0,_T("�ļ�����"));
	myFAQTabCtrl.InsertItem(1,_T("���ݲ���"));
	myFAQTabCtrl.InsertItem(2,_T("ͬ������"));
	myFAQTabCtrl.InsertItem(3,_T("����"));
	fileDlg.Create(IDD_FILEFAQDIALOG,&myFAQTabCtrl);
	dataDlg.Create(IDD_DATAFAQDIALOG,&myFAQTabCtrl);
	syncDlg.Create(IDD_SYNCDIALOG,&myFAQTabCtrl);
	helpDlg.Create(IDD_HELPFAQDIALOG,&myFAQTabCtrl);
	CRect crect;
	myFAQTabCtrl.GetClientRect(crect);
	crect.top += 20;
	fileDlg.MoveWindow(&crect);
	dataDlg.MoveWindow(&crect);
	syncDlg.MoveWindow(&crect);
	helpDlg.MoveWindow(&crect);
	pDlg[0] = &fileDlg;
	pDlg[1] = &dataDlg;
	pDlg[2] = &syncDlg;
	pDlg[3] = &helpDlg;
	pDlg[0]->ShowWindow(SW_SHOW);
	pDlg[1]->ShowWindow(SW_HIDE);
	pDlg[2]->ShowWindow(SW_HIDE);
	pDlg[3]->ShowWindow(SW_HIDE);
	curentSelTab = 0;
	return TRUE;
}


void CFAQDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	pDlg[curentSelTab]->ShowWindow(SW_HIDE);
	curentSelTab = myFAQTabCtrl.GetCurSel();
	pDlg[curentSelTab]->ShowWindow(SW_SHOW);
	*pResult = 0;
	return;
}
