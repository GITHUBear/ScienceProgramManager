#pragma once
#include "afxcmn.h"
#include "FAQChildFileDlg.h"
#include "FAQChildDataDlg.h"
#include "FAQChildSyncDlg.h"
#include "FAQChildHelpDlg.h"

// CFAQDlg �Ի���

class CFAQDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQDlg)

public:
	CFAQDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFAQDlg();

// �Ի�������
	enum { IDD = IDD_FAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
