#pragma once


// CFAQChildFileDlg �Ի���

class CFAQChildFileDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFAQChildFileDlg)

public:
	CFAQChildFileDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFAQChildFileDlg();

// �Ի�������
	enum { IDD = IDD_FILEFAQDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
