
// SciPgMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "SciPgMDlg.h"
#include "afxdialogex.h"
#include "InstituteDlg.h"
#include "resource.h"
#include "TeamDlg.h"
#include "ProgramDlg.h"
#include "FileDlg.h"
#include "TableResetDlg.h"
#include "FindInfoDlg.h"
#include "StatisticDlg.h"
#include "FAQDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSciPgMDlg �Ի���



CSciPgMDlg::CSciPgMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSciPgMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_ICON1);
	hAccel = LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINMENU));
}

void CSciPgMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSERTBTN, insertBtn);
	DDX_Control(pDX, IDC_DELEBTN, deleteBtn);
	DDX_Control(pDX, IDC_EDITBTN, editBtn);
}

BEGIN_MESSAGE_MAP(CSciPgMDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSERTBTN, &CSciPgMDlg::OnBnClickedInsertbtn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_DELEBTN, &CSciPgMDlg::OnBnClickedDelebtn)
	ON_BN_CLICKED(IDC_EDITBTN, &CSciPgMDlg::OnBnClickedEditbtn)
	ON_COMMAND(ID_32771, &CSciPgMDlg::OnOpenFile)
	ON_COMMAND(ID_32779, &CSciPgMDlg::OnSaveInstituteTable)
	ON_COMMAND(ID_32780, &CSciPgMDlg::OnSaveTeamTable)
	ON_COMMAND(ID_32781, &CSciPgMDlg::OnSaveProgramTable)
	ON_COMMAND(ID_32775, &CSciPgMDlg::OnSaveAll)
	ON_COMMAND(ID_Menu, &CSciPgMDlg::OnTableReset)
	ON_COMMAND(ID_32778, &CSciPgMDlg::OnExit)
	ON_COMMAND(ID_32776, &CSciPgMDlg::OnFormLinkedList)
	ON_COMMAND(ID_32796, &CSciPgMDlg::OnClearLinkedList)
	ON_COMMAND(ID_32800, &CSciPgMDlg::OnFuncUse)
	ON_COMMAND(ID_32801, &CSciPgMDlg::OnFuncUnuse)
	ON_COMMAND(ID_32802, &CSciPgMDlg::On32802)
	ON_COMMAND(ID_32783, &CSciPgMDlg::OnFindInfo)
	ON_COMMAND(ID_32782, &CSciPgMDlg::OnStatistic)
	ON_COMMAND(ID_32784, &CSciPgMDlg::OnIntro)
	ON_COMMAND(ID_32785, &CSciPgMDlg::OnAbout)
END_MESSAGE_MAP()


// CSciPgMDlg ��Ϣ�������

BOOL CSciPgMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	SetFocus();
	autoSynSwitch = true;
	iLL.head = NULL; iLL.tail = NULL;
	CMenu *menu = GetMenu()->GetSubMenu(2);
	menu->CheckMenuRadioItem(ID_32800,ID_32801,ID_32800,MF_BYCOMMAND);

	HICON insertIconBtn = AfxGetApp()->LoadIcon(IDI_INSERTICON);
	HICON deleteIconBtn = AfxGetApp()->LoadIcon(IDI_DELETEICON);
	HICON editIconBtn = AfxGetApp()->LoadIcon(IDI_EDITICON);
	insertBtn.SetIcon(insertIconBtn);
	deleteBtn.SetIcon(deleteIconBtn);
	editBtn.SetIcon(editIconBtn);
	ModifyStyle(this->m_hWnd,WS_THICKFRAME,0,0);

	//ʹ���б�ؼ������ʼ���б�
	//��ʼ���б�1
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	pListCtrl->InsertColumn(0,_T("Ժϵ����"),0,150);
	pListCtrl->InsertColumn(1,_T("������"),0,100);
	pListCtrl->InsertColumn(2,_T("��ϵ�绰"),0,150);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//��ʼ���б�2
	CListCtrl *pListCtrl2 = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	pListCtrl2->InsertColumn(0,_T("�Ŷ�����"),0,100);
	pListCtrl2->InsertColumn(1,_T("������"),0,100);
	pListCtrl2->InsertColumn(2,_T("��ʦ����"),0,100);
	pListCtrl2->InsertColumn(3,_T("�о�������"),0,100);
	pListCtrl2->InsertColumn(4,_T("����Ժϵ"),0,100);
	pListCtrl2->SetBkColor(RGB(205,226,252));
	pListCtrl2->SetTextBkColor(RGB(205,226,252));
	pListCtrl2->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//��ʼ���б�3
	CListCtrl *pListCtrl3 = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pListCtrl3->InsertColumn(0,_T("��Ŀ���"),0,100);
	pListCtrl3->InsertColumn(1,_T("��Ŀ���"),0,100);
	pListCtrl3->InsertColumn(2,_T("��ʼʱ��"),0,100);
	pListCtrl3->InsertColumn(3,_T("��Ŀ����"),0,100);
	pListCtrl3->InsertColumn(4,_T("��Ŀ������"),0,100);
	pListCtrl3->InsertColumn(5,_T("�����Ŷ�"),0,100);
	pListCtrl3->InsertColumn(6,_T("����Ժϵ"),0,100);
	pListCtrl3->SetBkColor(RGB(205,226,252));
	pListCtrl3->SetTextBkColor(RGB(205,226,252));
	pListCtrl3->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSciPgMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSciPgMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//���෽��SetListViewItem,����������ѡ�����б�ؼ��в�����Ŀ
void SetListViewItem(CListCtrl *pListCtrl, std::vector<CString,std::allocator<CString>> &cstrVec)
{
	auto vecSize = cstrVec.size();
	int ctr = pListCtrl->GetItemCount();
	pListCtrl->InsertItem(ctr,cstrVec[0]);
	for(decltype(vecSize) i = 1;i < vecSize;i++)
		pListCtrl->SetItemText(ctr,i,cstrVec[i]);
}

InstituteNode *CSciPgMDlg::initInsti()
{
	InstituteNode *pinstNode = (InstituteNode *)malloc(sizeof(InstituteNode));
	pinstNode->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));pinstNode->tLL->head = NULL;pinstNode->tLL->tail = NULL;
	wcscpy_s(pinstNode->institude.name,cstringVec[0]);
	wcscpy_s(pinstNode->institude.manager,cstringVec[1]);
	wcscpy_s(pinstNode->institude.tel,cstringVec[2]);
	pinstNode->nextNode = NULL;pinstNode->prevNode = NULL;
	return pinstNode;
}

TeamNode *CSciPgMDlg::initTeam()
{
	TeamNode *pTeamNode = (TeamNode *)malloc(sizeof(TeamNode));
	pTeamNode->pLL = (programLinkedList *)malloc(sizeof(programLinkedList));pTeamNode->pLL->head = NULL;pTeamNode->pLL->tail = NULL;
	wcscpy_s(pTeamNode->team.name,cstringVec[0]);
	wcscpy_s(pTeamNode->team.manager,cstringVec[1]);
	pTeamNode->team.teacherNum = _wtoi(cstringVec[2]);
	pTeamNode->team.postGraduaNum = _wtoi(cstringVec[3]);
	wcscpy_s(pTeamNode->team.instituteName,cstringVec[4]);
	pTeamNode->nextNode = NULL;pTeamNode->prevNode = NULL;
	return pTeamNode;
}

programItemNode *CSciPgMDlg::initProgram()
{
	programItemNode *pProNode = (programItemNode *)malloc(sizeof(programItemNode));
	wcscpy_s(pProNode->item.number,cstringVec[0]);
	pProNode->item.typePro = cstringVec[1][0];
	wcscpy_s(pProNode->item.startTime,cstringVec[2]);
	pProNode->item.cost = (float)_wtof(cstringVec[3]);
	wcscpy_s(pProNode->item.manager,cstringVec[4]);
	wcscpy_s(pProNode->item.teamName,cstringVec[5]);
	wcscpy_s(pProNode->item.instiName,cstringVec[6]);
	pProNode->nextNode = NULL;pProNode->prevNode = NULL;
	return pProNode;
}

void CSciPgMDlg::insertInsti2iLL(InstituteNode *pInstiNode)
{
	if(iLL.head)
	{
		iLL.tail->nextNode = pInstiNode;
		pInstiNode->prevNode = iLL.tail;
		iLL.tail = pInstiNode;
		pInstiNode->nextNode = NULL;
	}else
	{
		iLL.head = pInstiNode;
		iLL.tail = pInstiNode;
		pInstiNode->nextNode = NULL;pInstiNode->prevNode = NULL;
	}
	return;
}



void CSciPgMDlg::insertTeam2tLL(TeamLinkedList *tLL,TeamNode *pTeamNode)
{
	if(tLL->head)
	{
		tLL->tail->nextNode = pTeamNode;
		pTeamNode->prevNode = tLL->tail;
		tLL->tail = pTeamNode;
		pTeamNode->nextNode = NULL;
	}else
	{
		tLL->head = pTeamNode;
		tLL->tail = pTeamNode;
		pTeamNode->nextNode = NULL;pTeamNode->prevNode = NULL;
	}
	return;
}

void CSciPgMDlg::insertProg2pLL(programLinkedList *pLL,programItemNode *pProNode)
{
	if(pLL->head)
	{
		pLL->tail->nextNode = pProNode;
		pProNode->prevNode = pLL->tail;
		pLL->tail = pProNode;
		pProNode->nextNode = NULL;
	}else
	{
		pLL->head = pProNode;
		pLL->tail = pProNode;
		pProNode->nextNode = NULL;pProNode->prevNode = NULL;
	}
	return;
}

//���밴ť��Ӧ
void CSciPgMDlg::OnBnClickedInsertbtn()
{
	CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
	HTREEITEM hTreeItem;
	switch (this->FocusedListID)
	{
	case IDC_INSTILIST:
		{
			CInstituteDlg cinstiDlg(this);
			cinstiDlg.isEdit = 0;
			if(IDOK == cinstiDlg.DoModal())
			{
				this->cstringVec = cinstiDlg.cstringVec;
				delete(cinstiDlg);
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
				std::string str = CT2A(cstringVec[0]);
				std::map<std::string,InstituteNode *>::iterator mapIter = instiNameMap.find(str);
				if(autoSynSwitch)
				{
					for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
					std::string str = CT2A(cstringVec[0]);
					//�������
					std::map<std::string,InstituteNode *>::iterator mapIter = instiNameMap.find(str);
					if(mapIter == instiNameMap.end())
					{
						pTreeCtrl->InsertItem(cstringVec[0],TVI_ROOT,hTreeItem);
						InstituteNode *pinstNode = initInsti();
						insertInsti2iLL(pinstNode);
						//��ַ��Ϣ����map
						instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(str,pinstNode));
					}else
					{
						InstituteNode *pinstNode = mapIter->second;
						if(wcslen(pinstNode->institude.manager))
						{
							MessageBox(_T("�����Ѵ��ڸ�����,�޷�¼��!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
							return;
						}else
						{
							wcscpy_s(pinstNode->institude.manager,cstringVec[1]);
							wcscpy_s(pinstNode->institude.tel,cstringVec[2]);
						}
					}
				}
				SetListViewItem(pListCtrl,this->cstringVec);
			}
		}
		break;
	case IDC_TEAMLIST:
		{
			CTeamDlg cteamDlg(this);
			cteamDlg.isEdit = 0;
			if(IDOK == cteamDlg.DoModal())
			{
				this->cstringVec = cteamDlg.cstringVec;
				delete(cteamDlg);
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
				if(autoSynSwitch)
				{
					std::string str = CT2A(cstringVec[4]);  //Ժϵ
					std::string strTemp = CT2A(cstringVec[0]);  //�Ŷ���
					std::map<std::string,InstituteNode *>::iterator instiMapIter = instiNameMap.find(str);
					std::map<std::string,TeamNode *>::iterator teamMapIter = teamNameMap.find(strTemp + " " + str);
					if(teamMapIter == teamNameMap.end())
					{
						InstituteNode *pinstNode;
						//����ǰ������Ϣδ�����ڴ�
						if(instiMapIter == instiNameMap.end())
						{
							//���δ���ٵĶ��������Ժϵ��Ϣδ�����򿪱�Ժϵ��Ϣ
							pinstNode = (InstituteNode *)malloc(sizeof(InstituteNode));
							pinstNode->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
							pinstNode->tLL->head = NULL;pinstNode->tLL->tail = NULL;
							wcscpy_s(pinstNode->institude.name,cstringVec[4]);
							wcscpy_s(pinstNode->institude.manager,_T(""));
							wcscpy_s(pinstNode->institude.tel,_T(""));
							insertInsti2iLL(pinstNode);
							instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(str,pinstNode));
							CListCtrl *pTempListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
							pTempListCtrl->InsertItem(pTempListCtrl->GetItemCount(),cstringVec[4]);
							//���ؼ�����
							for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
							hTreeItem = pTreeCtrl->InsertItem(cstringVec[4],TVI_ROOT,hTreeItem);
							pTreeCtrl->InsertItem(cstringVec[0],hTreeItem);
						}else
						{
							//���δ�����ڴ�Ķ����Ժϵ��Ϣ�Ѵ���
							pinstNode = instiMapIter->second;
							//���ؼ�����
							for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstringVec[4];hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
							HTREEITEM hItem;
							for(hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem;hItem = pTreeCtrl->GetNextSiblingItem(hItem));
							pTreeCtrl->InsertItem(cstringVec[0],hTreeItem,hItem);
						}
						TeamNode *pTeamNode = initTeam();
						insertTeam2tLL(pinstNode->tLL,pTeamNode);
						teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(strTemp + " " + str,pTeamNode));
					}else
					{
						//��ǰ�Ŷ���Ϣ�ѿ��ٹ��ڴ�
						TeamNode *pTeamNode = teamMapIter->second;
						if(wcslen(pTeamNode->team.manager))
						{
							//���ٹ��ڴ沢�ѱ�������ȫ����Ϣ
							MessageBox(_T("�Ŷ�������,�޷�¼��!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
							return;
						}else
						{
							//��δ��ֵ����и�ֵ
							wcscpy_s(pTeamNode->team.manager,cstringVec[1]);
							pTeamNode->team.teacherNum = _wtoi(cstringVec[2]);
							pTeamNode->team.postGraduaNum = _wtoi(cstringVec[3]);
							wcscpy_s(pTeamNode->team.instituteName,cstringVec[4]);
						}
					}
				}
				SetListViewItem(pListCtrl,this->cstringVec);
			}
		}
		break;
	case IDC_ITEMLIST:
		{
			CProgramDlg cproDlg(this);
			cproDlg.isEdit = 0;
			if(IDOK == cproDlg.DoModal())
			{
				this->cstringVec = cproDlg.cstringVec;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
				if(autoSynSwitch)
				{
					std::string str = CT2A(cstringVec[6]);  //Ժϵ
					std::string str2 = CT2A(cstringVec[5]);  //�Ŷ���
					std::string str3 = CT2A(cstringVec[0]);	 //��Ŀ���
					std::map<std::string,InstituteNode *>::iterator instMapIter = instiNameMap.find(str);
					std::map<std::string,TeamNode *>::iterator teamMapIter = teamNameMap.find(str2 + " " + str);
					std::map<std::string,programItemNode *>::iterator itemMapIter = itemNumMap.find(str3);
					if(itemMapIter == itemNumMap.end())
					{
						//����Ŀ��δ¼��
						if(teamMapIter == teamNameMap.end())
						{
							//����Ŀ���Ŷ���Ϣ������
							InstituteNode *pinstNode;
							TeamNode *pTeamNode;
							if(instMapIter == instiNameMap.end())
							{
								//����Ŀ��Ժϵ��ϢҲ������,�����µ�Ժϵ�ڵ���Ŷӽڵ�
								pinstNode = (InstituteNode *)malloc(sizeof(InstituteNode));
								pinstNode->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
								pinstNode->tLL->head = NULL;pinstNode->tLL->tail = NULL;
								wcscpy_s(pinstNode->institude.name,cstringVec[6]);
								wcscpy_s(pinstNode->institude.manager,_T(""));
								wcscpy_s(pinstNode->institude.tel,_T(""));
								insertInsti2iLL(pinstNode);
								instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(str,pinstNode));
								CListCtrl *pTempListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
								pTempListCtrl->InsertItem(pTempListCtrl->GetItemCount(),cstringVec[6]);

								pTeamNode = (TeamNode *)malloc(sizeof(TeamNode));
								pTeamNode->pLL = (programLinkedList *)malloc(sizeof(programLinkedList));
								pTeamNode->pLL->head = NULL;pTeamNode->pLL->tail = NULL;
								wcscpy_s(pTeamNode->team.name,cstringVec[5]);
								wcscpy_s(pTeamNode->team.manager,_T(""));
								pTeamNode->team.teacherNum = -1;
								pTeamNode->team.postGraduaNum = -1;
								wcscpy_s(pTeamNode->team.instituteName,_T(""));
								insertTeam2tLL(pinstNode->tLL,pTeamNode);
								teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(str2 + " " + str,pTeamNode));
								pTempListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
								pTempListCtrl->InsertItem(pTempListCtrl->GetItemCount(),cstringVec[5]);
								pTempListCtrl->SetItemText(pTempListCtrl->GetItemCount() - 1,4,cstringVec[6]);
								//���ؼ�����
								for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[6],TVI_ROOT,hTreeItem);
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[5],hTreeItem);
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[0],hTreeItem);
							}else
							{
								pinstNode = instMapIter->second;
								//����Ŀ��Ժϵ��Ϣ�����򲻿���Ժϵ,�����µ��Ŷӽڵ�
								pTeamNode = (TeamNode *)malloc(sizeof(TeamNode));
								pTeamNode->pLL = (programLinkedList *)malloc(sizeof(programLinkedList));
								pTeamNode->pLL->head = NULL;pTeamNode->pLL->tail = NULL;
								wcscpy_s(pTeamNode->team.name,cstringVec[5]);
								wcscpy_s(pTeamNode->team.manager,_T(""));
								pTeamNode->team.teacherNum = -1;
								pTeamNode->team.postGraduaNum = -1;
								wcscpy_s(pTeamNode->team.instituteName,_T(""));
								insertTeam2tLL(pinstNode->tLL,pTeamNode);
								teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(str2 + " " + str,pTeamNode));
								CListCtrl *pTempListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
								pTempListCtrl->InsertItem(pTempListCtrl->GetItemCount(),cstringVec[5]);
								pTempListCtrl->SetItemText(pTempListCtrl->GetItemCount() - 1,4,cstringVec[6]);
								//���ؼ�����
								for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstringVec[6];hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
								HTREEITEM hItem;
								for(hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem && pTreeCtrl->GetItemText(hItem) != cstringVec[0];hItem = pTreeCtrl->GetNextSiblingItem(hItem));
								if(pTreeCtrl->GetItemText(hItem) != cstringVec[5])
									hItem = pTreeCtrl->InsertItem(cstringVec[5],hTreeItem,hItem);
								pTreeCtrl->InsertItem(cstringVec[0],hItem);
							}
							programItemNode *pProItemNode = initProgram();
							insertProg2pLL(pTeamNode->pLL,pProItemNode);
							itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(str3,pProItemNode));
						}else
						{
							//����Ŀ���Ŷ���Ϣ�ѿ����ڴ�
							TeamNode *pTeamNode = teamMapIter->second;
							programItemNode *pProItemNode = initProgram();
							insertProg2pLL(pTeamNode->pLL,pProItemNode);
							itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(str3,pProItemNode));
							//���ؼ�����
							for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != cstringVec[6];hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
							HTREEITEM hItem,hIt;
							for(hItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hItem) != cstringVec[5];hItem = pTreeCtrl->GetNextSiblingItem(hItem));
							for(hIt = pTreeCtrl->GetChildItem(hItem);hIt;hIt = pTreeCtrl->GetNextSiblingItem(hIt));
							pTreeCtrl->InsertItem(cstringVec[0],hItem,hIt);
						}
					}else
					{
						//����Ŀ�ѱ�¼��
						MessageBox(_T("��Ŀ����������,�޷�¼��!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
						return;
					}
				}
				SetListViewItem(pListCtrl,this->cstringVec);
			}
		}
		break;
	default:
		break;
	}
}

//ɾ����ť��Ӧ
void CSciPgMDlg::OnBnClickedDelebtn()
{
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(this->FocusedListID);
	CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
	HTREEITEM hTreeItem;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if(pos)
	{
		int response = MessageBox(_T("ȷ��ɾ��ѡ�е�����"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
		if(response == IDOK)
		{
			while(pos)
			{
				int nId = pListCtrl->GetNextSelectedItem(pos);
				if(this->FocusedListID == IDC_TEAMLIST)
				{
					CString cstrTeamName = pListCtrl->GetItemText(nId,0);
					CString cstrInstName = pListCtrl->GetItemText(nId,4);
					std::string strTeamName = CT2A(cstrTeamName);
					std::string strInstiName = CT2A(cstrInstName);
					std::map<std::string,TeamNode *>::iterator teamNameIter = teamNameMap.find(strTeamName + " " + strInstiName);
					std::map<std::string,InstituteNode *>::iterator instiNameIter = instiNameMap.find(strInstiName);
					if(teamNameIter != teamNameMap.end())
					{
						//�ҵ�
						//1.ɾ�����ؼ����Ŷ��µ���������
						std::set<CString> tempSet; //���������Ŀ��ŵļ���
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrInstName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrTeamName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(HTREEITEM hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem;hItem = pTreeCtrl->GetNextSiblingItem(hItem))
							tempSet.insert(std::set<CString>::value_type(pTreeCtrl->GetItemText(hItem)));
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.ɾ���б�ؼ��е������Ŀ
						CListCtrl *pItemListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
						for(int NumOfItem = 0;NumOfItem < pItemListCtrl->GetItemCount();NumOfItem++)
						{
							if(tempSet.find(pItemListCtrl->GetItemText(NumOfItem,0)) != tempSet.end())
							{
								pItemListCtrl->DeleteItem(NumOfItem);
								NumOfItem--;
							}
						}
						//3.���ڴ�ռ�ɾ����Ŀ��Ϣ
						TeamNode *pTeamNode = teamNameIter->second;
						InstituteNode *pInstiNode = instiNameIter->second;
						programItemNode *pProItemNode,*pProFastNode;
						if(pTeamNode->pLL->head)
						{
							for(pProItemNode = pTeamNode->pLL->head,pProFastNode = pProItemNode->nextNode;
								pProFastNode;pProItemNode = pProFastNode,pProFastNode = pProItemNode->nextNode)
							{
								CString cstrItemNum;
								cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
								std::string strItemNum = CT2A(cstrItemNum);
								std::map<std::string,programItemNode *>::iterator tempIter = itemNumMap.find(strItemNum);
								if(tempIter != itemNumMap.end())
									itemNumMap.erase(tempIter);
								free(pProItemNode);
							}
							CString cstrItemNum;
							cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
							std::string strItemNum = CT2A(cstrItemNum);
							std::map<std::string,programItemNode *>::iterator tempIter = itemNumMap.find(strItemNum);
							if(tempIter != itemNumMap.end())
								itemNumMap.erase(tempIter);
							free(pProItemNode);
						}
						if(pTeamNode->nextNode && pTeamNode->prevNode)
						{
							pTeamNode->prevNode->nextNode = pTeamNode->nextNode;
							pTeamNode->nextNode->prevNode = pTeamNode->prevNode;
						}else if(pTeamNode->nextNode)
						{
							pTeamNode->nextNode->prevNode = NULL;
							pInstiNode->tLL->head = pTeamNode->nextNode;
						}else if(pTeamNode->prevNode)
						{
							pTeamNode->prevNode->nextNode = NULL;
							pInstiNode->tLL->tail = pTeamNode->prevNode;
						}else
						{
							pInstiNode->tLL->head = NULL;
							pInstiNode->tLL->tail = NULL;
						}
						free(pTeamNode->pLL);
						free(pTeamNode);
						teamNameMap.erase(teamNameIter);
					}
				}else if(this->FocusedListID == IDC_INSTILIST)
				{
					CString cstrInstiName = pListCtrl->GetItemText(nId,0);
					std::string strInstiName = CT2A(cstrInstiName);
					std::map<std::string,InstituteNode *>::iterator instiNameIter = instiNameMap.find(strInstiName);
					if(instiNameIter != instiNameMap.end())
					{
						//1.ɾ�����ؼ���ѧԺ�µ���������
						std::set<CString> tempTeamSet,tempItemSet;
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrInstiName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(HTREEITEM hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem;hItem = pTreeCtrl->GetNextSiblingItem(hItem))
						{
							tempTeamSet.insert(pTreeCtrl->GetItemText(hItem));
							for(HTREEITEM hItem2 = pTreeCtrl->GetChildItem(hItem);hItem2;hItem2 = pTreeCtrl->GetNextSiblingItem(hItem2))
								tempItemSet.insert(pTreeCtrl->GetItemText(hItem2));
						}
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.ɾ���б�ؼ��е������Ŀ
						CListCtrl *pTeamListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
						for(int NumOfItem = 0;NumOfItem < pTeamListCtrl->GetItemCount();NumOfItem++)
						{
							if(tempTeamSet.find(pTeamListCtrl->GetItemText(NumOfItem,0)) != tempTeamSet.end()
								&& pTeamListCtrl->GetItemText(NumOfItem,4) == cstrInstiName)
							{
								pTeamListCtrl->DeleteItem(NumOfItem);
								NumOfItem--;
							}
						}
						CListCtrl *pItemListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
						for(int NumOfItem = 0;NumOfItem < pItemListCtrl->GetItemCount();NumOfItem++)
						{
							if(tempItemSet.find(pItemListCtrl->GetItemText(NumOfItem,0)) != tempItemSet.end())
							{
								pItemListCtrl->DeleteItem(NumOfItem);
								NumOfItem--;
							}
						}
						//3.���ڴ�ռ�ɾ����Ŀ��Ϣ
						InstituteNode *pInstiNode =instiNameIter->second;
						TeamNode *pTeamNode,*pFastNode;
						if(pInstiNode->tLL->head)
						{
							pTeamNode = pInstiNode->tLL->head;
							pFastNode = pTeamNode->nextNode;
							for(;pFastNode;pTeamNode = pFastNode,pFastNode = pTeamNode->nextNode)
							{
								programItemNode *pProItemNode = pTeamNode->pLL->head;
								if(pProItemNode)
								{
									programItemNode *pProFastNode = pProItemNode->nextNode;
									for(;pProFastNode;pProItemNode = pProFastNode,pProFastNode = pProItemNode->nextNode)
									{
										CString cstrItemNum;
										cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
										std::string strItemNum = CT2A(cstrItemNum);
										itemNumMap.erase(itemNumMap.find(strItemNum));
										free(pProItemNode);
									}
									CString cstrItemNum;
									cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
									std::string strItemNum = CT2A(cstrItemNum);
									itemNumMap.erase(itemNumMap.find(strItemNum));
									free(pProItemNode);
								}
								CString cstrTeamName,cstrTeamInsti;
								cstrTeamName.Format(_T("%s"),pTeamNode->team.name);
								cstrTeamInsti.Format(_T("%s"),pTeamNode->team.instituteName);
								std::string strTeamName = CT2A(cstrTeamName),strTeamInsti = CT2A(cstrTeamInsti);
								std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(strTeamName + " " + strTeamInsti);
								if(teamIter != teamNameMap.end())
									teamNameMap.erase(teamIter);
								free(pTeamNode->pLL);
								free(pTeamNode);
							}
							programItemNode *pProItemNode = pTeamNode->pLL->head;
							if(pProItemNode)
							{
								programItemNode *pProFastNode = pProItemNode->nextNode;
								for(;pProFastNode;pProItemNode = pProFastNode,pProFastNode = pProItemNode->nextNode)
								{
									CString cstrItemNum;
									cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
									std::string strItemNum = CT2A(cstrItemNum);
									itemNumMap.erase(itemNumMap.find(strItemNum));
									free(pProItemNode);
								}
								CString cstrItemNum;
								cstrItemNum.Format(_T("%s"),pProItemNode->item.number);
								std::string strItemNum = CT2A(cstrItemNum);
								itemNumMap.erase(itemNumMap.find(strItemNum));
								free(pProItemNode);
							}
							CString cstrTeamName,cstrTeamInsti;
							cstrTeamName.Format(_T("%s"),pTeamNode->team.name);
							cstrTeamInsti.Format(_T("%s"),pTeamNode->team.instituteName);
							std::string strTeamName = CT2A(cstrTeamName),strTeamInsti = CT2A(cstrTeamInsti);
							std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(strTeamName + " " + strTeamInsti);
							if(teamIter != teamNameMap.end())
								teamNameMap.erase(teamIter);
							free(pTeamNode->pLL);
							free(pTeamNode);
						}
						if(pInstiNode->prevNode && pInstiNode->nextNode)
						{
							pInstiNode->prevNode->nextNode = pInstiNode->nextNode;
							pInstiNode->nextNode->prevNode = pInstiNode->prevNode;
						}else if(pInstiNode->prevNode)
						{
							pInstiNode->prevNode->nextNode = NULL;
							iLL.tail = pInstiNode->prevNode;
						}else if(pInstiNode->nextNode)
						{
							pInstiNode->nextNode->prevNode = NULL;
							iLL.head = pInstiNode->nextNode;
						}else
						{
							iLL.head = NULL;iLL.tail = NULL;
						}
						instiNameMap.erase(instiNameIter);
						free(pInstiNode->tLL);
						free(pInstiNode);
					}
				}else if(this->FocusedListID == IDC_ITEMLIST)
				{
					CString cstrItemNum = pListCtrl->GetItemText(nId,0);
					CString cstrItemInsti = pListCtrl->GetItemText(nId,6);
					CString cstrItemTeam = pListCtrl->GetItemText(nId,5);
					std::string strItemNum = CT2A(cstrItemNum);
					std::string strItemInsti = CT2A(cstrItemInsti);
					std::string strItemTeam = CT2A(cstrItemTeam);
					std::map<std::string,TeamNode *>::iterator teamItemIter = teamNameMap.find(strItemTeam + " " + strItemInsti); 
					std::map<std::string,programItemNode *>::iterator proItemIter = itemNumMap.find(strItemNum);
					if(proItemIter != itemNumMap.end())
					{
						//1.ɾ�����ؼ������Ӧ��Ŀ����
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrItemInsti;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrItemTeam;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrItemNum;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.���ڴ�ռ�ɾ����Ŀ��Ϣ
						programItemNode *pProItemNode = proItemIter->second;
						TeamNode *pTeamNode = teamItemIter->second;
						if(pProItemNode->nextNode && pProItemNode->prevNode)
						{
							pProItemNode->prevNode->nextNode = pProItemNode->nextNode;
							pProItemNode->nextNode->prevNode = pProItemNode->prevNode;
						}else if(pProItemNode->nextNode)
						{
							pProItemNode->nextNode->prevNode = NULL;
							pTeamNode->pLL->head = pProItemNode->nextNode;
						}else if(pProItemNode->prevNode)
						{
							pProItemNode->prevNode->nextNode = NULL;
							pTeamNode->pLL->tail = pProItemNode->prevNode;
						}else
						{
							pTeamNode->pLL->head = NULL;
							pTeamNode->pLL->tail = NULL;
						}
						free(pProItemNode);
						itemNumMap.erase(proItemIter);
						
					}
				}
				if(nId >= 0 && nId < pListCtrl->GetItemCount())
					pListCtrl->DeleteItem(nId);
				pos = pListCtrl->GetFirstSelectedItemPosition();
			}
		}	
	}else
		MessageBox(_T("No item is selected!"),_T("NOTICE"));

}

//�޸İ�ť��Ӧ
void CSciPgMDlg::OnBnClickedEditbtn()
{
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(this->FocusedListID);
	int nSeleted = pListCtrl->GetSelectionMark();
	this->cstringVec.clear();
	if(nSeleted < 0)
	{
		MessageBox(_T("No item is selected!"),_T("NOTICE"));
		return;
	}
	switch (this->FocusedListID)
	{
	case IDC_INSTILIST:
		{
			CString keyCString;
			std::string keyString;
			for(int i = 0;i < 3;i++)
			{
				CString cstr = pListCtrl->GetItemText(nSeleted,i);
				if(!i) {keyCString = cstr;keyString = CT2A(cstr);}
				cstringVec.push_back(cstr);
			}
			std::map<std::string,InstituteNode *>::iterator instiIter = instiNameMap.find(keyString);
			if(instiIter == instiNameMap.end())
			{
				MessageBox(_T("��⵽�����ļ���δ��������,Ϊ�˻�ø��õ�����,�뵽�˵����������������Ctrl + F��ݼ�,�����޸���ȡ��"),_T("NOTICE"));
				return;
			}
			InstituteNode *pInstiNode = instiIter->second;
			CInstituteDlg cinstiDlg(this);
			cinstiDlg.isEdit = 1;
			cinstiDlg.cstringVec.clear();
			for(auto &cstr : cstringVec)
				cinstiDlg.cstringVec.push_back(cstr);
			instiNameMap.erase(instiIter);
			if(IDOK == cinstiDlg.DoModal())
			{
				//�ı�ͼ�οؼ��е���ʾ
				//���ؼ�
				this->cstringVec = cinstiDlg.cstringVec;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
				int nSel = pListCtrl->GetSelectionMark();
				std::string instiNameStr = CT2A(cstringVec[0]);
				std::map<std::string,InstituteNode *>::iterator instiIter2 = instiNameMap.find(instiNameStr);
				if(instiIter2 != instiNameMap.end())
				{
					MessageBox(_T("��⵽��ѧԺ���Ѵ���,�޷�����!"),_T("NOTICE"));
					instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(instiNameStr,pInstiNode));
					return;
				}
				pListCtrl->SetItemText(nSel,0,cstringVec[0]);
				pListCtrl->SetItemText(nSel,1,cstringVec[1]);
				pListCtrl->SetItemText(nSel,2,cstringVec[2]);
				//�ı�ѧԺ�ڵ���Ϣ
				wcscpy_s(pInstiNode->institude.name,cstringVec[0]);
				wcscpy_s(pInstiNode->institude.manager,cstringVec[1]);
				wcscpy_s(pInstiNode->institude.tel,cstringVec[2]);
				instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(instiNameStr,pInstiNode));
				//���ѧԺ������ؼ��ַ����ı䣬��ô����Ӧ����
				if(keyCString != cstringVec[0])
				{
					//�ı�������������е���Ϣ
					//�Ŷӱ�
					pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
					int itemNum = pListCtrl->GetItemCount();
					for(int i = 0;i < itemNum;i++)
					{
						if(keyCString == pListCtrl->GetItemText(i,4))
						{
							CString secKeyCstr = pListCtrl->GetItemText(i,0);
							std::string secKeyStr = CT2A(secKeyCstr);
							std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(secKeyStr + " " + keyString);
							TeamNode *pTeamNode = teamIter->second;
							wcscpy_s(pTeamNode->team.instituteName,cstringVec[0]);
							teamNameMap.erase(teamIter);
							teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(secKeyStr + " " + instiNameStr,pTeamNode));
							pListCtrl->SetItemText(i,4,cstringVec[0]);
						}
					}
					//��Ŀ��
					pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
					itemNum = pListCtrl->GetItemCount();
					for(int i = 0;i < itemNum;i++)
					{
						if(keyCString == pListCtrl->GetItemText(i,6))
						{
							CString itemNumCStr = pListCtrl->GetItemText(i,0);
							std::string itemNumStr = CT2A(itemNumCStr);
							std::map<std::string,programItemNode *>::iterator itemIter = itemNumMap.find(itemNumStr);
							programItemNode *pItemNode = itemIter->second;
							wcscpy_s(pItemNode->item.instiName,cstringVec[0]);
							pListCtrl->SetItemText(i,6,cstringVec[0]);
						}
					}
					//��
					CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
					HTREEITEM hTreeItem;
					for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl && pTreeCtrl->GetItemText(hTreeItem) != keyCString;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
					if(pTreeCtrl)
						pTreeCtrl->SetItemText(hTreeItem,cstringVec[0]);
				}
			}
		}
		break;
	case IDC_TEAMLIST:
		{
			CString keyCString1,keyCString2;
			std::string keyString1,keyString2;
			for(int i = 0;i < 5;i++)
			{
				CString cstr = pListCtrl->GetItemText(nSeleted,i);
				cstringVec.push_back(cstr);
			}
			keyCString1 = cstringVec[0],keyCString2 = cstringVec[4];
			keyString1 = CT2A(keyCString1),keyString2 = CT2A(keyCString2);
			std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(keyString1 + " " +keyString2);
			if(teamIter == teamNameMap.end())
			{
				MessageBox(_T("��⵽�����ļ���δ��������,Ϊ�˻�ø��õ�����,�뵽�˵����������������Ctrl + F��ݼ�,�����޸���ȡ��"),_T("NOTICE"));
				return;
			}
			TeamNode *pTeamNode = teamIter->second;
			CTeamDlg cteamDlg(this);
			cteamDlg.isEdit = 1;
			cteamDlg.cstringVec.clear();
			for(auto &cstr : cstringVec)
				cteamDlg.cstringVec.push_back(cstr);
			teamNameMap.erase(teamIter);
			if(IDOK == cteamDlg.DoModal())
			{
				this->cstringVec = cteamDlg.cstringVec;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
				int nSel = pListCtrl->GetSelectionMark();
				std::string strTeamName = CT2A(cstringVec[0]);
				std::string strInstiName = CT2A(cstringVec[4]);
				std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(strTeamName + " " + strInstiName);
				std::map<std::string,InstituteNode *>::iterator instiIter = instiNameMap.find(strInstiName);
				if(teamIter != teamNameMap.end())
				{
					MessageBox(_T("��⵽���Ŷ��Ѵ���,�޷�����!"),_T("NOTICE"));
					teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(keyString1 + " " + keyString2,pTeamNode));
					return;
				}
				if(instiIter == instiNameMap.end())
				{
					MessageBox(_T("�޷��ҵ����޸ĺ��Ժϵ�����Ӧ��Ժϵ��Ϣ,�޸Ĳ������ṩ�ڴ濪�ٵĹ���!"),_T("NOTICE"));
					teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(keyString1 + " " + keyString2,pTeamNode));
					return;
				}
				pListCtrl->SetItemText(nSel,0,cstringVec[0]);
				pListCtrl->SetItemText(nSel,1,cstringVec[1]);
				pListCtrl->SetItemText(nSel,2,cstringVec[2]);
				pListCtrl->SetItemText(nSel,3,cstringVec[3]);
				pListCtrl->SetItemText(nSel,4,cstringVec[4]);
				//�ı��Ŷӽڵ����Ϣ
				wcscpy_s(pTeamNode->team.name,cstringVec[0]);
				wcscpy_s(pTeamNode->team.manager,cstringVec[1]);
				pTeamNode->team.teacherNum = _wtoi(cstringVec[2]);
				pTeamNode->team.postGraduaNum = _wtoi(cstringVec[3]);
				wcscpy_s(pTeamNode->team.instituteName,cstringVec[4]);
				teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(strTeamName + " " + strInstiName,pTeamNode));
				//���ѧԺ������ؼ��ַ����ı䣬��ô����Ӧ����
				if((keyCString1 + _T(" ") + keyCString2) != (cstringVec[0] + _T(" ") + cstringVec[4]))
				{
					if(keyCString1 != cstringVec[0] && keyCString2 == cstringVec[4])
					{
						//�������޸ĵ�ѧԺ������
						//�ı���Ŀ�б��е�����
						pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
						int itemNum = pListCtrl->GetItemCount();
						for(int i = 0;i < itemNum;i++)
						{
							if(keyCString1 == pListCtrl->GetItemText(i,5) && keyCString2 == pListCtrl->GetItemText(i,6))
							{
								CString itemNumCstr = pListCtrl->GetItemText(i,0);
								std::string itemNumStr = CT2A(itemNumCstr);
								std::map<std::string,programItemNode *>::iterator itemIter = itemNumMap.find(itemNumStr);
								programItemNode *pItemNode = itemIter->second;
								wcscpy_s(pItemNode->item.teamName,cstringVec[0]);
								pListCtrl->SetItemText(i,5,cstringVec[0]);
							}
						}
						//��
						CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
						HTREEITEM hTreeItem;
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCString2;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCString1;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						if(hTreeItem)
							pTreeCtrl->SetItemText(hTreeItem,cstringVec[0]);
					}
					if(keyCString2 != cstringVec[4])
					{
						//Ժϵ�������ı�
						//�ı���Ŀ�б������
						pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
						int itemNum = pListCtrl->GetItemCount();
						for(int i = 0;i < itemNum;i++)
						{
							if(keyCString1 == pListCtrl->GetItemText(i,5) && keyCString2 == pListCtrl->GetItemText(i,6))
							{
								CString itemNumCstr = pListCtrl->GetItemText(i,0);
								std::string itemNumStr = CT2A(itemNumCstr);
								std::map<std::string,programItemNode *>::iterator itemIter = itemNumMap.find(itemNumStr);
								programItemNode *pItemNode = itemIter->second;
								wcscpy_s(pItemNode->item.teamName,cstringVec[0]);
								wcscpy_s(pItemNode->item.instiName,cstringVec[4]);
								pListCtrl->SetItemText(i,5,cstringVec[0]);
								pListCtrl->SetItemText(i,6,cstringVec[4]);
							}
						}
						//�ı����Ľṹ������Ľṹ
						CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
						HTREEITEM originTreeItem,destTreeItem;
						for(originTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);originTreeItem && pTreeCtrl->GetItemText(originTreeItem) != keyCString2;
							originTreeItem = pTreeCtrl->GetNextSiblingItem(originTreeItem));
						for(originTreeItem = pTreeCtrl->GetChildItem(originTreeItem);originTreeItem && pTreeCtrl->GetItemText(originTreeItem) != keyCString1;
							originTreeItem = pTreeCtrl->GetNextSiblingItem(originTreeItem));
						pTreeCtrl->SetItemText(originTreeItem,cstringVec[0]);
						for(destTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);destTreeItem && pTreeCtrl->GetItemText(destTreeItem) != cstringVec[4];
							destTreeItem = pTreeCtrl->GetNextSiblingItem(destTreeItem));
						moveTree(originTreeItem,destTreeItem,pTreeCtrl);
						pTreeCtrl->DeleteItem(originTreeItem);
						//����ṹ�ı�
						std::map<std::string,InstituteNode *>::iterator OrgInstiIter = instiNameMap.find(keyString2);
						InstituteNode *pInstiNode = OrgInstiIter->second;
						if(pTeamNode->nextNode && pTeamNode->prevNode)
						{
							pTeamNode->prevNode->nextNode = pTeamNode->nextNode;
							pTeamNode->nextNode->prevNode = pTeamNode->prevNode;
						}else if(pTeamNode->nextNode)
						{
							pTeamNode->nextNode->prevNode = NULL;
							pInstiNode->tLL->head = pTeamNode->nextNode;
						}else if(pTeamNode->prevNode)
						{
							pTeamNode->prevNode->nextNode = NULL;
							pInstiNode->tLL->tail = pTeamNode->prevNode;
						}else
						{
							pInstiNode->tLL->head = NULL;
							pInstiNode->tLL->tail = NULL;
						}
						insertTeam2tLL((instiIter->second)->tLL,pTeamNode);
					}
				}
			}
		}
		break;
	case IDC_ITEMLIST:
		{
			CString keyCstring,keyCstrTeam,keyCstrInsti;
			std::string keyString,keyStrTeam,keyStrInsti;
			for(int i = 0;i < 7;i++)
			{
				CString cstr = pListCtrl->GetItemText(nSeleted,i);
				cstringVec.push_back(cstr);
			}
			keyCstring = cstringVec[0],keyCstrTeam = cstringVec[5],keyCstrInsti = cstringVec[6];
			keyString = CT2A(keyCstring),keyStrTeam = CT2A(cstringVec[5]),keyStrInsti = CT2A(cstringVec[6]);
			std::map<std::string,programItemNode *>::iterator proIter = itemNumMap.find(keyString);
			if(proIter == itemNumMap.end())
			{
				MessageBox(_T("��⵽�����ļ���δ��������,Ϊ�˻�ø��õ�����,�뵽�˵����������������Ctrl + F��ݼ�,�����޸���ȡ��"),_T("NOTICE"));
				return;
			}
			programItemNode *pProItemNode = proIter->second;
			CProgramDlg cProDlg(this);
			cProDlg.isEdit = 1;
			cProDlg.cstringVec.clear();
			for(auto &cstr : cstringVec)
				cProDlg.cstringVec.push_back(cstr);
			itemNumMap.erase(proIter);
			if(IDOK == cProDlg.DoModal())
			{
				this->cstringVec = cProDlg.cstringVec;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
				int nSel = pListCtrl->GetSelectionMark();
				std::string strItemNum = CT2A(cstringVec[0]),strItemTeam = CT2A(cstringVec[5]),strItemInsti = CT2A(cstringVec[6]);
				std::map<std::string,programItemNode *>::iterator newItemIter = itemNumMap.find(strItemNum);
				std::map<std::string,TeamNode *>::iterator teamIter = teamNameMap.find(strItemTeam + " " + strItemInsti);
				if(newItemIter != itemNumMap.end())
				{
					MessageBox(_T("��⵽����Ŀ�Ѵ���,�޷�����!"),_T("NOTICE"));
					itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(keyString,pProItemNode));
					return;
				}
				if(teamIter == teamNameMap.end())
				{
					MessageBox(_T("�޷��ҵ����޸ĺ���Ŷ������Ӧ���Ŷ���Ϣ,�޸Ĳ������ṩ�ڴ濪�ٵĹ���!"),_T("NOTICE"));
					itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(keyString,pProItemNode));
					return;
				}
				pListCtrl->SetItemText(nSel,0,cstringVec[0]);
				pListCtrl->SetItemText(nSel,1,cstringVec[1]);
				pListCtrl->SetItemText(nSel,2,cstringVec[2]);
				pListCtrl->SetItemText(nSel,3,cstringVec[3]);
				pListCtrl->SetItemText(nSel,4,cstringVec[4]);
				pListCtrl->SetItemText(nSel,5,cstringVec[5]);
				pListCtrl->SetItemText(nSel,6,cstringVec[6]);
				//�ı���Ŀ�ڵ����Ϣ
				wcscpy_s(pProItemNode->item.number,cstringVec[0]);
				pProItemNode->item.typePro = cstringVec[1][0];
				wcscpy_s(pProItemNode->item.startTime,cstringVec[2]);
				pProItemNode->item.cost = (float)_wtof(cstringVec[3]);
				wcscpy_s(pProItemNode->item.manager,cstringVec[4]);
				wcscpy_s(pProItemNode->item.teamName,cstringVec[5]);
				wcscpy_s(pProItemNode->item.instiName,cstringVec[6]);
				itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(strItemNum,pProItemNode));
				//����ؼ��ַ��������ı�,������Ӧ�Ĵ���
				CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
				HTREEITEM hTreeItem;
				for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstrInsti;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstrTeam;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstring;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				pTreeCtrl->SetItemText(hTreeItem,cstringVec[0]);
				if(((keyCstrTeam + _T(" ") + keyCstrInsti) != (cstringVec[5] + _T(" ") + cstringVec[6])))
				{
					//����ѧԺ�����ı�
					//�ı����ؼ����ڴ�ṹ
					HTREEITEM tempItem;
					for(tempItem = pTreeCtrl->GetChildItem(TVI_ROOT);tempItem && pTreeCtrl->GetItemText(tempItem) != cstringVec[6];tempItem = pTreeCtrl->GetNextSiblingItem(tempItem));
					for(tempItem = pTreeCtrl->GetChildItem(tempItem);tempItem && pTreeCtrl->GetItemText(tempItem) != cstringVec[5];tempItem = pTreeCtrl->GetNextSiblingItem(tempItem));
					moveTree(hTreeItem,tempItem,pTreeCtrl);
					pTreeCtrl->DeleteItem(hTreeItem);
					//����ṹ
					std::map<std::string,TeamNode *>::iterator teamIter2 = teamNameMap.find(keyStrTeam + " " + keyStrInsti);
					TeamNode *pTeamNode = teamIter2->second;
					if(pProItemNode->nextNode && pProItemNode->prevNode)
					{
						pProItemNode->prevNode->nextNode = pProItemNode->nextNode;
						pProItemNode->nextNode->prevNode = pProItemNode->prevNode;
					}else if(pProItemNode->nextNode)
					{
						pProItemNode->nextNode->prevNode = NULL;
						pTeamNode->pLL->head = pProItemNode->nextNode;
					}else if(pProItemNode->prevNode)
					{
						pProItemNode->prevNode->nextNode = NULL;
						pTeamNode->pLL->tail = pProItemNode->prevNode;
					}else
					{
						pTeamNode->pLL->head = NULL;
						pTeamNode->pLL->tail = NULL;
					}
					insertProg2pLL((teamIter->second)->pLL,pProItemNode);
				}
			}
		}
		break;
	default:
		break;
	}
}


void CSciPgMDlg::moveTree(HTREEITEM hSource,HTREEITEM hDest,CTreeCtrl *pTreeCtrl)
{
	if(!hSource)
		return;
	HTREEITEM hNewDest;
	hNewDest = pTreeCtrl->InsertItem(pTreeCtrl->GetItemText(hSource),hDest);
	for(HTREEITEM hTreeItem = pTreeCtrl->GetChildItem(hSource);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem))
		moveTree(hTreeItem,hNewDest,pTreeCtrl);
}

//��������ƶ��¼����浱ǰѡ�е��б�ؼ�,������CSciPgMDlg�����Ӧ�����з���������������
void CSciPgMDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd *pWnd = GetFocus();
	CString cstr("ѡ��");
	UINT nId;
	if(pWnd)
		nId = pWnd->GetDlgCtrlID();
	else
		return;
	if(nId == IDC_INSTILIST || nId == IDC_TEAMLIST || nId == IDC_ITEMLIST)
	{
		this->FocusedListID = nId;
		if(nId == IDC_ITEMLIST)
			SetDlgItemText(IDC_NOTICE,cstr + " ������Ŀ��Ϣ��");
		else if(nId == IDC_INSTILIST)
			SetDlgItemText(IDC_NOTICE,cstr + " ѧԺ��Ϣ��");
		else if(nId == IDC_TEAMLIST)
			SetDlgItemText(IDC_NOTICE,cstr + " �����Ŷ���Ϣ��");
	}
}

//�˵���->���ļ�ѡ��
void CSciPgMDlg::OnOpenFile()
{
	CFileDlg cfileDlg(this);
	if(IDOK == cfileDlg.DoModal())
	{
		CString filePath = cfileDlg.filePath,temp;
		char tableFlag;int itemNum;
		CFile file;
		file.Open(filePath,CFile::modeRead);
		if(file.m_hFile == CFile::hFileNull)
		{
			MessageBox(_T("�ļ�ռ�û򲻿ɷ���"),_T("EXCEPTION"),MB_ICONERROR);
			return;
		}
		file.Read(&tableFlag,sizeof(tableFlag));
		file.Read(&itemNum,sizeof(int));
		CProgressCtrl *pProgressCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
		pProgressCtrl->SetRange(0,(short)itemNum);
		switch (tableFlag)
		{
		case '1':
			{
				Institute inst;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
				if(pListCtrl->GetItemCount())
				{
					int nRes = MessageBox(_T("�򿪵��ļ��Ḳ�ǵ�ǰѧԺ��Ϣ��,�Ƿ񱣴浱ǰ���"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
					if(nRes == IDOK)
						OnSaveInstituteTable();
				}
				pListCtrl->DeleteAllItems();
				while(file.Read(&inst,sizeof(inst)) >= sizeof(inst))
				{
					int ctn = pListCtrl->GetItemCount();
					temp.Format(_T("%s"),inst.name);
					pListCtrl->InsertItem(ctn,temp);
					temp.Format(_T("%s"),inst.manager);
					pListCtrl->SetItemText(ctn,1,temp);
					temp.Format(_T("%s"),inst.tel);
					pListCtrl->SetItemText(ctn,2,temp);
					pProgressCtrl->OffsetPos(1);
				}
			}
			OnFormLinkedList();
			break;
		case '2':
			{
				Team team;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
				if(pListCtrl->GetItemCount())
				{
					int nRes = MessageBox(_T("�򿪵��ļ��Ḳ�ǵ�ǰ�Ŷ���Ϣ��,�Ƿ񱣴浱ǰ���"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
					if(nRes == IDOK)
						OnSaveTeamTable();
				}
				pListCtrl->DeleteAllItems();
				while(file.Read(&team,sizeof(team)) >= sizeof(team))
				{
					int ctn = pListCtrl->GetItemCount();
					temp.Format(_T("%s"),team.name);
					pListCtrl->InsertItem(ctn,temp);
					temp.Format(_T("%s"),team.manager);
					pListCtrl->SetItemText(ctn,1,temp);
					temp.Format(_T("%d"),team.teacherNum);
					pListCtrl->SetItemText(ctn,2,temp);
					temp.Format(_T("%d"),team.postGraduaNum);
					pListCtrl->SetItemText(ctn,3,temp);
					temp.Format(_T("%s"),team.instituteName);
					pListCtrl->SetItemText(ctn,4,temp);
					pProgressCtrl->OffsetPos(1);
				}
			}
			OnFormLinkedList();
			break;
		case '3':
			{
				programItem prog;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
				if(pListCtrl->GetItemCount())
				{
					int nRes = MessageBox(_T("�򿪵��ļ��Ḳ�ǵ�ǰ������Ŀ��Ϣ��,�Ƿ񱣴浱ǰ���"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
					if(nRes == IDOK)
						OnSaveProgramTable();
				}
				pListCtrl->DeleteAllItems();
				while(file.Read(&prog,sizeof(prog)) >= sizeof(prog))
				{
					int ctn = pListCtrl->GetItemCount();
					temp.Format(_T("%s"),prog.number);
					pListCtrl->InsertItem(ctn,temp);
					temp.Format(_T("%c"),prog.typePro);
					pListCtrl->SetItemText(ctn,1,temp);
					temp.Format(_T("%s"),prog.startTime);
					pListCtrl->SetItemText(ctn,2,temp);
					temp.Format(_T("%0.4lf"),prog.cost);
					pListCtrl->SetItemText(ctn,3,temp);
					temp.Format(_T("%s"),prog.manager);
					pListCtrl->SetItemText(ctn,4,temp);
					temp.Format(_T("%s"),prog.teamName);
					pListCtrl->SetItemText(ctn,5,temp);
					temp.Format(_T("%s"),prog.instiName);
					pListCtrl->SetItemText(ctn,6,temp);
					pProgressCtrl->OffsetPos(1);
				}
			}
			OnFormLinkedList();
			break;
		default:
			break;
		}
		file.Close();
		MessageBox(_T("�ļ�����ɹ�"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
		pProgressCtrl->SetPos(0);
	}
}

//�˵���->����ѧԺ�ļ�ѡ��
void CSciPgMDlg::OnSaveInstituteTable()
{
	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle = _T("InstituteTable Save Dlg");
	fileDlg.m_ofn.lpstrFilter = _T("Binary Data Files(*.dat)\0*.dat\0All Files()*.*\0*.*\0\0");
	fileDlg.m_ofn.lpstrDefExt = _T("dat");
	if(IDOK == fileDlg.DoModal())
	{
		CString cstr = fileDlg.GetPathName();
		CFile file;
		file.Open(cstr,CFile::modeCreate | CFile::modeWrite);
		if(file.m_hFile == CFile::hFileNull)
		{
			MessageBox(_T("�ļ�ռ�û򲻿ɷ���,����ʧ��"),_T("EXCEPTION"),MB_ICONERROR);
			return;
		}
		const char c = '1';
		file.Write(&c,sizeof(char));
		CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
		int itemNum = pListCtrl->GetItemCount();
		file.Write(&itemNum,sizeof(int));
		CProgressCtrl *pProgressCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
		pProgressCtrl->SetRange(0,(short)itemNum);
		for(int i = 0;i < itemNum;i++)
		{
			Institute inst;
			cstr = pListCtrl->GetItemText(i,0);
			wcscpy_s(inst.name,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,1);
			wcscpy_s(inst.manager,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,2);
			wcscpy_s(inst.tel,cstr.GetBuffer(cstr.GetLength()));
			file.Write(&inst,sizeof(inst));
			pProgressCtrl->OffsetPos(1);
		}
		file.Close();
		MessageBox(_T("Institude Table Saved!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
		pProgressCtrl->SetPos(0);
	}
}

//�˵���->��������Ŷ��ļ�ѡ��
void CSciPgMDlg::OnSaveTeamTable()
{
	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle = _T("TeamTable Save Dlg");
	fileDlg.m_ofn.lpstrFilter = _T("Binary Data Files(*.dat)\0*.dat\0All Files()*.*\0*.*\0\0");
	fileDlg.m_ofn.lpstrDefExt = _T("dat");
	if(IDOK == fileDlg.DoModal())
	{
		CString cstr = fileDlg.GetPathName();
		CFile file;
		file.Open(cstr,CFile::modeCreate | CFile::modeWrite);
		if(file.m_hFile == CFile::hFileNull)
		{
			MessageBox(_T("�ļ�ռ�û򲻿ɷ��ʣ�,����ʧ��"),_T("EXCEPTION"),MB_ICONERROR);
			return;
		}
		const char c = '2';
		file.Write(&c,sizeof(char));
		CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
		int itemNum = pListCtrl->GetItemCount();
		file.Write(&itemNum,sizeof(int));
		CProgressCtrl *pProgressCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
		pProgressCtrl->SetRange(0,(short)itemNum);
		for(int i = 0;i < itemNum;i++)
		{
			Team team;
			cstr = pListCtrl->GetItemText(i,0);
			wcscpy_s(team.name,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,1);
			wcscpy_s(team.manager,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,2);
			team.teacherNum = _wtoi(cstr);
			cstr = pListCtrl->GetItemText(i,3);
			team.postGraduaNum = _wtoi(cstr);
			cstr = pListCtrl->GetItemText(i,4);
			wcscpy_s(team.instituteName,cstr.GetBuffer(cstr.GetLength()));
			file.Write(&team,sizeof(team));
			pProgressCtrl->OffsetPos(1);
		}
		file.Close();
		MessageBox(_T("Team Table Saved!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
		pProgressCtrl->SetPos(0);
	}
}

//�˵���->���������Ŀ�ļ�ѡ��
void CSciPgMDlg::OnSaveProgramTable()
{
	CFileDialog fileDlg(FALSE);
	fileDlg.m_ofn.lpstrTitle = _T("ProgramTable Save Dlg");
	fileDlg.m_ofn.lpstrFilter = _T("Binary Data Files(*.dat)\0*.dat\0All Files()*.*\0*.*\0\0");
	fileDlg.m_ofn.lpstrDefExt = _T("dat");	
	if(IDOK == fileDlg.DoModal())
	{
		CString cstr = fileDlg.GetPathName();
		CFile file;
		file.Open(cstr,CFile::modeCreate | CFile::modeWrite);
		if(file.m_hFile == CFile::hFileNull)
		{
			MessageBox(_T("�ļ�ռ�û򲻿ɷ���,����ʧ��"),_T("EXCEPTION"),MB_ICONERROR);
			return;
		}
		const char c = '3';
		file.Write(&c,sizeof(char));
		CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
		int itemNum = pListCtrl->GetItemCount();
		file.Write(&itemNum,sizeof(int));
		CProgressCtrl *pProgressCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS);
		pProgressCtrl->SetRange(0,(short)itemNum);
		for(int i = 0;i < itemNum;i++)
		{
			programItem program;
			cstr = pListCtrl->GetItemText(i,0);
			wcscpy_s(program.number,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,1);
			program.typePro = cstr[0];
			cstr = pListCtrl->GetItemText(i,2);
			wcscpy_s(program.startTime,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,3);
			program.cost = (float)_wtof(cstr);
			cstr = pListCtrl->GetItemText(i,4);
			wcscpy_s(program.manager,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,5);
			wcscpy_s(program.teamName,cstr.GetBuffer(cstr.GetLength()));
			cstr = pListCtrl->GetItemText(i,6);
			wcscpy_s(program.instiName,cstr.GetBuffer(cstr.GetLength()));
			file.Write(&program,sizeof(program));
			pProgressCtrl->OffsetPos(1);
		}
		file.Close();
		MessageBox(_T("Program Item Table Saved"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
		pProgressCtrl->SetPos(0);
	}
}

//�˵���->����ȫ���ļ�ѡ��
void CSciPgMDlg::OnSaveAll()
{
	OnSaveInstituteTable();
	OnSaveTeamTable();
	OnSaveProgramTable();
}

//�˵���->�ļ�����ѡ��
void CSciPgMDlg::OnTableReset()
{
	CTableResetDlg tableResetDlg(this);
	if(IDOK == tableResetDlg.DoModal())
	{
		int nresponse = MessageBox(_T("�Ƿ���Ҫ���浱ǰ����������?"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
		if(IDOK == nresponse)
			OnSaveAll();
		CListCtrl *pListCtrl;
		pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
		pListCtrl->DeleteAllItems();
		pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
		pListCtrl->DeleteAllItems();
		pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
		pListCtrl->DeleteAllItems();
		OnClearLinkedList();
	}
}

//�˵���->�ļ��˳�ѡ��
void CSciPgMDlg::OnExit()
{
	int nRes = MessageBox(_T("�˳�ǰ�Ƿ񱣴��ļ���"),_T("NOTICE"),MB_ICONQUESTION | MB_OKCANCEL);
	if(nRes == IDOK)
		OnSaveAll();
	OnClearLinkedList();
	EndDialog(IDCANCEL);
}

//�����麯��,ʵ�ֿ�ݼ�
BOOL CSciPgMDlg::PreTranslateMessage(MSG* pMsg)
{
	if(TranslateAccelerator(m_hWnd,hAccel,pMsg))  
		return true;    
	return CDialogEx::PreTranslateMessage(pMsg);
}

//�رհ�ť��Ӧ
void CSciPgMDlg::OnCancel()
{
	OnExit();
}

//չ�����οؼ������нڵ�
void CSciPgMDlg::ExpandAllNode(HTREEITEM hItem, CTreeCtrl *treeShow)
{
	HTREEITEM hChild = treeShow->GetChildItem(hItem);
	while(hChild)
	{
		treeShow->Expand(hItem, TVE_EXPAND);
		ExpandAllNode(hChild, treeShow);
		hChild = treeShow->GetNextSiblingItem(hChild);
	}
}

//���ؼ�չʾ
void CSciPgMDlg::showOnTreeCtrl()
{
	CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
	pTreeCtrl->DeleteAllItems();
	InstituteNode *pInstiTrav = iLL.head;
	HTREEITEM hItem = NULL,hSubItem = NULL,hSubSubItem = NULL;
	for(;pInstiTrav;pInstiTrav = pInstiTrav->nextNode)
	{
		if(pInstiTrav == iLL.head)
			hItem = pTreeCtrl->InsertItem(pInstiTrav->institude.name,TVI_ROOT);
		else
			hItem = pTreeCtrl->InsertItem(pInstiTrav->institude.name,TVI_ROOT,hItem);
		for(TeamNode *pTeamTrav = pInstiTrav->tLL->head;pTeamTrav;pTeamTrav = pTeamTrav->nextNode)
		{
			if(pTeamTrav == pInstiTrav->tLL->head)
				hSubItem = pTreeCtrl->InsertItem(pTeamTrav->team.name,hItem);
			else
				hSubItem = pTreeCtrl->InsertItem(pTeamTrav->team.name,hItem,hSubItem);
			for(programItemNode *pPItemTrav = pTeamTrav->pLL->head;pPItemTrav;pPItemTrav = pPItemTrav->nextNode)
			{
				if(pPItemTrav == pTeamTrav->pLL->head)
					hSubSubItem = pTreeCtrl->InsertItem(pPItemTrav->item.number,hSubItem);
				else
					hSubSubItem = pTreeCtrl->InsertItem(pPItemTrav->item.number,hSubItem,hSubSubItem);
			}
		}
	}
	ExpandAllNode(TVI_ROOT,pTreeCtrl);
	return;
}



//��������
void CSciPgMDlg::OnFormLinkedList()
{
	OnClearLinkedList();
	OnFuncUse();
	iLL.head = NULL;iLL.tail = NULL;
	CListCtrl *pListCtrl;
	pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	int itemNum = pListCtrl->GetItemCount();
	CString cstr;
	std::map<std::string,InstituteNode *>::iterator instiMapIter;
	std::map<std::string,TeamNode *>::iterator teamMapIter;
	std::map<std::string,programItemNode *>::iterator itemMapIter;
	//ת��ѧԺ���Ϊ����Ҫ���ʮ������
	for(int i = 0;i < itemNum;i++)
	{
		std::string strKey = CT2A(pListCtrl->GetItemText(i,0));
		if((instiMapIter = instiNameMap.find(strKey)) != instiNameMap.end())
			continue;
		InstituteNode *inst = (InstituteNode *)malloc(sizeof(InstituteNode));
		//��ѧԺ����ڵ����
		inst->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
		inst->tLL->head = NULL;inst->tLL->tail = NULL;
		
		cstr = pListCtrl->GetItemText(i,0);
		wcscpy_s(inst->institude.name, cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,1);
		wcscpy_s(inst->institude.manager,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,2);
		wcscpy_s(inst->institude.tel,cstr.GetBuffer(cstr.GetLength()));
		//Ϊ���Ż���ѯ�ٶ�,ʹ��STL����map
		instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(strKey,inst));
		insertInsti2iLL(inst);
	}
	//ת���Ŷӱ��
	pListCtrl = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	itemNum = pListCtrl->GetItemCount();
	for(int i = 0;i < itemNum;i++)
	{
		std::string strKey = CT2A(pListCtrl->GetItemText(i,0));
		std::string findStr = CT2A(pListCtrl->GetItemText(i,4));
		if((teamMapIter = teamNameMap.find(strKey + " " + findStr)) != teamNameMap.end())
			continue;
		TeamNode *team = (TeamNode *)malloc(sizeof(TeamNode));
		team->pLL = (programLinkedList *)malloc(sizeof(programLinkedList));
		team->pLL->head = NULL;team->pLL->tail = NULL;

		cstr = pListCtrl->GetItemText(i,0);
		wcscpy_s(team->team.name,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,1);
		wcscpy_s(team->team.manager,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,2);
		team->team.teacherNum = _wtoi(cstr);
		cstr = pListCtrl->GetItemText(i,3);
		team->team.postGraduaNum = _wtoi(cstr);
		cstr = pListCtrl->GetItemText(i,4);
		wcscpy_s(team->team.instituteName,cstr.GetBuffer(cstr.GetLength()));
		teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(strKey + " " + findStr,team));
		std::map<std::string,InstituteNode *>::iterator tempiter;
		if((tempiter = instiNameMap.find(findStr)) != instiNameMap.end())
		{
			//ѧԺ���Ѵ��ڵ�����������µ��Ŷ���
			InstituteNode *pinstNode = tempiter->second;
			insertTeam2tLL(pinstNode->tLL,team);
		}else
		{
			//ѧԺ��Ҳ�����ڴ����µ�ѧԺ�ڵ�
			InstituteNode *pinstNode = (InstituteNode *)malloc(sizeof(InstituteNode));
			pinstNode->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
			pinstNode->tLL->head = NULL;pinstNode->tLL->tail = NULL;
			wcscpy_s(pinstNode->institude.name,cstr);
			wcscpy_s(pinstNode->institude.manager,_T(""));
			wcscpy_s(pinstNode->institude.tel,_T(""));
			insertInsti2iLL(pinstNode);
			insertTeam2tLL(pinstNode->tLL,team);
			instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(findStr,pinstNode));
		}
	}
	//ת��������Ŀ���
	pListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	itemNum = pListCtrl->GetItemCount();
	for(int i = 0;i < itemNum;i++)
	{
		std::string str = CT2A(pListCtrl->GetItemText(i,0));
		if((itemMapIter = itemNumMap.find(str)) != itemNumMap.end())
			continue;
		programItemNode *pItemNode = (programItemNode *)malloc(sizeof(programItemNode));
		
		cstr = pListCtrl->GetItemText(i,0);
		wcscpy_s(pItemNode->item.number,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,1);
		pItemNode->item.typePro = cstr[0];
		cstr = pListCtrl->GetItemText(i,2);
		wcscpy_s(pItemNode->item.startTime,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,3);
		pItemNode->item.cost = (float)_wtof(cstr);
		cstr = pListCtrl->GetItemText(i,4);
		wcscpy_s(pItemNode->item.manager,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,5);
		wcscpy_s(pItemNode->item.teamName,cstr.GetBuffer(cstr.GetLength()));
		std::string strKey = CT2A(cstr);
		cstr = pListCtrl->GetItemText(i,6);
		std::string findStr = CT2A(cstr);
		wcscpy_s(pItemNode->item.instiName,cstr.GetBuffer(cstr.GetLength()));
		itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(str,pItemNode));
		std::map<std::string,TeamNode *>::iterator tempIter;
		if((tempIter = teamNameMap.find(strKey + " " + findStr)) != teamNameMap.end())
		{
			//�ҵ����Ѵ��ڵ��Ŷ���Ϣ
			TeamNode *pteamNode = tempIter->second;
			insertProg2pLL(pteamNode->pLL,pItemNode);
		}else
		{
			InstituteNode *pinstNode;
			//δ�ҵ��Ѵ��ڵ��Ŷ���Ϣ
			if((instiMapIter = instiNameMap.find(findStr)) != instiNameMap.end())
			{
				pinstNode = instiMapIter->second;
				//Ժϵ���Ѵ���:�����µ��Ŷӽڵ㲢�����ŶӼ���map����,�ٲ�����Ŀ�ڵ�
			}else
			{
				//Ժϵ�������ڣ������µ�Ժϵ�ڵ���Ŷӽڵ㲢����Щ��������map���棬�ٲ�����Ŀ�ڵ�
				pinstNode = (InstituteNode *)malloc(sizeof(InstituteNode));
				pinstNode->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
				pinstNode->tLL->head = NULL;pinstNode->tLL->tail = NULL;
				wcscpy_s(pinstNode->institude.name,pListCtrl->GetItemText(i,6));
				wcscpy_s(pinstNode->institude.manager,_T(""));
				wcscpy_s(pinstNode->institude.tel,_T(""));
				insertInsti2iLL(pinstNode);
				instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(findStr,pinstNode));
			}
			TeamNode *pTeamNode = (TeamNode *)malloc(sizeof(TeamNode));
			pTeamNode->pLL = (programLinkedList *)malloc(sizeof(programLinkedList));
			pTeamNode->pLL->head = NULL; pTeamNode->pLL->tail = NULL;
			wcscpy_s(pTeamNode->team.name,pListCtrl->GetItemText(i,5));
			wcscpy_s(pTeamNode->team.manager,_T(""));
			pTeamNode->team.teacherNum = -1;
			pTeamNode->team.postGraduaNum = -1;
			wcscpy_s(pTeamNode->team.instituteName,_T(""));
			insertTeam2tLL(pinstNode->tLL,pTeamNode);
			teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(strKey + " " + findStr,pTeamNode));

			insertProg2pLL(pTeamNode->pLL,pItemNode);
		}
	}
	showOnTreeCtrl();
}

//�����ʼ��
void CSciPgMDlg::OnClearLinkedList()
{
	instiNameMap.clear();teamNameMap.clear();itemNumMap.clear();
	if(!iLL.head)
		return;
	InstituteNode *pinstNode,*fastInstNode;
	for(pinstNode = iLL.head,fastInstNode = pinstNode->nextNode;fastInstNode;
		pinstNode = fastInstNode,fastInstNode = pinstNode->nextNode)
	{
		if(pinstNode->tLL->head)
		{
			TeamNode *pTeamNode,*fastTeamNode;
			for(pTeamNode = pinstNode->tLL->head,fastTeamNode = pTeamNode->nextNode;fastTeamNode;
				pTeamNode = fastTeamNode,fastTeamNode = pTeamNode->nextNode)
			{
				if(pTeamNode->pLL->head)
				{
					programItemNode *ppItemNode,*fastItemNode;
					for(ppItemNode = pTeamNode->pLL->head,fastItemNode = ppItemNode->nextNode;fastItemNode;
						ppItemNode = fastItemNode,fastItemNode = ppItemNode->nextNode)
						free(ppItemNode);
					free(ppItemNode);
				}
				free(pTeamNode->pLL);
				free(pTeamNode);
			}
			if(pTeamNode->pLL->head)
			{
				programItemNode *ppItemNode,*fastItemNode;
				for(ppItemNode = pTeamNode->pLL->head,fastItemNode = ppItemNode->nextNode;fastItemNode;
					ppItemNode = fastItemNode,fastItemNode = ppItemNode->nextNode)
					free(ppItemNode);
				free(ppItemNode);
			}
			free(pTeamNode->pLL);
			free(pTeamNode);
		}
		free(pinstNode->tLL);
		free(pinstNode);
	}
	if(pinstNode->tLL->head)
	{
		TeamNode *pTeamNode,*fastTeamNode;
		for(pTeamNode = pinstNode->tLL->head,fastTeamNode = pTeamNode->nextNode;fastTeamNode;
			pTeamNode = fastTeamNode,fastTeamNode = pTeamNode->nextNode)
		{
			if(pTeamNode->pLL->head)
			{
				programItemNode *ppItemNode,*fastItemNode;
				for(ppItemNode = pTeamNode->pLL->head,fastItemNode = ppItemNode->nextNode;fastItemNode;
					ppItemNode = fastItemNode,fastItemNode = ppItemNode->nextNode)
					free(ppItemNode);
				free(ppItemNode);
			}
			free(pTeamNode->pLL);
			free(pTeamNode);
		}
		if(pTeamNode->pLL->head)
		{
			programItemNode *ppItemNode,*fastItemNode;
			for(ppItemNode = pTeamNode->pLL->head,fastItemNode = ppItemNode->nextNode;fastItemNode;
				ppItemNode = fastItemNode,fastItemNode = ppItemNode->nextNode)
				free(ppItemNode);
			free(ppItemNode);
		}
		free(pTeamNode->pLL);
		free(pTeamNode);
	}
	free(pinstNode->tLL);
	free(pinstNode);
	iLL.head = NULL;iLL.tail = NULL;
	showOnTreeCtrl();
	MessageBox(_T("�ڴ������ʼ���ɹ�"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
	return;
}


void CSciPgMDlg::OnFuncUse()
{
	GetMenu()->GetSubMenu(2)->CheckMenuRadioItem(ID_32800,ID_32801,ID_32800,MF_BYCOMMAND);
	autoSynSwitch = true;
}


void CSciPgMDlg::OnFuncUnuse()
{
	MessageBox(_T("���ڽ��ù��ܻᵼ�²���Ԥ�ϵĳ�����Ϊ,�Ѿ�������!"),_T("NOTICE"),MB_ICONINFORMATION);
	return;
}

//Debug����
void CSciPgMDlg::On32802()
{
	showOnTreeCtrl();
}

//��������ʾ�����ؼ���
void CSciPgMDlg::linkedList2ListShow()
{
	CListCtrl *pInstiList = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	CListCtrl *pTeamList = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	CListCtrl *pItemList = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pInstiList->DeleteAllItems();
	pTeamList->DeleteAllItems();
	pItemList->DeleteAllItems();
	for(InstituteNode *pInstiNode = iLL.head;pInstiNode;pInstiNode = pInstiNode->nextNode)
	{
		int instiItemCount = pInstiList->GetItemCount();
		pInstiList->InsertItem(instiItemCount,pInstiNode->institude.name);
		pInstiList->SetItemText(instiItemCount,1,pInstiNode->institude.manager);
		pInstiList->SetItemText(instiItemCount,2,pInstiNode->institude.tel);
		for(TeamNode *pTeamNode = pInstiNode->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
		{
			int teamItemCount = pTeamList->GetItemCount();
			pTeamList->InsertItem(teamItemCount,pTeamNode->team.name);
			pTeamList->SetItemText(teamItemCount,1,pTeamNode->team.manager);
			CString temp;
			temp.Format(_T("%d"),pTeamNode->team.teacherNum);
			pTeamList->SetItemText(teamItemCount,2,temp);
			temp.Format(_T("%d"),pTeamNode->team.postGraduaNum);
			pTeamList->SetItemText(teamItemCount,3,temp);
			pTeamList->SetItemText(teamItemCount,4,pTeamNode->team.instituteName);
			for(programItemNode *pItemNode = pTeamNode->pLL->head;pItemNode;pItemNode = pItemNode->nextNode)
			{
				int proItemCount = pItemList->GetItemCount();
				pItemList->InsertItem(proItemCount,pItemNode->item.number);
				CString temp2;
				temp2.Format(_T("%c"),pItemNode->item.typePro);
				pItemList->SetItemText(proItemCount,1,temp2);
				pItemList->SetItemText(proItemCount,2,pItemNode->item.startTime);
				temp2.Format(_T("%f"),pItemNode->item.cost);
				pItemList->SetItemText(proItemCount,3,temp2);
				pItemList->SetItemText(proItemCount,4,pItemNode->item.manager);
				pItemList->SetItemText(proItemCount,5,pItemNode->item.teamName);
				pItemList->SetItemText(proItemCount,6,pItemNode->item.instiName);
			}
		}
	}
	return;
}

void CSciPgMDlg::findInsti2ListShow(BOOL (*compareFunc)(InstituteNode *,const CString&),CString keyWord)
{
	CListCtrl *pInstiList = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	CListCtrl *pTeamList = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	CListCtrl *pItemList = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pInstiList->DeleteAllItems();
	pTeamList->DeleteAllItems();
	pItemList->DeleteAllItems();
	for(InstituteNode *pInstiNode = iLL.head;pInstiNode;pInstiNode = pInstiNode->nextNode)
	{
		if(compareFunc(pInstiNode,keyWord))
		{
			int instiItemCount = pInstiList->GetItemCount();
			pInstiList->InsertItem(instiItemCount,pInstiNode->institude.name);
			pInstiList->SetItemText(instiItemCount,1,pInstiNode->institude.manager);
			pInstiList->SetItemText(instiItemCount,2,pInstiNode->institude.tel);
		}
		for(TeamNode *pTeamNode = pInstiNode->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
		{
			int teamItemCount = pTeamList->GetItemCount();
			pTeamList->InsertItem(teamItemCount,pTeamNode->team.name);
			pTeamList->SetItemText(teamItemCount,1,pTeamNode->team.manager);
			CString temp;
			temp.Format(_T("%d"),pTeamNode->team.teacherNum);
			pTeamList->SetItemText(teamItemCount,2,temp);
			temp.Format(_T("%d"),pTeamNode->team.postGraduaNum);
			pTeamList->SetItemText(teamItemCount,3,temp);
			pTeamList->SetItemText(teamItemCount,4,pTeamNode->team.instituteName);
			for(programItemNode *pItemNode = pTeamNode->pLL->head;pItemNode;pItemNode = pItemNode->nextNode)
			{
				int proItemCount = pItemList->GetItemCount();
				pItemList->InsertItem(proItemCount,pItemNode->item.number);
				CString temp2;
				temp2.Format(_T("%c"),pItemNode->item.typePro);
				pItemList->SetItemText(proItemCount,1,temp2);
				pItemList->SetItemText(proItemCount,2,pItemNode->item.startTime);
				temp2.Format(_T("%f"),pItemNode->item.cost);
				pItemList->SetItemText(proItemCount,3,temp2);
				pItemList->SetItemText(proItemCount,4,pItemNode->item.manager);
				pItemList->SetItemText(proItemCount,5,pItemNode->item.teamName);
				pItemList->SetItemText(proItemCount,6,pItemNode->item.instiName);
			}
		}
	}
	return;
}

void CSciPgMDlg::findTeam2ListShow(BOOL (*compareFunc)(TeamNode *,const CString&),CString keyWord)
{
	CListCtrl *pInstiList = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	CListCtrl *pTeamList = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	CListCtrl *pItemList = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pInstiList->DeleteAllItems();
	pTeamList->DeleteAllItems();
	pItemList->DeleteAllItems();
	for(InstituteNode *pInstiNode = iLL.head;pInstiNode;pInstiNode = pInstiNode->nextNode)
	{
		int instiItemCount = pInstiList->GetItemCount();
		pInstiList->InsertItem(instiItemCount,pInstiNode->institude.name);
		pInstiList->SetItemText(instiItemCount,1,pInstiNode->institude.manager);
		pInstiList->SetItemText(instiItemCount,2,pInstiNode->institude.tel);
		for(TeamNode *pTeamNode = pInstiNode->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
		{
			if(compareFunc(pTeamNode,keyWord))
			{
				int teamItemCount = pTeamList->GetItemCount();
				pTeamList->InsertItem(teamItemCount,pTeamNode->team.name);
				pTeamList->SetItemText(teamItemCount,1,pTeamNode->team.manager);
				CString temp;
				temp.Format(_T("%d"),pTeamNode->team.teacherNum);
				pTeamList->SetItemText(teamItemCount,2,temp);
				temp.Format(_T("%d"),pTeamNode->team.postGraduaNum);
				pTeamList->SetItemText(teamItemCount,3,temp);
				pTeamList->SetItemText(teamItemCount,4,pTeamNode->team.instituteName);
			}
			for(programItemNode *pItemNode = pTeamNode->pLL->head;pItemNode;pItemNode = pItemNode->nextNode)
			{
				int proItemCount = pItemList->GetItemCount();
				pItemList->InsertItem(proItemCount,pItemNode->item.number);
				CString temp2;
				temp2.Format(_T("%c"),pItemNode->item.typePro);
				pItemList->SetItemText(proItemCount,1,temp2);
				pItemList->SetItemText(proItemCount,2,pItemNode->item.startTime);
				temp2.Format(_T("%f"),pItemNode->item.cost);
				pItemList->SetItemText(proItemCount,3,temp2);
				pItemList->SetItemText(proItemCount,4,pItemNode->item.manager);
				pItemList->SetItemText(proItemCount,5,pItemNode->item.teamName);
				pItemList->SetItemText(proItemCount,6,pItemNode->item.instiName);
			}
		}
	}
	return;
}

void CSciPgMDlg::findItem2ListShow(BOOL (*compareFunc)(programItemNode *,const CString&),CString keyWord)
{
	CListCtrl *pInstiList = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	CListCtrl *pTeamList = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	CListCtrl *pItemList = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pInstiList->DeleteAllItems();
	pTeamList->DeleteAllItems();
	pItemList->DeleteAllItems();
	for(InstituteNode *pInstiNode = iLL.head;pInstiNode;pInstiNode = pInstiNode->nextNode)
	{
		int instiItemCount = pInstiList->GetItemCount();
		pInstiList->InsertItem(instiItemCount,pInstiNode->institude.name);
		pInstiList->SetItemText(instiItemCount,1,pInstiNode->institude.manager);
		pInstiList->SetItemText(instiItemCount,2,pInstiNode->institude.tel);
		for(TeamNode *pTeamNode = pInstiNode->tLL->head;pTeamNode;pTeamNode = pTeamNode->nextNode)
		{
			int teamItemCount = pTeamList->GetItemCount();
			pTeamList->InsertItem(teamItemCount,pTeamNode->team.name);
			pTeamList->SetItemText(teamItemCount,1,pTeamNode->team.manager);
			CString temp;
			temp.Format(_T("%d"),pTeamNode->team.teacherNum);
			pTeamList->SetItemText(teamItemCount,2,temp);
			temp.Format(_T("%d"),pTeamNode->team.postGraduaNum);
			pTeamList->SetItemText(teamItemCount,3,temp);
			pTeamList->SetItemText(teamItemCount,4,pTeamNode->team.instituteName);
			for(programItemNode *pItemNode = pTeamNode->pLL->head;pItemNode;pItemNode = pItemNode->nextNode)
			{
				if(compareFunc(pItemNode,keyWord))
				{
					int proItemCount = pItemList->GetItemCount();
					pItemList->InsertItem(proItemCount,pItemNode->item.number);
					CString temp2;
					temp2.Format(_T("%c"),pItemNode->item.typePro);
					pItemList->SetItemText(proItemCount,1,temp2);
					pItemList->SetItemText(proItemCount,2,pItemNode->item.startTime);
					temp2.Format(_T("%f"),pItemNode->item.cost);
					pItemList->SetItemText(proItemCount,3,temp2);
					pItemList->SetItemText(proItemCount,4,pItemNode->item.manager);
					pItemList->SetItemText(proItemCount,5,pItemNode->item.teamName);
					pItemList->SetItemText(proItemCount,6,pItemNode->item.instiName);
				}
			}
		}
	}
	return;
}

void CSciPgMDlg::OnFindInfo()
{
	CFindInfoDlg *findDlg = new CFindInfoDlg;
	findDlg->Create(IDD_FINDDIALOG,NULL);
	findDlg->pSciPgmDlg = this;
	findDlg->ShowWindow(SW_SHOW);
}

//Override�Է�ֹ�س����ø����OnOK���˳�
void CSciPgMDlg::OnOK()
{
	return;
}

void CSciPgMDlg::OnStatistic()
{
	CStatisticDlg CstatisDlg(this);
	CstatisDlg.pSciDlg = this;
	CstatisDlg.DoModal();
}


void CSciPgMDlg::OnIntro()
{
	CFAQDlg faqDlg(this);
	faqDlg.DoModal();
}


void CSciPgMDlg::OnAbout()
{
	CAboutDlg aboutDlg(this);
	aboutDlg.DoModal();
}
