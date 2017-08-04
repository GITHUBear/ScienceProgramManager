#pragma once
#include "SciPgMDlg.h"

// CStatisChildDlg3 对话框

class CStatisChildDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisChildDlg3)

public:
	CStatisChildDlg3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisChildDlg3();

// 对话框数据
	enum { IDD = IDD_STATISDIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	struct packageTeam
	{
		TeamNode *pTeam;
		int itemCountryNum;
		double allCost;
	};
	virtual BOOL OnInitDialog();
	CSciPgMDlg *pSciDlg;
	afx_msg void OnDestroy();

private:
	packageTeam *remakeTeam(TeamNode *);
	std::vector<packageTeam *> pacTeamVec;
};
