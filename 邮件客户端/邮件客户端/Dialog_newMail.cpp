// Dialog_newMail.cpp: 实现文件
//

#include "pch.h"
#include "邮件客户端.h"
#include "afxdialogex.h"
#include "Dialog_newMail.h"


// Dialog_newMail 对话框

IMPLEMENT_DYNAMIC(Dialog_newMail, CDialogEx)

Dialog_newMail::Dialog_newMail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NewMail, pParent)
{

}

Dialog_newMail::~Dialog_newMail()
{
}

void Dialog_newMail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dialog_newMail, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_newMail::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dialog_newMail::OnBnClickedCancel)
END_MESSAGE_MAP()


// Dialog_newMail 消息处理程序


void Dialog_newMail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i = 0; i < info.size(); i++) {
		GetDlgItemText(IDC_EDIT1 + i, info[i]);
		//MessageBox(info[i]);
	}
	if (info[0] != "")
		mail.EmailTo = CT2A(info[0].GetString());
	if (info[1] != "") {
		mail.subject = CT2A(info[1].GetString());
	}
	if (info[2] != "") {
		mail.content = CT2A(info[2].GetString());
	}
	mail.SendMail();
	CDialogEx::OnOK();
}


void Dialog_newMail::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
