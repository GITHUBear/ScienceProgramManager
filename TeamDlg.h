#pragma once


// CTeamDlg �Ի���

class CTeamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTeamDlg)

public:
	CTeamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTeamDlg();

	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

// �Ի�������
	enum { IDD = IDD_TEAMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
