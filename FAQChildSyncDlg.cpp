// FAQChildSyncDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FAQChildSyncDlg.h"
#include "afxdialogex.h"


// CFAQChildSyncDlg �Ի���

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


// CFAQChildSyncDlg ��Ϣ�������


BOOL CFAQChildSyncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgItemText(IDC_EDIT2,_T("  ͬ������,ʹ���û���ͼ�ν����ַ��ϵı༭����ͬ�������ڴ�ռ��ϵõ��������ڿ��������ͬ�������ķ���ִ��,�ᵼ��һЩ�޷�Ԥ�Ƶĳ�����Ϊ,���Կ������ѽ����ù��ܽ���"));
	return TRUE;
}
