#pragma once
#include "SciPgMDlg.h"

// CStatisChildDlg2 对话框

class CStatisChildDlg2 : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisChildDlg2)

public:
	CStatisChildDlg2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisChildDlg2();

// 对话框数据
	enum { IDD = IDD_STATISDIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	struct packageInsti
	{
		InstituteNode *pinst;
		int itemNum;
		int item973Num;
		int item863Num;
		double allCost;
	};
	virtual BOOL OnInitDialog();
	CSciPgMDlg *pSciDlg;

private:
	packageInsti *remakeInsti(InstituteNode *);
	std::vector<packageInsti *> pacInstiVec;
public:
	afx_msg void OnDestroy();
};
