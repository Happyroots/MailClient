// Dialog_Login.cpp: 实现文件
//

#include "pch.h"
#include "邮件客户端.h"
#include "afxdialogex.h"
#include "Dialog_Login.h"


// Dialog_Login 对话框

IMPLEMENT_DYNAMIC(Dialog_Login, CDialogEx)

Dialog_Login::Dialog_Login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Login, pParent)
{

}

Dialog_Login::~Dialog_Login()
{
}

void Dialog_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(Dialog_Login, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &Dialog_Login::OnBnClickedOk)
	ON_BN_CLICKED(ID_login, &Dialog_Login::OnBnClickedlogin)
	ON_BN_CLICKED(IDCANCEL, &Dialog_Login::OnBnClickedCancel)
END_MESSAGE_MAP()


void Dialog_Login::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//邮箱用户名.GetWindowTextW(testStr);
	//if (GetDlgItemText(IDC_EDIT1,邮箱用户名)) {
	//	
	//}

}


void Dialog_Login::OnBnClickedlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < info.size(); i++) {
		GetDlgItemText(IDC_EDIT1 + i, info[i]);
		//MessageBox(info[i]);
	}
	if (info[0] != "") {
		mail.username = CT2A(info[0].GetString());
	}
	if (info[1] != "") {
		mail.password = CT2A(info[1].GetString());
	}
	if (info[2] != "") {
		mail.sendHostAddr = CT2A(info[2].GetString());
	}
	if (info[3] != "") {
		mail.recHostAddr = CT2A(info[3].GetString());
	}
	mail.Login();
	CDialogEx::OnCancel();
}


void Dialog_Login::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
