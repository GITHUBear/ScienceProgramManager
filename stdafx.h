
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��

#include <vector>
#include <map>
#include <string>
#include <atlconv.h>
#include <set>
#include <algorithm>


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif

struct Institute
{
	TCHAR name[20];
	TCHAR manager[12];
	TCHAR tel[15];
};

struct Team
{
	TCHAR name[30];
	TCHAR manager[12];
	int teacherNum;
	int postGraduaNum;
	TCHAR instituteName[20];
};

struct programItem
{
	TCHAR number[15];
	TCHAR typePro;
	TCHAR startTime[8];
	float cost;
	TCHAR manager[12];
	TCHAR teamName[30];
	TCHAR instiName[20];
};

struct programItemNode
{
	programItem item;
	programItemNode *nextNode;
	programItemNode *prevNode;
};

struct programLinkedList
{
	programItemNode *head;
	programItemNode *tail;
};

struct TeamNode
{
	Team team;
	TeamNode *nextNode;
	TeamNode *prevNode;
	programLinkedList *pLL;
};

//�Ŷ�����
struct TeamLinkedList
{
	TeamNode *head;
	TeamNode *tail;
};

//ѧԺ����ڵ�
struct InstituteNode
{
	Institute institude;
	InstituteNode *nextNode;
	InstituteNode *prevNode;
	TeamLinkedList *tLL;
};

//ѧԺ����
struct InstituteLinkedList
{
	InstituteNode *head;
	InstituteNode *tail;
};