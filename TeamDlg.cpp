// TeamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "TeamDlg.h"
#include "afxdialogex.h"


// CTeamDlg 对话框

IMPLEMENT_DYNAMIC(CTeamDlg, CDialogEx)

CTeamDlg::CTeamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTeamDlg::IDD, pParent)
{

}

CTeamDlg::~CTeamDlg()
{
}

void CTeamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTeamDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTeamDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTeamDlg 消息处理程序


void CTeamDlg::OnBnClickedOk()
{
	CString cstrTeam,cstrManager,cstrTeacherNum,cstrPostGraNum,cstrInsti;
	int teacherNum,postGraNum;
	GetDlgItemText(IDC_TEAMDLG2,cstrTeam);
	GetDlgItemText(IDC_MANAGERDLG2,cstrManager);
	GetDlgItemText(IDC_TEACHERNUMDLG2,cstrTeacherNum);
	GetDlgItemText(IDC_POSTGRANUMDLG2,cstrPostGraNum);
	GetDlgItemText(IDC_INSTIDLG2,cstrInsti);
	teacherNum = _wtoi(cstrTeacherNum);
	postGraNum = _wtoi(cstrPostGraNum);
	if(wcslen(cstrTeam) >= 30 
		|| wcslen(cstrManager) >= 12 
		|| !teacherNum
		|| !postGraNum
		|| wcslen(cstrInsti) >= 20)
	{
		if(wcslen(cstrTeam) >= 30)
			MessageBox(_T("团队名输入数据应小于30"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrManager) >= 12)
			MessageBox(_T("负责人输入数据应小于12"),_T("提示"),MB_ICONINFORMATION);
		if(!teacherNum)
			MessageBox(_T("教师人数不能为0或者格式有误"),_T("提示"),MB_ICONINFORMATION);
		if(!postGraNum)
			MessageBox(_T("研究生人数不能为0或者格式有误"),_T("提示"),MB_ICONINFORMATION);
		if(wcslen(cstrInsti) >= 20)
			MessageBox(_T("学院名输入数据应小于20"),_T("提示"),MB_ICONINFORMATION);
		return;
	}
	this->cstringVec.clear();
	if(!cstrTeam.IsEmpty() && !cstrManager.IsEmpty() && !cstrPostGraNum.IsEmpty()
		&& !cstrPostGraNum.IsEmpty() && !cstrInsti.IsEmpty())
	{
		cstrTeacherNum.Format(_T("%d"),teacherNum);
		cstrPostGraNum.Format(_T("%d"),postGraNum);
		cstringVec.push_back(cstrTeam);
		cstringVec.push_back(cstrManager);
		cstringVec.push_back(cstrTeacherNum);
		cstringVec.push_back(cstrPostGraNum);
		cstringVec.push_back(cstrInsti);
		return CDialogEx::OnOK();
	}else
		MessageBox(_T("输入数据不完整"),_T("提示"));
}


BOOL CTeamDlg::OnInitDialog()
{
	SetFocus();
	if(isEdit)
	{
		SetDlgItemText(IDC_TEAMDLG2,cstringVec[0]);
		SetDlgItemText(IDC_MANAGERDLG2,cstringVec[1]);
		SetDlgItemText(IDC_TEACHERNUMDLG2,cstringVec[2]);
		SetDlgItemText(IDC_POSTGRANUMDLG2,cstringVec[3]);
		SetDlgItemText(IDC_INSTIDLG2,cstringVec[4]);
	}
	return TRUE;
}
