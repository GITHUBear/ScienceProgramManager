#pragma once


// CFAQChildHelpDlg �Ի���

class CFAQChildHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildHelpDlg)

public:
	CFAQChildHelpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFAQChildHelpDlg();

// �Ի�������
	enum { IDD = IDD_HELPFAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
