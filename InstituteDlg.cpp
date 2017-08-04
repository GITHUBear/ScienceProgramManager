// InstituteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "InstituteDlg.h"
#include "afxdialogex.h"
#include <cstringt.h>

// CInstituteDlg �Ի���

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

// CInstituteDlg ��Ϣ�������

void CInstituteDlg::OnBnClickedOk()
{
	CString cstrName, cstrManager, cstrTel;
	GetDlgItemText(IDC_NAME,cstrName);
	GetDlgItemText(IDC_MANAGER, cstrManager);
	GetDlgItemText(IDC_TEL,cstrTel);
	if(wcslen(cstrName) >= 20 || wcslen(cstrManager) >= 12 || wcslen(cstrTel) >= 15)
	{
		if(wcslen(cstrName) >= 20)
			MessageBox(_T("ѧԺ����������ӦС��20"),_T("��ʾ"),MB_ICONINFORMATION);
		if(wcslen(cstrManager) >= 12)
			MessageBox(_T("��������������ӦС��12"),_T("��ʾ"),MB_ICONINFORMATION);
		if(wcslen(cstrTel) >= 15)
			MessageBox(_T("��ϵ�绰��������ӦС��15"),_T("��ʾ"),MB_ICONINFORMATION);
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
		MessageBox(_T("�������ݲ�����"),_T("��ʾ"));
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