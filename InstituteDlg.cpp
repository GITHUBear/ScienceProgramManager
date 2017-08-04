// InstituteDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "InstituteDlg.h"
#include "afxdialogex.h"
#include <cstringt.h>

// CInstituteDlg 对话框

IMPLEMENT_DYNAMIC(CInstituteDlg, CDialogEx)

CInstituteDlg::CInstituteDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInstituteDlg::IDD, pParent)
{

}

CInstituteDlg::~CInstituteDlg()
{
}

void CInstituteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInstituteDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInstituteDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CInstituteDlg 消息处理程序

void CInstituteDlg::OnBnClickedOk()
{
	CString cstrName, cstrManager, cstrTel;
	GetDlgItemText(IDC_NAME,cstrName);
	GetDlgItemText(IDC_MANAGER, cstrManager);
	GetDlgItemText(IDC_TEL,cstrTel);
	if(wcslen(cstrName) >= 20 || wcslen(cstrManager) >= 12 || wcslen(cstrTel) >= 15)
	{
		if(wcslen(cstrName) >= 20)
			MessageBox(_T("学院名输入数据应小于20"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrManager) >= 12)
			MessageBox(_T("负责人输入数据应小于12"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrTel) >= 15)
			MessageBox(_T("联系电话输入数据应小于15"),_T("提示"),MB_ICONINFORMATION);
		return;
	}
	this->cstringVec.clear();
	if(!cstrName.IsEmpty() && !cstrManager.IsEmpty() && !cstrTel.IsEmpty())
	{
		this->cstringVec.push_back(cstrName);
		this->cstringVec.push_back(cstrManager);
		this->cstringVec.push_back(cstrTel);
		return CDialogEx::OnOK();
	}
	else
		MessageBox(_T("输入数据不完整"),_T("提示"));
}


BOOL CInstituteDlg::OnInitDialog()
{
	SetFocus();
	if(isEdit)
	{
		SetDlgItemText(IDC_NAME,cstringVec[0]);
		SetDlgItemText(IDC_MANAGER,cstringVec[1]);
		SetDlgItemText(IDC_TEL,cstringVec[2]);
	}
	return TRUE;
}