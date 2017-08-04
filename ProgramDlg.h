#pragma once


// CProgramDlg 对话框

class CProgramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgramDlg)

public:
	CProgramDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgramDlg();

	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

// 对话框数据
	enum { IDD = IDD_PRODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
