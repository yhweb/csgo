// MFC_DLL_TEST.cpp: 实现文件
//

#include "pch.h"
#include "MFC_DLL.h"
#include "afxdialogex.h"
#include "MFC_DLL_TEST.h"


// MFC_DLL_TEST 对话框

IMPLEMENT_DYNAMIC(MFC_DLL_TEST, CDialogEx)

MFC_DLL_TEST::MFC_DLL_TEST(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MFC_DLL_TEST::~MFC_DLL_TEST()
{
}

void MFC_DLL_TEST::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MFC_DLL_TEST, CDialogEx)
	ON_BN_CLICKED(IDOK, &MFC_DLL_TEST::OnBnClickedOk)
END_MESSAGE_MAP()


// MFC_DLL_TEST 消息处理程序


void MFC_DLL_TEST::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	::MessageBoxA();
	CDialogEx::OnOK();
}
