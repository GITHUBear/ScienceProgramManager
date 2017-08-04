
// SciPgMDlg.cpp : 实现文件
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


// CSciPgMDlg 对话框



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


// CSciPgMDlg 消息处理程序

BOOL CSciPgMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

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

	//使用列表控件句柄初始化列表
	//初始化列表1
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
	pListCtrl->InsertColumn(0,_T("院系名称"),0,150);
	pListCtrl->InsertColumn(1,_T("负责人"),0,100);
	pListCtrl->InsertColumn(2,_T("联系电话"),0,150);
	pListCtrl->SetBkColor(RGB(205,226,252));
	pListCtrl->SetTextBkColor(RGB(205,226,252));
	pListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//初始化列表2
	CListCtrl *pListCtrl2 = (CListCtrl *)GetDlgItem(IDC_TEAMLIST);
	pListCtrl2->InsertColumn(0,_T("团队名称"),0,100);
	pListCtrl2->InsertColumn(1,_T("负责人"),0,100);
	pListCtrl2->InsertColumn(2,_T("教师人数"),0,100);
	pListCtrl2->InsertColumn(3,_T("研究生人数"),0,100);
	pListCtrl2->InsertColumn(4,_T("所属院系"),0,100);
	pListCtrl2->SetBkColor(RGB(205,226,252));
	pListCtrl2->SetTextBkColor(RGB(205,226,252));
	pListCtrl2->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//初始化列表3
	CListCtrl *pListCtrl3 = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
	pListCtrl3->InsertColumn(0,_T("项目编号"),0,100);
	pListCtrl3->InsertColumn(1,_T("项目类别"),0,100);
	pListCtrl3->InsertColumn(2,_T("起始时间"),0,100);
	pListCtrl3->InsertColumn(3,_T("项目经费"),0,100);
	pListCtrl3->InsertColumn(4,_T("项目负责人"),0,100);
	pListCtrl3->InsertColumn(5,_T("所属团队"),0,100);
	pListCtrl3->InsertColumn(6,_T("所属院系"),0,100);
	pListCtrl3->SetBkColor(RGB(205,226,252));
	pListCtrl3->SetTextBkColor(RGB(205,226,252));
	pListCtrl3->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSciPgMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSciPgMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//非类方法SetListViewItem,用来帮助在选定的列表控件中插入项目
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

//插入按钮响应
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
					//链表插入
					std::map<std::string,InstituteNode *>::iterator mapIter = instiNameMap.find(str);
					if(mapIter == instiNameMap.end())
					{
						pTreeCtrl->InsertItem(cstringVec[0],TVI_ROOT,hTreeItem);
						InstituteNode *pinstNode = initInsti();
						insertInsti2iLL(pinstNode);
						//地址信息插入map
						instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(str,pinstNode));
					}else
					{
						InstituteNode *pinstNode = mapIter->second;
						if(wcslen(pinstNode->institude.manager))
						{
							MessageBox(_T("表中已存在该数据,无法录入!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
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
					std::string str = CT2A(cstringVec[4]);  //院系
					std::string strTemp = CT2A(cstringVec[0]);  //团队名
					std::map<std::string,InstituteNode *>::iterator instiMapIter = instiNameMap.find(str);
					std::map<std::string,TeamNode *>::iterator teamMapIter = teamNameMap.find(strTemp + " " + str);
					if(teamMapIter == teamNameMap.end())
					{
						InstituteNode *pinstNode;
						//若当前队伍信息未开辟内存
						if(instiMapIter == instiNameMap.end())
						{
							//这个未开辟的队伍如果其院系信息未开辟则开辟院系信息
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
							//树控件插入
							for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
							hTreeItem = pTreeCtrl->InsertItem(cstringVec[4],TVI_ROOT,hTreeItem);
							pTreeCtrl->InsertItem(cstringVec[0],hTreeItem);
						}else
						{
							//这个未开辟内存的队伍的院系信息已存在
							pinstNode = instiMapIter->second;
							//树控件插入
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
						//当前团队信息已开辟过内存
						TeamNode *pTeamNode = teamMapIter->second;
						if(wcslen(pTeamNode->team.manager))
						{
							//开辟过内存并已被赋过完全的信息
							MessageBox(_T("团队名重名,无法录入!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
							return;
						}else
						{
							//尚未赋值则进行赋值
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
					std::string str = CT2A(cstringVec[6]);  //院系
					std::string str2 = CT2A(cstringVec[5]);  //团队名
					std::string str3 = CT2A(cstringVec[0]);	 //项目编号
					std::map<std::string,InstituteNode *>::iterator instMapIter = instiNameMap.find(str);
					std::map<std::string,TeamNode *>::iterator teamMapIter = teamNameMap.find(str2 + " " + str);
					std::map<std::string,programItemNode *>::iterator itemMapIter = itemNumMap.find(str3);
					if(itemMapIter == itemNumMap.end())
					{
						//该项目尚未录入
						if(teamMapIter == teamNameMap.end())
						{
							//该项目的团队信息不存在
							InstituteNode *pinstNode;
							TeamNode *pTeamNode;
							if(instMapIter == instiNameMap.end())
							{
								//该项目的院系信息也不存在,开辟新的院系节点和团队节点
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
								//树控件插入
								for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[6],TVI_ROOT,hTreeItem);
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[5],hTreeItem);
								hTreeItem = pTreeCtrl->InsertItem(cstringVec[0],hTreeItem);
							}else
							{
								pinstNode = instMapIter->second;
								//该项目的院系信息存在则不开辟院系,开辟新的团队节点
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
								//树控件插入
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
							//该项目的团队信息已开辟内存
							TeamNode *pTeamNode = teamMapIter->second;
							programItemNode *pProItemNode = initProgram();
							insertProg2pLL(pTeamNode->pLL,pProItemNode);
							itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(str3,pProItemNode));
							//树控件插入
							for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != cstringVec[6];hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
							HTREEITEM hItem,hIt;
							for(hItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hItem) != cstringVec[5];hItem = pTreeCtrl->GetNextSiblingItem(hItem));
							for(hIt = pTreeCtrl->GetChildItem(hItem);hIt;hIt = pTreeCtrl->GetNextSiblingItem(hIt));
							pTreeCtrl->InsertItem(cstringVec[0],hItem,hIt);
						}
					}else
					{
						//该项目已被录入
						MessageBox(_T("项目代号名重名,无法录入!"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
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

//删除按钮响应
void CSciPgMDlg::OnBnClickedDelebtn()
{
	CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(this->FocusedListID);
	CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
	HTREEITEM hTreeItem;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if(pos)
	{
		int response = MessageBox(_T("确定删除选中的行吗？"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
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
						//找到
						//1.删除树控件里团队下的所有内容
						std::set<CString> tempSet; //存放所有项目序号的集合
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrInstName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrTeamName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(HTREEITEM hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem;hItem = pTreeCtrl->GetNextSiblingItem(hItem))
							tempSet.insert(std::set<CString>::value_type(pTreeCtrl->GetItemText(hItem)));
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.删除列表控件中的相关项目
						CListCtrl *pItemListCtrl = (CListCtrl *)GetDlgItem(IDC_ITEMLIST);
						for(int NumOfItem = 0;NumOfItem < pItemListCtrl->GetItemCount();NumOfItem++)
						{
							if(tempSet.find(pItemListCtrl->GetItemText(NumOfItem,0)) != tempSet.end())
							{
								pItemListCtrl->DeleteItem(NumOfItem);
								NumOfItem--;
							}
						}
						//3.在内存空间删除项目信息
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
						//1.删除树控件里学院下的所有内容
						std::set<CString> tempTeamSet,tempItemSet;
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrInstiName;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(HTREEITEM hItem = pTreeCtrl->GetChildItem(hTreeItem);hItem;hItem = pTreeCtrl->GetNextSiblingItem(hItem))
						{
							tempTeamSet.insert(pTreeCtrl->GetItemText(hItem));
							for(HTREEITEM hItem2 = pTreeCtrl->GetChildItem(hItem);hItem2;hItem2 = pTreeCtrl->GetNextSiblingItem(hItem2))
								tempItemSet.insert(pTreeCtrl->GetItemText(hItem2));
						}
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.删除列表控件中的相关项目
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
						//3.在内存空间删除项目信息
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
						//1.删除树控件里的相应项目内容
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);pTreeCtrl->GetItemText(hTreeItem) != cstrItemInsti;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrItemTeam;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);pTreeCtrl->GetItemText(hTreeItem) != cstrItemNum;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						pTreeCtrl->DeleteItem(hTreeItem);
						//2.在内存空间删除项目信息
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

//修改按钮响应
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
				MessageBox(_T("检测到您打开文件后未创建链表,为了获得更好的体验,请到菜单栏中生成链表或者Ctrl + F快捷键,本次修改已取消"),_T("NOTICE"));
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
				//改变图形控件中的显示
				//表格控件
				this->cstringVec = cinstiDlg.cstringVec;
				CListCtrl *pListCtrl = (CListCtrl *)GetDlgItem(IDC_INSTILIST);
				int nSel = pListCtrl->GetSelectionMark();
				std::string instiNameStr = CT2A(cstringVec[0]);
				std::map<std::string,InstituteNode *>::iterator instiIter2 = instiNameMap.find(instiNameStr);
				if(instiIter2 != instiNameMap.end())
				{
					MessageBox(_T("检测到此学院名已存在,无法输入!"),_T("NOTICE"));
					instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(instiNameStr,pInstiNode));
					return;
				}
				pListCtrl->SetItemText(nSel,0,cstringVec[0]);
				pListCtrl->SetItemText(nSel,1,cstringVec[1]);
				pListCtrl->SetItemText(nSel,2,cstringVec[2]);
				//改变学院节点信息
				wcscpy_s(pInstiNode->institude.name,cstringVec[0]);
				wcscpy_s(pInstiNode->institude.manager,cstringVec[1]);
				wcscpy_s(pInstiNode->institude.tel,cstringVec[2]);
				instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(instiNameStr,pInstiNode));
				//如果学院名这个关键字符串改变，那么做相应处理
				if(keyCString != cstringVec[0])
				{
					//改变其他两个表格中的信息
					//团队表
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
					//项目表
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
					//树
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
				MessageBox(_T("检测到您打开文件后未创建链表,为了获得更好的体验,请到菜单栏中生成链表或者Ctrl + F快捷键,本次修改已取消"),_T("NOTICE"));
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
					MessageBox(_T("检测到此团队已存在,无法输入!"),_T("NOTICE"));
					teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(keyString1 + " " + keyString2,pTeamNode));
					return;
				}
				if(instiIter == instiNameMap.end())
				{
					MessageBox(_T("无法找到与修改后的院系名相对应的院系信息,修改操作不提供内存开辟的功能!"),_T("NOTICE"));
					teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(keyString1 + " " + keyString2,pTeamNode));
					return;
				}
				pListCtrl->SetItemText(nSel,0,cstringVec[0]);
				pListCtrl->SetItemText(nSel,1,cstringVec[1]);
				pListCtrl->SetItemText(nSel,2,cstringVec[2]);
				pListCtrl->SetItemText(nSel,3,cstringVec[3]);
				pListCtrl->SetItemText(nSel,4,cstringVec[4]);
				//改变团队节点的信息
				wcscpy_s(pTeamNode->team.name,cstringVec[0]);
				wcscpy_s(pTeamNode->team.manager,cstringVec[1]);
				pTeamNode->team.teacherNum = _wtoi(cstringVec[2]);
				pTeamNode->team.postGraduaNum = _wtoi(cstringVec[3]);
				wcscpy_s(pTeamNode->team.instituteName,cstringVec[4]);
				teamNameMap.insert(std::map<std::string,TeamNode *>::value_type(strTeamName + " " + strInstiName,pTeamNode));
				//如果学院名这个关键字符串改变，那么做相应处理
				if((keyCString1 + _T(" ") + keyCString2) != (cstringVec[0] + _T(" ") + cstringVec[4]))
				{
					if(keyCString1 != cstringVec[0] && keyCString2 == cstringVec[4])
					{
						//队伍名修改但学院名不变
						//改变项目列表中的内容
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
						//树
						CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
						HTREEITEM hTreeItem;
						for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCString2;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCString1;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
						if(hTreeItem)
							pTreeCtrl->SetItemText(hTreeItem,cstringVec[0]);
					}
					if(keyCString2 != cstringVec[4])
					{
						//院系名发生改变
						//改变项目列表的内容
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
						//改变树的结构和链表的结构
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
						//链表结构改变
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
				MessageBox(_T("检测到您打开文件后未创建链表,为了获得更好的体验,请到菜单栏中生成链表或者Ctrl + F快捷键,本次修改已取消"),_T("NOTICE"));
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
					MessageBox(_T("检测到此项目已存在,无法输入!"),_T("NOTICE"));
					itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(keyString,pProItemNode));
					return;
				}
				if(teamIter == teamNameMap.end())
				{
					MessageBox(_T("无法找到与修改后的团队名相对应的团队信息,修改操作不提供内存开辟的功能!"),_T("NOTICE"));
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
				//改变项目节点的信息
				wcscpy_s(pProItemNode->item.number,cstringVec[0]);
				pProItemNode->item.typePro = cstringVec[1][0];
				wcscpy_s(pProItemNode->item.startTime,cstringVec[2]);
				pProItemNode->item.cost = (float)_wtof(cstringVec[3]);
				wcscpy_s(pProItemNode->item.manager,cstringVec[4]);
				wcscpy_s(pProItemNode->item.teamName,cstringVec[5]);
				wcscpy_s(pProItemNode->item.instiName,cstringVec[6]);
				itemNumMap.insert(std::map<std::string,programItemNode *>::value_type(strItemNum,pProItemNode));
				//如果关键字符串发生改变,进行相应的处理
				CTreeCtrl *pTreeCtrl = (CTreeCtrl *)GetDlgItem(IDC_TREE);
				HTREEITEM hTreeItem;
				for(hTreeItem = pTreeCtrl->GetChildItem(TVI_ROOT);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstrInsti;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstrTeam;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				for(hTreeItem = pTreeCtrl->GetChildItem(hTreeItem);hTreeItem && pTreeCtrl->GetItemText(hTreeItem) != keyCstring;hTreeItem = pTreeCtrl->GetNextSiblingItem(hTreeItem));
				pTreeCtrl->SetItemText(hTreeItem,cstringVec[0]);
				if(((keyCstrTeam + _T(" ") + keyCstrInsti) != (cstringVec[5] + _T(" ") + cstringVec[6])))
				{
					//归属学院发生改变
					//改变树控件和内存结构
					HTREEITEM tempItem;
					for(tempItem = pTreeCtrl->GetChildItem(TVI_ROOT);tempItem && pTreeCtrl->GetItemText(tempItem) != cstringVec[6];tempItem = pTreeCtrl->GetNextSiblingItem(tempItem));
					for(tempItem = pTreeCtrl->GetChildItem(tempItem);tempItem && pTreeCtrl->GetItemText(tempItem) != cstringVec[5];tempItem = pTreeCtrl->GetNextSiblingItem(tempItem));
					moveTree(hTreeItem,tempItem,pTreeCtrl);
					pTreeCtrl->DeleteItem(hTreeItem);
					//链表结构
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

//捕获鼠标移动事件保存当前选中的列表控件,保存至CSciPgMDlg类的相应属性中方便其他函数访问
void CSciPgMDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd *pWnd = GetFocus();
	CString cstr("选中");
	UINT nId;
	if(pWnd)
		nId = pWnd->GetDlgCtrlID();
	else
		return;
	if(nId == IDC_INSTILIST || nId == IDC_TEAMLIST || nId == IDC_ITEMLIST)
	{
		this->FocusedListID = nId;
		if(nId == IDC_ITEMLIST)
			SetDlgItemText(IDC_NOTICE,cstr + " 科研项目信息表");
		else if(nId == IDC_INSTILIST)
			SetDlgItemText(IDC_NOTICE,cstr + " 学院信息表");
		else if(nId == IDC_TEAMLIST)
			SetDlgItemText(IDC_NOTICE,cstr + " 科研团队信息表");
	}
}

//菜单栏->打开文件选项
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
			MessageBox(_T("文件占用或不可访问"),_T("EXCEPTION"),MB_ICONERROR);
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
					int nRes = MessageBox(_T("打开的文件会覆盖当前学院信息表,是否保存当前表格？"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
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
					int nRes = MessageBox(_T("打开的文件会覆盖当前团队信息表,是否保存当前表格？"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
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
					int nRes = MessageBox(_T("打开的文件会覆盖当前科研项目信息表,是否保存当前表格？"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
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
		MessageBox(_T("文件导入成功"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
		pProgressCtrl->SetPos(0);
	}
}

//菜单栏->保存学院文件选项
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
			MessageBox(_T("文件占用或不可访问,保存失败"),_T("EXCEPTION"),MB_ICONERROR);
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

//菜单栏->保存科研团队文件选项
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
			MessageBox(_T("文件占用或不可访问，,保存失败"),_T("EXCEPTION"),MB_ICONERROR);
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

//菜单栏->保存科研项目文件选项
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
			MessageBox(_T("文件占用或不可访问,保存失败"),_T("EXCEPTION"),MB_ICONERROR);
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

//菜单栏->保存全部文件选项
void CSciPgMDlg::OnSaveAll()
{
	OnSaveInstituteTable();
	OnSaveTeamTable();
	OnSaveProgramTable();
}

//菜单栏->文件重置选项
void CSciPgMDlg::OnTableReset()
{
	CTableResetDlg tableResetDlg(this);
	if(IDOK == tableResetDlg.DoModal())
	{
		int nresponse = MessageBox(_T("是否需要保存当前表格后再重置?"),_T("QUESTION"),MB_ICONQUESTION | MB_OKCANCEL);
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

//菜单栏->文件退出选项
void CSciPgMDlg::OnExit()
{
	int nRes = MessageBox(_T("退出前是否保存文件？"),_T("NOTICE"),MB_ICONQUESTION | MB_OKCANCEL);
	if(nRes == IDOK)
		OnSaveAll();
	OnClearLinkedList();
	EndDialog(IDCANCEL);
}

//重载虚函数,实现快捷键
BOOL CSciPgMDlg::PreTranslateMessage(MSG* pMsg)
{
	if(TranslateAccelerator(m_hWnd,hAccel,pMsg))  
		return true;    
	return CDialogEx::PreTranslateMessage(pMsg);
}

//关闭按钮响应
void CSciPgMDlg::OnCancel()
{
	OnExit();
}

//展开树形控件的所有节点
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

//树控件展示
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



//链表生成
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
	//转化学院表格为课设要求的十字链表
	for(int i = 0;i < itemNum;i++)
	{
		std::string strKey = CT2A(pListCtrl->GetItemText(i,0));
		if((instiMapIter = instiNameMap.find(strKey)) != instiNameMap.end())
			continue;
		InstituteNode *inst = (InstituteNode *)malloc(sizeof(InstituteNode));
		//将学院链表节点插入
		inst->tLL = (TeamLinkedList *)malloc(sizeof(TeamLinkedList));
		inst->tLL->head = NULL;inst->tLL->tail = NULL;
		
		cstr = pListCtrl->GetItemText(i,0);
		wcscpy_s(inst->institude.name, cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,1);
		wcscpy_s(inst->institude.manager,cstr.GetBuffer(cstr.GetLength()));
		cstr = pListCtrl->GetItemText(i,2);
		wcscpy_s(inst->institude.tel,cstr.GetBuffer(cstr.GetLength()));
		//为了优化查询速度,使用STL——map
		instiNameMap.insert(std::map<std::string,InstituteNode *>::value_type(strKey,inst));
		insertInsti2iLL(inst);
	}
	//转化团队表格
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
			//学院名已存在的情况：出现新的团队名
			InstituteNode *pinstNode = tempiter->second;
			insertTeam2tLL(pinstNode->tLL,team);
		}else
		{
			//学院名也不存在创建新的学院节点
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
	//转化科研项目表格
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
			//找到了已存在的团队信息
			TeamNode *pteamNode = tempIter->second;
			insertProg2pLL(pteamNode->pLL,pItemNode);
		}else
		{
			InstituteNode *pinstNode;
			//未找到已存在的团队信息
			if((instiMapIter = instiNameMap.find(findStr)) != instiNameMap.end())
			{
				pinstNode = instiMapIter->second;
				//院系名已存在:创建新的团队节点并将新团队加入map保存,再插入项目节点
			}else
			{
				//院系名不存在：创建新的院系节点和团队节点并将这些名字送入map保存，再插入项目节点
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

//链表初始化
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
	MessageBox(_T("内存链表初始化成功"),_T("NOTICE"),MB_ICONINFORMATION | MB_OK);
	return;
}


void CSciPgMDlg::OnFuncUse()
{
	GetMenu()->GetSubMenu(2)->CheckMenuRadioItem(ID_32800,ID_32801,ID_32800,MF_BYCOMMAND);
	autoSynSwitch = true;
}


void CSciPgMDlg::OnFuncUnuse()
{
	MessageBox(_T("由于禁用功能会导致不可预料的程序行为,已经被舍弃!"),_T("NOTICE"),MB_ICONINFORMATION);
	return;
}

//Debug功能
void CSciPgMDlg::On32802()
{
	showOnTreeCtrl();
}

//将链表显示到表格控件中
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

//Override以防止回车调用父类的OnOK而退出
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
