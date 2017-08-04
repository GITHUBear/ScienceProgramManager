#pragma once
#include "afxcmn.h"
#include "FAQChildFileDlg.h"
#include "FAQChildDataDlg.h"
#include "FAQChildSyncDlg.h"
#include "FAQChildHelpDlg.h"

// CFAQDlg 对话框

class CFAQDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQDlg)

public:
	CFAQDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFAQDlg();

// 对话框数据
	enum { IDD = IDD_FAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl myFAQTabCtrl;
	int curentSelTab;
	CFAQChildFileDlg fileDlg;
	CFAQChildDataDlg dataDlg;
	CFAQChildSyncDlg syncDlg;
	CFAQChildHelpDlg helpDlg;
	CDialog *pDlg[4];
	virtual BOOL OnInitDialog();
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
};
