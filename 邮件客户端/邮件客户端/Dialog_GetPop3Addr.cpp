// Dialog_GetPop3Addr.cpp: 实现文件
//

#include "pch.h"
#include "邮件客户端.h"
#include "afxdialogex.h"
#include "Dialog_GetPop3Addr.h"


// Dialog_GetPop3Addr 对话框

IMPLEMENT_DYNAMIC(Dialog_GetPop3Addr, CDialogEx)

Dialog_GetPop3Addr::Dialog_GetPop3Addr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GetPop3Addr, pParent)
{

}

Dialog_GetPop3Addr::~Dialog_GetPop3Addr()
{
}

void Dialog_GetPop3Addr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog_GetPop3Addr, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_GetPop3Addr::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog_GetPop3Addr::OnBnClickedButton1)
END_MESSAGE_MAP()


// Dialog_GetPop3Addr 消息处理程序


void Dialog_GetPop3Addr::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempRecHost;
	GetDlgItemText(IDC_EDIT1, tempRecHost);

	if (tempRecHost != "") {
		mail.recHost = CT2A(tempRecHost.GetString());
	}
	mail.GetPop3Addr();
	SetDlgItemText(IDC_EDIT2, (CString)mail.recHostAddr.c_str());

	//CDialogEx::OnOK();
}


void Dialog_GetPop3Addr::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempRecHostAddr;
	GetDlgItemText(IDC_EDIT2, tempRecHostAddr);

	if (tempRecHostAddr != "") {
		mail.recHost = CT2A(tempRecHostAddr.GetString());
		MessageBox(L"修改成功");
	}
	//SetDlgItemText(IDC_EDIT2, (CString)mail.recHostAddr.c_str());

}
