// StatisChildDlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "SciPgM.h"
#include "StatisChildDlg2.h"
#include "afxdialogex.h"


// CStatisChildDlg2 对话框

IMPLEMENT_DYNAMIC(CStatisChildDlg2, CDialogEx)

CStatisChildDlg2::CStatisChildDlg2(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStatisChildDlg2::IDD, pParent)
{

}

CStatisChildDlg2::~CStatisChildDlg2()
{
}

void CStatisChildDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatisChildDlg2, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


bool compareFunc(CStatisChildDlg2::packageInsti *p1,CStatisChildDlg2::packageInsti *p2)
{
	return p1->itemNum > p2->itemNum;
}

// CStatisChildDlg2 消息处理程序


BOOL CStatisChildDlg2::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_LIST2);
	pListCtrl->InsertColumn(0,_T("院系名称"),0,100);
	pListCtrl->InsertColumn(1,_T("科研项目数"),0,100);
	pListCtrl->InsertColumn(2,_T("973项目数"),0,67);
	pListCtrl->InsertColumn(3,_T("863项目数"),0,67);
	pListCtrl->InsertColumn(4,_T("科研总经费"),0,100);
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
		pListCtrl->InsertItem(i,pPac->pinst->institude.name);
		tempCstr.Format(_T("%d"),pPac->itemNum);
		pListCtrl->SetItemText(i,1,tempCstr);
		tempCstr.Format(_T("%d"),pPac->item973Num);
		pListCtrl->SetItemText(i,2,tempCstr);
		tempCstr.Format(_T("%d"),pPac->item863Num);
		pListCtrl->SetItemText(i,3,tempCstr);
		tempCstr.Format(_T("%f"),pPac->allCost);
		pListCtrl->SetItemText(i,4,tempCstr);
	}
	return TRUE;
}

CStatisChildDlg2::packageInsti *CStatisChildDlg2::remakeInsti(InstituteNode *pInst)
{
	CStatisChildDlg2::packageInsti *pPacInst = (CStatisChildDlg2::packageInsti *)malloc(sizeof(CStatisChildDlg2::packageInsti));
	pPacInst->pinst = pInst;pPacInst->itemNum = 0;pPacInst->item973Num = 0;pPacInst->item863Num = 0;pPacInst->allCost = 0;
	for(TeamNode *pTeamNode = pInst->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
	{
		for(programItemNode *pProNode = pTeamNode->pLL->head;pProNode;pProNode = pProNode->nextNode)
		{
			(pPacInst->itemNum)++;pPacInst->allCost += pProNode->item.cost;
			if(pProNode->item.typePro == _T('1'))
			{
				(pPacInst->item973Num)++;
			}else if(pProNode->item.typePro == _T('3'))
			{
				(pPacInst->item863Num)++;
			}
		}
	}
	return pPacInst;
}

void CStatisChildDlg2::OnDestroy()
{
	CDialogEx::OnDestroy();
	for(int i = 0;i < (int)pacInstiVec.size();i++)
		free(pacInstiVec[i]);
	pacInstiVec.clear();
	return;
}
