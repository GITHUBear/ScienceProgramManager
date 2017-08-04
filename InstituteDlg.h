#pragma once

#include <vector>
#include <cstringt.h>

// CInstituteDlg �Ի���

class CInstituteDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInstituteDlg)

public:
	CInstituteDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInstituteDlg();

// �Ի�������
	enum { IDD = IDD_INSTIDLG };

	//��Ҫ���ݵ����ݱ�����vector��
	std::vector<CString,std::allocator<CString>> cstringVec;
	int isEdit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
