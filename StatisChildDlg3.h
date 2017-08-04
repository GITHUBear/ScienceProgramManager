#pragma once
#include "SciPgMDlg.h"

// CStatisChildDlg3 �Ի���

class CStatisChildDlg3 : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisChildDlg3)

public:
	CStatisChildDlg3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisChildDlg3();

// �Ի�������
	enum { IDD = IDD_STATISDIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	struct packageTeam
	{
		TeamNode *pTeam;
		int itemCountryNum;
		double allCost;
	};
	virtual BOOL OnInitDialog();
	CSciPgMDlg *pSciDlg;
	afx_msg void OnDestroy();

private:
	packageTeam *remakeTeam(TeamNode *);
	std::vector<packageTeam *> pacTeamVec;
};
