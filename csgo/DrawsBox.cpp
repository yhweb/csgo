// DrawsBox.cpp: 实现文件
//

#include "pch.h"
#include "afxdialogex.h"
#include "DrawsBox.h"


// DrawsBox 对话框

IMPLEMENT_DYNAMIC(DrawsBox, CDialogEx)

DrawsBox::DrawsBox(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

DrawsBox::~DrawsBox()
{
}

void DrawsBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DrawsBox, CDialogEx)
	ON_BN_CLICKED(IDOK, &DrawsBox::OnBnClickedOk)
END_MESSAGE_MAP()


// DrawsBox 消息处理程序


void DrawsBox::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
