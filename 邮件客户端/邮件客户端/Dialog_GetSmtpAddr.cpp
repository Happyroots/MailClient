// Dialog_GetSmtpAddr.cpp: 实现文件
//

#include "pch.h"
#include "邮件客户端.h"
#include "afxdialogex.h"
#include "Dialog_GetSmtpAddr.h"


// Dialog_GetSmtpAddr 对话框

IMPLEMENT_DYNAMIC(Dialog_GetSmtpAddr, CDialogEx)

Dialog_GetSmtpAddr::Dialog_GetSmtpAddr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GetSmtpAddr, pParent)
{

}

Dialog_GetSmtpAddr::~Dialog_GetSmtpAddr()
{
}

void Dialog_GetSmtpAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog_GetSmtpAddr, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_GetSmtpAddr::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog_GetSmtpAddr::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog_GetSmtpAddr::OnBnClickedButton1)
END_MESSAGE_MAP()


// Dialog_GetSmtpAddr 消息处理程序


void Dialog_GetSmtpAddr::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempSendHost;
	GetDlgItemText(IDC_EDIT1 , tempSendHost);

	if (tempSendHost != "") {
		mail.sendHost = CT2A(tempSendHost.GetString());
	}
	mail.GetSmtpAddr();
	SetDlgItemText(IDC_EDIT2, (CString)mail.sendHostAddr.c_str());

	//CDialogEx::OnOK();
}


void Dialog_GetSmtpAddr::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	
	CDialogEx::OnCancel();
}


void Dialog_GetSmtpAddr::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString tempSendHostAddr;
	GetDlgItemText(IDC_EDIT2, tempSendHostAddr);

	if (tempSendHostAddr != "") {
		mail.sendHostAddr = CT2A(tempSendHostAddr.GetString());
		MessageBox(L"修改成功");
	}
}
