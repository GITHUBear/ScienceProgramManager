// FAQChildDataDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildDataDlg.h"
#include "afxdialogex.h"


// CFAQChildDataDlg �Ի���

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


// CFAQChildDataDlg ��Ϣ�������


BOOL CFAQChildDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pListCtrl->InsertColumn(0,_T("����ѡ��"),0,150);
	pListCtrl->InsertColumn(1,_T("����˵��"),0,630);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListCtrl->InsertItem(0,_T("����ͳ��"));
	pListCtrl->SetItemText(0,1,_T("��ʾ�γ����Ҫ��ļ���ͳ��"));
	pListCtrl->InsertItem(1,_T("���ݲ���"));
	pListCtrl->SetItemText(1,1,_T("ComboBox�Ľ�������,�ṩ�û���������ģʽ,�Ҷ�֧��ģ������,ͬʱ���ڲ��ҳ����������û��������ɵؽ���ɾ��"));
	return TRUE;
}
