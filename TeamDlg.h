#pragma once


// CTeamDlg 对话框

class CTeamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeamDlg)

public:
	CTeamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTeamDlg();

	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

// 对话框数据
	enum { IDD = IDD_TEAMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
