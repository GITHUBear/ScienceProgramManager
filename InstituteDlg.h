#pragma once

#include <vector>
#include <cstringt.h>

// CInstituteDlg 对话框

class CInstituteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInstituteDlg)

public:
	CInstituteDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInstituteDlg();

// 对话框数据
	enum { IDD = IDD_INSTIDLG };

	//需要传递的数据保存在vector中
	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
