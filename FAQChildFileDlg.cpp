// FAQChildFileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildFileDlg.h"
#include "afxdialogex.h"


// CFAQChildFileDlg �Ի���

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


// CFAQChildFileDlg ��Ϣ�������


BOOL CFAQChildFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST1);
	pListCtrl->InsertColumn(0,_T("����ѡ��"),0,120);
	pListCtrl->InsertColumn(1,_T("����˵��"),0,630);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	pListCtrl->InsertItem(0,_T("�ļ���"));
	pListCtrl->SetItemText(0,1,_T("�����ֶ������ļ�·���ķ�ʽ(�����Զ�ʶ���ļ������ı��),�ṩ�ļ�\r\n�İ�ȫ���,�Լ�����·����ʾ�Ȱ�ȫ����"));
	pListCtrl->InsertItem(1,_T("�ļ�����"));
	pListCtrl->SetItemText(1,1,_T("��չ�������������ڴ�,���ǰ��ձ���ѯ��"));
	pListCtrl->InsertItem(2,_T("�����ļ���ȫ������"));
	pListCtrl->SetItemText(2,1,_T("����windows���õ��û��ļ����潻������(֧�ֵ��������ȫ������),���ܽ���Ȩ����Microsoft"));
	pListCtrl->InsertItem(3,_T("�������ɼ����"));
	pListCtrl->SetItemText(3,1,_T("Release���������û��ֶ������ڴ�,�����߽������˹������Ա���"));
	pListCtrl->InsertItem(4,_T("Debug"));
	pListCtrl->SetItemText(4,1,_T("������������ʾ�ڴ�״���Ĺ���,�û���������"));
	pListCtrl->InsertItem(5,_T("�˳�"));
	pListCtrl->SetItemText(5,1,_T("����˼��,�ṩ�رձ���ѯ��"));
	return TRUE;
}
