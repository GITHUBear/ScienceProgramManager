// TeamDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "TeamDlg.h"
#include "afxdialogex.h"


// CTeamDlg �Ի���

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


// CTeamDlg ��Ϣ�������


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
			MessageBox(_T("�Ŷ�����������ӦС��30"),_T("��ʾ"),MB_ICONINFORMATION);
		if(wcslen(cstrManager) >= 12)
			MessageBox(_T("��������������ӦС��12"),_T("��ʾ"),MB_ICONINFORMATION);
		if(!teacherNum)
			MessageBox(_T("��ʦ��������Ϊ0���߸�ʽ����"),_T("��ʾ"),MB_ICONINFORMATION);
		if(!postGraNum)
			MessageBox(_T("�о�����������Ϊ0���߸�ʽ����"),_T("��ʾ"),MB_ICONINFORMATION);
		if(wcslen(cstrInsti) >= 20)
			MessageBox(_T("ѧԺ����������ӦС��20"),_T("��ʾ"),MB_ICONINFORMATION);
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
		MessageBox(_T("�������ݲ�����"),_T("��ʾ"));
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
