#pragma once


// CFAQChildDataDlg 对话框

class CFAQChildDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildDataDlg)

public:
	CFAQChildDataDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFAQChildDataDlg();

// 对话框数据
	enum { IDD = IDD_DATAFAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
