#pragma once
#include "afxdialogex.h"


// MFC_DLL_TEST 对话框

class MFC_DLL_TEST : public CDialogEx
{
	DECLARE_DYNAMIC(MFC_DLL_TEST)

public:
	MFC_DLL_TEST(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MFC_DLL_TEST();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
