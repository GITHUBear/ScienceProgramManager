#pragma once


// CProgramDlg �Ի���

class CProgramDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProgramDlg)

public:
	CProgramDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CProgramDlg();

	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

// �Ի�������
	enum { IDD = IDD_PRODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
