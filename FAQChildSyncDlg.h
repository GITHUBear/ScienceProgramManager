#pragma once


// CFAQChildSyncDlg �Ի���

class CFAQChildSyncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildSyncDlg)

public:
	CFAQChildSyncDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFAQChildSyncDlg();

// �Ի�������
	enum { IDD = IDD_SYNCDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
