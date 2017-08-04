#pragma once


// CFAQChildFileDlg 对话框

class CFAQChildFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildFileDlg)

public:
	CFAQChildFileDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFAQChildFileDlg();

// 对话框数据
	enum { IDD = IDD_FILEFAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
