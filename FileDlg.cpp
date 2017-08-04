// FileDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FileDlg.h"
#include "afxdialogex.h"
#include <regex>
#include <string>

// CFileDlg �Ի���

IMPLEMENT_DYNAMIC(CFileDlg, CDialogEx)

CFileDlg::CFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileDlg::IDD, pParent)
{

}

CFileDlg::~CFileDlg()
{
}

void CFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFileDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CFileDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CFileDlg ��Ϣ�������


void CFileDlg::OnBnClickedOk()
{
	GetDlgItemText(IDC_FILEPATH,this->filePath);
	if(!this->filePath.IsEmpty())
	{
		std::string pattern("([[:alpha:]]:|\\.)(\\\\.*)+\\.dat");
		CStringA cstr(this->filePath.GetBuffer(0));
		this->filePath.ReleaseBuffer();
		std::string temp = cstr.GetBuffer(0);
		cstr.ReleaseBuffer();
		std::regex re(pattern);
		if(std::regex_match(temp,re))
		{
			CString strFileTitle; 
			CFileFind finder; 
			BOOL bWorking = finder.FindFile(this->filePath); 
			if(!bWorking)
				MessageBox(_T("�ļ�������,����������"),_T("NOTICE"),MB_ICONWARNING | MB_OK);
			else
				return CDialogEx::OnOK();
		}else
		{
			MessageBox(_T("�Ƿ�·��,����������"),_T("NOTICE"),MB_ICONWARNING | MB_OK);
			SetDlgItemText(IDC_FILEPATH,_T(""));
		}
	}else
		MessageBox(_T("�ļ�·������Ϊ�գ�"),_T("NOTICE"),MB_ICONWARNING | MB_OK);
}


BOOL CFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;
}
