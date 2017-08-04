#pragma once
#include "SciPgMDlg.h"

// CStatisChildDlg1 �Ի���

class CStatisChildDlg1 : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisChildDlg1)

public:
	CStatisChildDlg1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisChildDlg1();

// �Ի�������
	enum { IDD = IDD_STATISDIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	struct packageInsti
	{
		InstituteNode *pInsti;
		int teacherNum;
		int postGraNum;
		double ratioValue;
	};
	virtual BOOL OnInitDialog();
	CSciPgMDlg *pSciDlg;

private:
	packageInsti *remakeInsti(InstituteNode *);
	std::vector<packageInsti *> pacInstiVec;
public:
	afx_msg void OnDestroy();
};
