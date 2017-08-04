#pragma once
#include "SciPgMDlg.h"

// CStatisChildDlg4 �Ի���

class CStatisChildDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisChildDlg4)

public:
	CStatisChildDlg4(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisChildDlg4();

// �Ի�������
	enum { IDD = IDD_STATISDIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	struct packageTeam
	{
		TeamNode *pTeam;
		int teacherNum;
		int itemNum;
		double ratioValue;
	};
	virtual BOOL OnInitDialog();
	CSciPgMDlg *pSciDlg;
	afx_msg void OnDestroy();

private:
	packageTeam *remakeTeam(TeamNode *);
	std::vector<packageTeam *> pacTeamVec;
};
