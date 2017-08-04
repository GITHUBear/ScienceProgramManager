// StatisChildDlg4.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "StatisChildDlg4.h"
#include "afxdialogex.h"


// CStatisChildDlg4 对话框

IMPLEMENT_DYNAMIC(CStatisChildDlg4, CDialogEx)

CStatisChildDlg4::CStatisChildDlg4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisChildDlg4::IDD, pParent)
{

}

CStatisChildDlg4::~CStatisChildDlg4()
{
}

void CStatisChildDlg4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatisChildDlg4, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


bool compareFunc(CStatisChildDlg4::packageTeam *p1,CStatisChildDlg4::packageTeam *p2)
{
	return p1->ratioValue > p2->ratioValue;
}

// CStatisChildDlg4 消息处理程序


BOOL CStatisChildDlg4::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	pListCtrl->InsertColumn(0,_T("团队名称"),0,60);
	pListCtrl->InsertColumn(1,_T("院系名称"),0,80);
	pListCtrl->InsertColumn(2,_T("项目数"),0,50);
	pListCtrl->InsertColumn(3,_T("教师人数"),0,50);
	pListCtrl->InsertColumn(4,_T("项目数和教师人数比值"),0,150);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	for(InstituteNode *pInst = pSciDlg->iLL.head;pInst;pInst = pInst->nextNode)
	{
		for(TeamNode *pTeam = pInst->tLL->head;pTeam;pTeam = pTeam->nextNode)
		{
			packageTeam *pPac = remakeTeam(pTeam);
			if(pPac)
				pacTeamVec.push_back(pPac);
		}
	}
	sort(pacTeamVec.begin(),pacTeamVec.end(),compareFunc);
	if(pacTeamVec.size() >= 5)
	{
		for(int i = 0;i < 5;i++)
		{
			packageTeam *pPac = pacTeamVec[i];
			CString tempCstr;
			pListCtrl->InsertItem(i,pPac->pTeam->team.name);
			pListCtrl->SetItemText(i,1,pPac->pTeam->team.instituteName);
			tempCstr.Format(_T("%d"),pPac->itemNum);
			pListCtrl->SetItemText(i,2,tempCstr);
			tempCstr.Format(_T("%d"),pPac->teacherNum);
			pListCtrl->SetItemText(i,3,tempCstr);
			tempCstr.Format(_T("%f"),pPac->ratioValue);
			pListCtrl->SetItemText(i,4,tempCstr);
		}
	}else
	{
		for(int i = 0;i < (int)pacTeamVec.size();i++)
		{
			packageTeam *pPac = pacTeamVec[i];
			CString tempCstr;
			pListCtrl->InsertItem(i,pPac->pTeam->team.name);
			pListCtrl->SetItemText(i,1,pPac->pTeam->team.instituteName);
			tempCstr.Format(_T("%d"),pPac->itemNum);
			pListCtrl->SetItemText(i,2,tempCstr);
			tempCstr.Format(_T("%d"),pPac->teacherNum);
			pListCtrl->SetItemText(i,3,tempCstr);
			tempCstr.Format(_T("%f"),pPac->ratioValue);
			pListCtrl->SetItemText(i,4,tempCstr);
		}
	}
	return TRUE;
}

double doubleFormat2(double d)
{
	CString cstr;
	double newd;
	cstr.Format(_T("%.2lf"),d);
	newd = _wtof(cstr);
	return newd;
}

CStatisChildDlg4::packageTeam *CStatisChildDlg4::remakeTeam(TeamNode *pTeam)
{
	if(!wcslen(pTeam->team.manager))
		return NULL;
	packageTeam *pPacTeam = (packageTeam *)malloc(sizeof(packageTeam));
	pPacTeam->pTeam = pTeam;pPacTeam->itemNum = 0;pPacTeam->teacherNum = pTeam->team.teacherNum;pPacTeam->ratioValue = 0;
	for(programItemNode *pItem = pTeam->pLL->head;pItem;pItem = pItem->nextNode)
		(pPacTeam->itemNum)++;
	pPacTeam->ratioValue = doubleFormat2(pPacTeam->itemNum * 1.0 / pPacTeam->teacherNum);
	return pPacTeam;
}

void CStatisChildDlg4::OnDestroy()
{
	CDialogEx::OnDestroy();
	for(int i = 0;i < (int)pacTeamVec.size();i++)
		free(pacTeamVec[i]);
	pacTeamVec.clear();
	return;
}
