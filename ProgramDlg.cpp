// ProgramDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "ProgramDlg.h"
#include "afxdialogex.h"
#include <regex>

// CProgramDlg 对话框

IMPLEMENT_DYNAMIC(CProgramDlg, CDialogEx)

CProgramDlg::CProgramDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CProgramDlg::IDD, pParent)
{

}

CProgramDlg::~CProgramDlg()
{
}

void CProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProgramDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CProgramDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CProgramDlg 消息处理程序


void CProgramDlg::OnBnClickedOk()
{
	std::string pattern("1|2|3|4|5");
	std::regex re(pattern);
	CString cstrProCode,cstrType,cstrStartTime,cstrCost,cstrManager,cstrTeam,cstrInsti;
	GetDlgItemText(IDC_PROCODEDLG3,cstrProCode);
	GetDlgItemText(IDC_PROTYPEDLG3,cstrType);
	GetDlgItemText(IDC_STARTIMEDLG3,cstrStartTime);
	GetDlgItemText(IDC_COSTDLG3,cstrCost);
	GetDlgItemText(IDC_PROMANADLG3,cstrManager);
	GetDlgItemText(IDC_PROTEAMDLG3,cstrTeam);
	GetDlgItemText(IDC_PROINSTIDLG3,cstrInsti);
	std::string str = CT2A(cstrType);
	bool flag = std::regex_match(str,re);
	float cost = (float)_wtof(cstrCost);
	if(wcslen(cstrProCode) >= 15
		|| !flag
		|| wcslen(cstrStartTime) >= 8
		|| !cost
		|| wcslen(cstrManager) >= 12
		|| wcslen(cstrTeam) >= 30)
	{
		if(wcslen(cstrProCode) >= 15)
			MessageBox(_T("项目编号输入数据应小于15"),_T("提示"),MB_ICONINFORMATION);
		if(!flag)
			MessageBox(_T("项目类型输入格式有误"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrStartTime) >= 8)
			MessageBox(_T("起始时间输入数据应小于8"),_T("提示"),MB_ICONINFORMATION);
		if(!cost)
			MessageBox(_T("项目经费不能为0或输入格式有误"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrManager) >= 12)
			MessageBox(_T("负责人输入数据应小于12"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrInsti) >= 30)
			MessageBox(_T("学院名输入数据应小于30"),_T("提示"),MB_ICONINFORMATION);
		return;
	}
	this->cstringVec.clear();
	if(!cstrProCode.IsEmpty() && !cstrType.IsEmpty() && !cstrStartTime.IsEmpty()
		&& !cstrCost.IsEmpty() && !cstrManager.IsEmpty() && !cstrTeam.IsEmpty() && !cstrInsti.IsEmpty())
	{
		this->cstringVec.push_back(cstrProCode);
		this->cstringVec.push_back(cstrType);
		this->cstringVec.push_back(cstrStartTime);
		this->cstringVec.push_back(cstrCost);
		this->cstringVec.push_back(cstrManager);
		this->cstringVec.push_back(cstrTeam);
		this->cstringVec.push_back(cstrInsti);
		return CDialogEx::OnOK();
	}
	else
		MessageBox(_T("输入数据不完整"),_T("提示"));
}


BOOL CProgramDlg::OnInitDialog()
{
	SetFocus();
	if(isEdit)
	{
		SetDlgItemText(IDC_PROCODEDLG3,cstringVec[0]);
		SetDlgItemText(IDC_PROTYPEDLG3,cstringVec[1]);
		SetDlgItemText(IDC_STARTIMEDLG3,cstringVec[2]);
		SetDlgItemText(IDC_COSTDLG3,cstringVec[3]);
		SetDlgItemText(IDC_PROMANADLG3,cstringVec[4]);
		SetDlgItemText(IDC_PROTEAMDLG3,cstringVec[5]);
		SetDlgItemText(IDC_PROINSTIDLG3,cstringVec[6]);
	}
	return TRUE;
}
