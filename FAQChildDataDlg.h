#pragma once


// CFAQChildDataDlg �Ի���

class CFAQChildDataDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildDataDlg)

public:
	CFAQChildDataDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFAQChildDataDlg();

// �Ի�������
	enum { IDD = IDD_DATAFAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
