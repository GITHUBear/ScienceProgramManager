#pragma once


// CTableResetDlg �Ի���

class CTableResetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTableResetDlg)

public:
	CTableResetDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTableResetDlg();

// �Ի�������
	enum { IDD = IDD_TABLERESETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
