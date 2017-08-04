// FindInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SciPgM.h"
#include "FindInfoDlg.h"
#include "afxdialogex.h"
#include <regex>

// CFindInfoDlg �Ի���

IMPLEMENT_DYNAMIC(CFindInfoDlg, CDialogEx)

CFindInfoDlg::CFindInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindInfoDlg::IDD, pParent)
{

}

CFindInfoDlg::~CFindInfoDlg()
{
}

void CFindInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBOLISTCHOOSE, listChooseCombo);
	DDX_Control(pDX, IDC_COMBOFINDMETHOD, findMethodCombo);
}


BEGIN_MESSAGE_MAP(CFindInfoDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBOLISTCHOOSE, &CFindInfoDlg::OnCbnSelchangeCombolistchoose)
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()


// CFindInfoDlg ��Ϣ�������


void CFindInfoDlg::OnCancel()
{
	CDialogEx::OnCancel();
	pSciPgmDlg->linkedList2ListShow();
	DestroyWindow();
}


void CFindInfoDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	delete this;
}


BOOL CFindInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetFocus();
	listChooseCombo.AddString(_T("ѧԺ�б�"));
	listChooseCombo.AddString(_T("�Ŷ��б�"));
	listChooseCombo.AddString(_T("��Ŀ�б�"));
	return TRUE;
}


void CFindInfoDlg::OnCbnSelchangeCombolistchoose()
{
	int nIndex = listChooseCombo.GetCurSel();
	CString listContext;
	listChooseCombo.GetLBText(nIndex,listContext);
	if(listContext == _T("ѧԺ�б�"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("Ժϵ������"));
		findMethodCombo.AddString(_T("ѧԺ��"));
	}else if(listContext == _T("�Ŷ��б�"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("�Ŷ�����"));
		findMethodCombo.AddString(_T("��ʦ����>"));
		findMethodCombo.AddString(_T("��ʦ����<"));
		findMethodCombo.AddString(_T("��ʦ����>="));
		findMethodCombo.AddString(_T("��ʦ����<="));
		findMethodCombo.AddString(_T("��ʦ����>=? <=?"));
	}else if(listContext == _T("��Ŀ�б�"))
	{
		findMethodCombo.ResetContent();
		findMethodCombo.AddString(_T("��Ŀ���"));
		findMethodCombo.AddString(_T("�����Ŷ�"));
	}
	return;
}

BOOL instiManagerMatch(InstituteNode *pInsti,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pInsti->institude.manager,keyWord);
}

BOOL instiNameMatch(InstituteNode *pInsti,const CString& keyWord)
{
 	return CFindInfoDlg::KMP(pInsti->institude.name,keyWord);
}

BOOL teamNameMatch(TeamNode *pTeam,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pTeam->team.name,keyWord);
}

//��ʦ����>
BOOL teamTeacherNumMatch1(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum > num ? TRUE : FALSE;
}

//��ʦ����<
BOOL teamTeacherNumMatch2(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum < num ? TRUE : FALSE;
}

//��ʦ����>=
BOOL teamTeacherNumMatch3(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum >= num ? TRUE : FALSE;
}

//��ʦ����<=
BOOL teamTeacherNumMatch4(TeamNode *pTeam,const CString& keyWord)
{
	int num = _wtoi(keyWord);
	return pTeam->team.teacherNum <= num ? TRUE : FALSE;
}

//��ʦ����>=? <=?
BOOL teamTeacherNumMatch5(TeamNode *pTeam,const CString& keyWord)
{
	int a,b;
	swscanf_s(keyWord,_T("%d %d"),&a,&b);
	if(a <= b)
		return (pTeam->team.teacherNum >= a && pTeam->team.teacherNum <= b) ? TRUE : FALSE;
	else
		return (pTeam->team.teacherNum >= b && pTeam->team.teacherNum <= a) ? TRUE : FALSE;
}

BOOL itemNumMatch(programItemNode *pItem,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pItem->item.number,keyWord);
}

BOOL itemTeamMatch(programItemNode *pItem,const CString& keyWord)
{
	return CFindInfoDlg::KMP(pItem->item.teamName,keyWord);
}

void CFindInfoDlg::OnOK()
{
	CString cstrListChoose,cstrSearchMethod,cstrKeyword;
	int nIndex;
	nIndex = listChooseCombo.GetCurSel();
	listChooseCombo.GetLBText(nIndex,cstrListChoose);
	nIndex = findMethodCombo.GetCurSel();
	findMethodCombo.GetLBText(nIndex,cstrSearchMethod);
	GetDlgItemText(IDC_FINDEDIT,cstrKeyword);
	if(!cstrListChoose.GetLength() || !cstrSearchMethod.GetLength() || !cstrKeyword.GetLength())
	{
		MessageBox(_T("����ĿΪ�գ�"),_T("NOTICE"),MB_ICONINFORMATION);
		return;
	}
	if(cstrListChoose == _T("ѧԺ�б�"))
	{
		if(cstrSearchMethod == _T("Ժϵ������"))
			pSciPgmDlg->findInsti2ListShow(instiManagerMatch,cstrKeyword);
		else if(cstrSearchMethod == _T("ѧԺ��"))
			pSciPgmDlg->findInsti2ListShow(instiNameMatch,cstrKeyword);
		else
		{
			MessageBox(_T("���ϸ�ʹ�ø�ѡ���ѡ��!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else if(cstrListChoose == _T("�Ŷ��б�"))
	{
		if(cstrSearchMethod == _T("�Ŷ�����"))
		{
			pSciPgmDlg->findTeam2ListShow(teamNameMatch,cstrKeyword);
		}else if(cstrSearchMethod == _T("��ʦ����>"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch1,cstrKeyword);
			else
			{
				MessageBox(_T("���ҹؼ��������ʽ����,����������(9λ��int��)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("��ʦ����<"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch2,cstrKeyword);
			else
			{
				MessageBox(_T("���ҹؼ��������ʽ����,����������(9λ��int��)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("��ʦ����>="))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch3,cstrKeyword);
			else
			{
				MessageBox(_T("���ҹؼ��������ʽ����,����������(9λ��int��)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("��ʦ����<="))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch4,cstrKeyword);
			else
			{
				MessageBox(_T("���ҹؼ��������ʽ����,����������(9λ��int��)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else if(cstrSearchMethod == _T("��ʦ����>=? <=?"))
		{
			std::string checkStr = CT2A(cstrKeyword);
			std::string pattern("(\\d{1,9}) (\\d{1,9})");
			std::regex re(pattern);
			if(std::regex_match(checkStr,re))
				pSciPgmDlg->findTeam2ListShow(teamTeacherNumMatch5,cstrKeyword);
			else
			{
				MessageBox(_T("���ҹؼ��������ʽ����,�������ʽ:num num(numΪ9λ��int��)"),_T("NOTICE"),MB_ICONEXCLAMATION);
				return;
			}
		}else
		{
			MessageBox(_T("���ϸ�ʹ�ø�ѡ���ѡ��!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else if(cstrListChoose == _T("��Ŀ�б�"))
	{
		if(cstrSearchMethod == _T("��Ŀ���"))
		{
			pSciPgmDlg->findItem2ListShow(itemNumMatch,cstrKeyword);
		}else if(cstrSearchMethod == _T("�����Ŷ�"))
		{
			pSciPgmDlg->findItem2ListShow(itemTeamMatch,cstrKeyword);
		}else
		{
			MessageBox(_T("���ϸ�ʹ�ø�ѡ���ѡ��!"),_T("NOTICE"),MB_ICONEXCLAMATION);
			return;
		}
	}else
	{
		MessageBox(_T("���ϸ�ʹ�ø�ѡ���ѡ��!"),_T("NOTICE"),MB_ICONEXCLAMATION);
		return;
	}
	return;
}

int *CFindInfoDlg::buildNext(const CString& patte)
{
	int i = 1,k = 1;
	int *nextArray = (int *)malloc(sizeof(int) * patte.GetLength());
	memset(nextArray,0,sizeof(nextArray));
	while(i < patte.GetLength()){
		if(k - 1 >= 0 && patte[i] == patte[nextArray[k - 1]]){
			nextArray[i] = nextArray[k - 1] + 1;
			i++;k = i;
		}else{
			if(k - 1 < 0){
				nextArray[i] = 0;
				i++;k = i;
			}else k = nextArray[k - 1];
		}
	}
	return nextArray;
}

BOOL CFindInfoDlg::KMP(const CString& str,const CString& patte)
{
	int *nextArray = buildNext(patte);
	int pos = 0;
	for(int i = 0;i <= str.GetLength();i++){
		if(pos == patte.GetLength())
		{
			free(nextArray);
			return TRUE;
		}
		if(!pos && patte[pos] != str[i]) continue;
		if(pos < patte.GetLength()){
			if(patte[pos] == str[i]){
				pos++;continue;
			}else{
				while(pos){
					if(patte[nextArray[pos - 1]] == str[i]){
						pos = nextArray[pos - 1] + 1;
						break;
					}else pos = nextArray[pos - 1];
				}
			}
		}
	}
	free(nextArray);
	return FALSE;
}