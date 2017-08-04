// StatisChildDlg3.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "StatisChildDlg3.h"
#include "afxdialogex.h"


// CStatisChildDlg3 对话框

IMPLEMENT_DYNAMIC(CStatisChildDlg3, CDialogEx)

CStatisChildDlg3::CStatisChildDlg3(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisChildDlg3::IDD, pParent)
{

}

CStatisChildDlg3::~CStatisChildDlg3()
{
}

void CStatisChildDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatisChildDlg3, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

bool compareFunc(CStatisChildDlg3::packageTeam *p1,CStatisChildDlg3::packageTeam *p2)
{
	return p1->itemCountryNum > p2->itemCountryNum;
}

// CStatisChildDlg3 消息处理程序


BOOL CStatisChildDlg3::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	pListCtrl->InsertColumn(0,_T("团队名称"),0,60);
	pListCtrl->InsertColumn(1,_T("院系名称"),0,80);
	pListCtrl->InsertColumn(2,_T("国家自然科学基金科研项目数"),0,170);
	pListCtrl->InsertColumn(3,_T("总经费"),0,100);
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
	if(pacTeamVec.size() >= 10)
	{
		for(int i = 0;i < 10;i++)
		{
			packageTeam *pPac = pacTeamVec[i];
			CString tempCstr;
			pListCtrl->InsertItem(i,pPac->pTeam->team.name);
			pListCtrl->SetItemText(i,1,pPac->pTeam->team.instituteName);
			tempCstr.Format(_T("%d"),pPac->itemCountryNum);
			pListCtrl->SetItemText(i,2,tempCstr);
			tempCstr.Format(_T("%f"),pPac->allCost);
			pListCtrl->SetItemText(i,3,tempCstr);
		}
	}else
	{
		for(int i = 0;i < (int)pacTeamVec.size();i++)
		{
			packageTeam *pPac = pacTeamVec[i];
			CString tempCstr;
			pListCtrl->InsertItem(i,pPac->pTeam->team.name);
			pListCtrl->SetItemText(i,1,pPac->pTeam->team.instituteName);
			tempCstr.Format(_T("%d"),pPac->itemCountryNum);
			pListCtrl->SetItemText(i,2,tempCstr);
			tempCstr.Format(_T("%f"),pPac->allCost);
			pListCtrl->SetItemText(i,3,tempCstr);
		}
	}
	return TRUE;
}

CStatisChildDlg3::packageTeam *CStatisChildDlg3::remakeTeam(TeamNode *pTeam)
{
	packageTeam *pPacTeam = (packageTeam *)malloc(sizeof(packageTeam));
	pPacTeam->pTeam = pTeam;pPacTeam->itemCountryNum = 0;pPacTeam->allCost = 0;
	for(programItemNode *pItem = pTeam->pLL->head;pItem;pItem = pItem->nextNode)
	{
		pPacTeam->allCost += pItem->item.cost;
		if(pItem->item.typePro == _T('2'))
			(pPacTeam->itemCountryNum)++;
	}
	return pPacTeam;
}

void CStatisChildDlg3::OnDestroy()
{
	CDialogEx::OnDestroy();
	for(int i = 0;i < (int)pacTeamVec.size();i++)
		free(pacTeamVec[i]);
	pacTeamVec.clear();
	return;
}
