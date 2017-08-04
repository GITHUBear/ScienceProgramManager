#pragma once


// CFAQChildSyncDlg 对话框

class CFAQChildSyncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildSyncDlg)

public:
	CFAQChildSyncDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFAQChildSyncDlg();

// 对话框数据
	enum { IDD = IDD_SYNCDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
