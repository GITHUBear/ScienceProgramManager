// StatisChildDlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "StatisChildDlg1.h"
#include "afxdialogex.h"


// CStatisChildDlg1 对话框

IMPLEMENT_DYNAMIC(CStatisChildDlg1, CDialogEx)

CStatisChildDlg1::CStatisChildDlg1(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisChildDlg1::IDD, pParent)
{

}

CStatisChildDlg1::~CStatisChildDlg1()
{
}

void CStatisChildDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatisChildDlg1, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


bool compareFunc(CStatisChildDlg1::packageInsti *p1,CStatisChildDlg1::packageInsti *p2)
{
	return p1->ratioValue > p2->ratioValue;
}

// CStatisChildDlg1 消息处理程序

BOOL CStatisChildDlg1::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	pListCtrl->InsertColumn(0,_T("院系名称"),0,100);
	pListCtrl->InsertColumn(1,_T("教师总数"),0,100);
	pListCtrl->InsertColumn(2,_T("研究生总数"),0,100);
	pListCtrl->InsertColumn(3,_T("研究生与教师的人数比"),0,150);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	for(InstituteNode *pInst = pSciDlg->iLL.head;pInst;pInst = pInst->nextNode)
	{
		packageInsti *pPac = remakeInsti(pInst);
		if(pPac)
			pacInstiVec.push_back(pPac);
	}
	sort(pacInstiVec.begin(),pacInstiVec.end(),compareFunc);

	for(int i = 0;i < (int)pacInstiVec.size();i++)
	{
		packageInsti *pPac = pacInstiVec[i];
		CString tempCstr;
		pListCtrl->InsertItem(i,pPac->pInsti->institude.name);
		tempCstr.Format(_T("%d"),pPac->teacherNum);
		pListCtrl->SetItemText(i,1,tempCstr);
		tempCstr.Format(_T("%d"),pPac->postGraNum);
		pListCtrl->SetItemText(i,2,tempCstr);
		tempCstr.Format(_T("%.2f"),pPac->ratioValue);
		pListCtrl->SetItemText(i,3,tempCstr);
	}
	return TRUE;
}

double doubleFormat(double d)
{
	CString cstr;
	double newd;
	cstr.Format(_T("%.2lf"),d);
	newd = _wtof(cstr);
	return newd;
}

CStatisChildDlg1::packageInsti *CStatisChildDlg1::remakeInsti(InstituteNode *pInst)
{
	if(!wcslen(pInst->institude.manager))
		return NULL;
	CStatisChildDlg1::packageInsti *pPacInst = (CStatisChildDlg1::packageInsti *)malloc(sizeof(CStatisChildDlg1::packageInsti));
	pPacInst->pInsti = pInst;pPacInst->teacherNum = 0;pPacInst->postGraNum = 0;
	for(TeamNode *pTeamNode = pInst->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
	{
		if(!wcslen(pTeamNode->team.manager))
			continue;
		pPacInst->teacherNum += pTeamNode->team.teacherNum;
		pPacInst->postGraNum += pTeamNode->team.postGraduaNum;
	}
	if(pPacInst->teacherNum == 0 || pPacInst->postGraNum == 0)
	{
		free(pPacInst);
		return NULL;
	}
	pPacInst->ratioValue = doubleFormat(pPacInst->postGraNum * 1.0 / pPacInst->teacherNum);
	return pPacInst;
}

void CStatisChildDlg1::OnDestroy()
{
	CDialogEx::OnDestroy();
	for(int i = 0;i < (int)pacInstiVec.size();i++)
		free(pacInstiVec[i]);
	pacInstiVec.clear();
	return;
}
