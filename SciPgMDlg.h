
// SciPgMDlg.h : 头文件
//

#pragma once
#include "afxwin.h"

// CSciPgMDlg 对话框
class CSciPgMDlg : public CDialogEx
{
// 构造
public:
	CSciPgMDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCIPGM_DIALOG };

	//添加的属性
	std::vector<CString,std::allocator<CString>> cstringVec;
	UINT FocusedListID;
	std::map<std::string,InstituteNode *> instiNameMap;
	std::map<std::string,TeamNode *> teamNameMap;
	std::map<std::string,programItemNode *> itemNumMap;
	bool autoSynSwitch;
	InstituteLinkedList iLL;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInsertbtn();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedDelebtn();
	afx_msg void OnBnClickedEditbtn();
	afx_msg void OnOpenFile();
	afx_msg void OnSaveInstituteTable();
	afx_msg void OnSaveTeamTable();
	afx_msg void OnSaveProgramTable();
	afx_msg void OnSaveAll();
	afx_msg void OnTableReset();
	afx_msg void OnExit();
	HACCEL hAccel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnCancel();
	afx_msg void OnFormLinkedList();
	void showOnTreeCtrl();
	void ExpandAllNode(HTREEITEM, CTreeCtrl *);
	InstituteNode *initInsti();
	TeamNode *initTeam();
	programItemNode *initProgram();
	void insertInsti2iLL(InstituteNode *);
	void insertTeam2tLL(TeamLinkedList *,TeamNode *);
	void insertProg2pLL(programLinkedList *,programItemNode *);
	void moveTree(HTREEITEM hSource,HTREEITEM hDest,CTreeCtrl *pTreeCtrl);
	void linkedList2ListShow();
	void findInsti2ListShow(BOOL (*compareFunc)(InstituteNode *,const CString&),CString keyWord);
	void findTeam2ListShow(BOOL (*compareFunc)(TeamNode *,const CString&),CString keyWord);
	void findItem2ListShow(BOOL (*compareFunc)(programItemNode *,const CString&),CString keyWord);
	afx_msg void OnClearLinkedList();
	afx_msg void OnFuncUse();
	afx_msg void OnFuncUnuse();
	afx_msg void On32802();
	afx_msg void OnFindInfo();
	virtual void OnOK();
	afx_msg void OnStatistic();
	CButton insertBtn;
	CButton deleteBtn;
	CButton editBtn;
	afx_msg void OnIntro();
	afx_msg void OnAbout();
};
