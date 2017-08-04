#pragma once
#include "afxcmn.h"
#include "SciPgMDlg.h"
#include "StatisChildDlg1.h"
#include "StatisChildDlg2.h"
#include "StatisChildDlg3.h"
#include "StatisChildDlg4.h"

// CStatisticDlg 对话框

class CStatisticDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticDlg)

public:
	CStatisticDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticDlg();

// 对话框数据
	enum { IDD = IDD_STATISTICDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CSciPgMDlg *pSciDlg;
	CTabCtrl myTabCtrl;
	int curentSelTab;
	CStatisChildDlg1 page1;
	CStatisChildDlg2 page2;
	CStatisChildDlg3 page3;
	CStatisChildDlg4 page4;
	CDialog *pDlg[4];
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
