// FindInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FindInfoDlg.h"
#include "afxdialogex.h"
#include <regex>

// CFindInfoDlg 对话框

IMPLEMENT_DYNAMIC(CFindInfoDlg, CDialogEx)

CFindInfoDlg::CFindInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindInfoDlg::IDD, pParent)
{

}

CFindInfoDlg::~CFindInfoDlg()
{
}

void CFindInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOLISTCHOOSE, listChooseCombo);
	DDX_Control(pDX, IDC_COMBOFINDMETHOD, findMethodCombo);
}


BEGIN_MESSAGE_MAP(CFindInfoDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBOLISTCHOOSE, &CFindInfoDlg::OnCbnSelchangeCombolistchoose)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CFindInfoDlg 消息处理程序


void CFindInfoDlg::OnCancel()
{
	CDialogEx::OnCancel();
	pSciPgmDlg->linkedList2ListShow();
	DestroyWindow();
}


void CFindInfoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete this;
}


BOOL CFindInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetFocus();
	listChooseCombo.AddString(_T("学院列表"));
	listChooseCombo.AddString(_T("团队列表"));
	listChooseCombo.AddString(_T("项目列表"));
	return TRUE;
}


void CFindInfoDlg::OnCbnSelchangeCombolistchoose()
{
	int nIndex = listChooseCombo.GetCurSel();
	CString listContext;
	listChooseCombo.GetLBText(nIndex,listContext);
	if(listContext == _T("学院列表"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("院系负责人"));
		findMethodCombo.AddString(_T("学院名"));
	}else if(listContext == _T("团队列表"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("团队名称"));
		findMethodCombo.AddString(_T("教师人数>"));
		findMethodCombo.AddString(_T("教师人数<"));
		findMethodCombo.AddString(_T("教师人数>="));
		findMethodCombo.AddString(_T("教师人数<="));
		findMethodCombo.AddString(_T("教师人数>=? <=?"));
	}else if(listContext == _T("项目列表"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("项目编号"));
		findMethodCombo.AddString(_T("所属团队"));
	}
	return;
}

BOOL instiManagerMatch(InstituteNode *pInsti,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pInsti->institude.manager,keyWord);
}

BOOL instiNameMatch(InstituteNode *pInsti,const CString& keyWord)
{
 	return CFindInfoDlg::KMP(pInsti->institude.name,keyWord);
}

BOOL teamNameMatch(TeamNode *pTeam,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pTeam->team.name,keyWord);
}

//教师人数>
BOOL teamTeacherNumMatch1(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum > num ? TRUE : FALSE;
}

//教师人数<
BOOL teamTeacherNumMatch2(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum < num ? TRUE : FALSE;
}

//教师人数>=
BOOL teamTeacherNumMatch3(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum >= num ? TRUE : FALSE;
}

//教师人数<=
BOOL teamTeacherNumMatch4(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum <= num ? TRUE : FALSE;
}

//教师人数>=? <=?
BOOL teamTeacherNumMatch5(TeamNode *pTeam,const CString& keyWord)
{
	int a,b;
	swscanf_s(keyWord,_T("%d %d"),&a,&b);
	if(a <= b)
		return (pTeam->team.teacherNum >= a && pTeam->team.teacherNum <= b) ? TRUE : FALSE;
	else
		return (pTeam->team.teacherNum >= b && pTeam->team.teacherNum <= a) ? TRUE : FALSE;
}

BOOL itemNumMatch(programItemNode *pItem,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pItem->item.number,keyWord);
}

BOOL itemTeamMatch(programItemNode *pItem,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pItem->item.teamName,keyWord);
}

void CFindInfoDlg::OnOK()
{
	CString cstrListChoose,cstrSearchMethod,cstrKeyword;
	int nIndex;
	nIndex = listChooseCombo.GetCurSel();
	listChooseCombo.GetLBText(nIndex,cstrListChoose);
	nIndex = findMethodCombo.GetCurSel();
	findMethodCombo.GetLBText(nIndex,cstrSearchMethod);
	GetDlgItemText(IDC_FINDEDIT,cstrKeyword);
	if(!cstrListChoose.GetLength() || !cstrSearchMethod.GetLength() || !cstrKeyword.GetLength())
	{
		MessageBox(_T("有项目为空！"),_T("NOTICE"),MB_ICONINFORMATION);
		return;
	}
	if(cstrListChoose == _T("学院列表"))
	{
		if(cstrSearchMethod == _T("院系负责人"))
			pSciPgmDlg->findInsti2ListShow(instiManagerMatch,cstrKeyword);
		else if(cstrSearchMethod == _T("学院名"))
			pSciPgmDlg->findInsti2ListShow(instiNameMatch,cstrKeyword);
		else
		{
			MessageBox(_T("请严格使用复选框的选项!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else if(cstrListChoose == _T("团队列表"))
	{
		if(cstrSearchMethod == _T("团队名称"))
		{
			pSciPgmDlg->findTeam2ListShow(teamNameMatch,cstrKeyword);
		}else if(cstrSearchMethod == _T("教师人数>"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch1,cstrKeyword);
			else
			{
				MessageBox(_T("查找关键字输入格式有误,仅允许纯数字(9位数int型)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("教师人数<"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch2,cstrKeyword);
			else
			{
				MessageBox(_T("查找关键字输入格式有误,仅允许纯数字(9位数int型)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("教师人数>="))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch3,cstrKeyword);
			else
			{
				MessageBox(_T("查找关键字输入格式有误,仅允许纯数字(9位数int型)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("教师人数<="))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch4,cstrKeyword);
			else
			{
				MessageBox(_T("查找关键字输入格式有误,仅允许纯数字(9位数int型)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("教师人数>=? <=?"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9}) (\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch5,cstrKeyword);
			else
			{
				MessageBox(_T("查找关键字输入格式有误,仅允许格式:num num(num为9位数int型)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else
		{
			MessageBox(_T("请严格使用复选框的选项!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else if(cstrListChoose == _T("项目列表"))
	{
		if(cstrSearchMethod == _T("项目编号"))
		{
			pSciPgmDlg->findItem2ListShow(itemNumMatch,cstrKeyword);
		}else if(cstrSearchMethod == _T("所属团队"))
		{
			pSciPgmDlg->findItem2ListShow(itemTeamMatch,cstrKeyword);
		}else
		{
			MessageBox(_T("请严格使用复选框的选项!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else
	{
		MessageBox(_T("请严格使用复选框的选项!"),_T("NOTICE"),MB_ICONEXCLAMATION);
		return;
	}
	return;
}

int *CFindInfoDlg::buildNext(const CString& patte)
{
	int i = 1,k = 1;
	int *nextArray = (int *)malloc(sizeof(int) * patte.GetLength());
	memset(nextArray,0,sizeof(nextArray));
	while(i < patte.GetLength()){
		if(k - 1 >= 0 && patte[i] == patte[nextArray[k - 1]]){
			nextArray[i] = nextArray[k - 1] + 1;
			i++;k = i;
		}else{
			if(k - 1 < 0){
				nextArray[i] = 0;
				i++;k = i;
			}else k = nextArray[k - 1];
		}
	}
	return nextArray;
}

BOOL CFindInfoDlg::KMP(const CString& str,const CString& patte)
{
	int *nextArray = buildNext(patte);
	int pos = 0;
	for(int i = 0;i <= str.GetLength();i++){
		if(pos == patte.GetLength())
		{
			free(nextArray);
			return TRUE;
		}
		if(!pos && patte[pos] != str[i]) continue;
		if(pos < patte.GetLength()){
			if(patte[pos] == str[i]){
				pos++;continue;
			}else{
				while(pos){
					if(patte[nextArray[pos - 1]] == str[i]){
						pos = nextArray[pos - 1] + 1;
						break;
					}else pos = nextArray[pos - 1];
				}
			}
		}
	}
	free(nextArray);
	return FALSE;
}