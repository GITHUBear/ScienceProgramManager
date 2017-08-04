#pragma once


// CTableResetDlg 对话框

class CTableResetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTableResetDlg)

public:
	CTableResetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTableResetDlg();

// 对话框数据
	enum { IDD = IDD_TABLERESETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
