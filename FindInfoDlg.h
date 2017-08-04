#pragma once
#include "afxwin.h"
#include "SciPgMDlg.h"

// CFindInfoDlg 对话框

class CFindInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFindInfoDlg)

public:
	CFindInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFindInfoDlg();

// 对话框数据
	enum { IDD = IDD_FINDDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox listChooseCombo;
	CComboBox findMethodCombo;
	CSciPgMDlg *pSciPgmDlg;
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCombolistchoose();
	virtual void OnOK();
	static BOOL KMP(const CString& str,const CString& patte);

private:
	static int *buildNext(const CString& patte);
};
