
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持

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

//团队链表
struct TeamLinkedList
{
	TeamNode *head;
	TeamNode *tail;
};

//学院链表节点
struct InstituteNode
{
	Institute institude;
	InstituteNode *nextNode;
	InstituteNode *prevNode;
	TeamLinkedList *tLL;
};

//学院链表
struct InstituteLinkedList
{
	InstituteNode *head;
	InstituteNode *tail;
};