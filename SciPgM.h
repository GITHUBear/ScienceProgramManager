
// SciPgM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSciPgMApp:
// �йش����ʵ�֣������ SciPgM.cpp
//

class CSciPgMApp : public CWinApp
{
public:
	CSciPgMApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSciPgMApp theApp;