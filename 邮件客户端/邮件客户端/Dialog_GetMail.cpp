// Dialog_GetMail.cpp: 实现文件
//

#include "pch.h"
#include "邮件客户端.h"
#include "afxdialogex.h"
#include "Dialog_GetMail.h"
#include <thread>
#include "邮件客户端Dlg.h"

// Dialog_GetMail 对话框

IMPLEMENT_DYNAMIC(Dialog_GetMail, CDialogEx)

Dialog_GetMail::Dialog_GetMail(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GetMail, pParent)
{
	//combox_choosmail.SetCurSel(0);	// SetCurSel(0)0：邮件1，1：邮件2
	//combox_choosmail.SetCueBanner(L"邮件1");

}

Dialog_GetMail::~Dialog_GetMail()
{
}

void Dialog_GetMail::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, combox_choosmail);

	//C邮件客户端Dlg* parent = (C邮件客户端Dlg*)GetParent();//CSensorSysDlg是主对话框对应的类
	C邮件客户端Dlg* pMMD = (C邮件客户端Dlg*)AfxGetMainWnd();     //获取主窗口指针
	
	for (int i = 0; i < pMMD->mail.mailCount; i++) {
		string tempIndexName = "邮件" + to_string(i + 1);
		//必须从0开始设置
		combox_choosmail.InsertString(i, (CString)tempIndexName.c_str()); 
	}	
	combox_choosmail.SetCurSel(0);	//设置完数据后才能选择？对了 0：邮件1，1：邮件2
}


BEGIN_MESSAGE_MAP(Dialog_GetMail, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dialog_GetMail::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Dialog_GetMail::OnBnClickedButton1)
END_MESSAGE_MAP()


// Dialog_GetMail 消息处理程序


void Dialog_GetMail::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

//Mail Dialog_GetMail_AfxMail ;
//void Dialog_GetMail_GetMail(int mailNum) {
//	Dialog_GetMail_AfxMail.ReadMail(mailNum);
//} 

void Dialog_GetMail::OnBnClickedButton1()
{
	//C邮件客户端Dlg* parent = (C邮件客户端Dlg*)GetParent();//CSensorSysDlg是主对话框对应的类

	// TODO: 在此添加控件通知处理程序代码
	SetTimer(1, 100, NULL);  //设置100毫秒一次.ID为1
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);// 当按钮点击完成之后.变为禁止状态.
	
	//HWND hEdit = GetDlgItem(this->m_hWnd, IDC_EDIT2);
	for (int i = 0; i < 4; i++) {
		SetDlgItemText(IDC_EDIT1 + i, L"");
	}
	SetDlgItemText(IDC_EDIT2, L"");
	mail.mailNum = combox_choosmail.GetCurSel() + 1;
	AfxMessageBox(L"请耐心等待，大约2-10分钟！");
	//mail.GetMail();
	//Dialog_GetMail_AfxMail = Dialog_GetMail::mail;
	//std::thread th(Dialog_GetMail_GetMail, mail.mailNum);
	//th.join();

	mail.GetMail();
	string tempMailFileName = "邮件-" + to_string(mail.mailNum) + ".txt";
	ifstream infile;

	infile.open(tempMailFileName.c_str());
	if (!infile) {
		AfxMessageBox(L"邮件不存在");
	}
	
	string from;
	string to;
	string subject;
	string content;
	for (string buf; getline(infile, buf);) {
		if (!memcmp(buf.c_str(), "+OK", sizeof("+OK") - 1)) {
			;
		}
		
		else if (!memcmp(buf.c_str(), "From", sizeof("From") - 1)) {
			from += buf;
		}
		else if (!memcmp(buf.c_str(), "To:", sizeof("To:") - 1)) {
			to += buf;
		}
		else if (!memcmp(buf.c_str(),"Subject", sizeof("Subject") - 1)) {
			while (memcmp(buf.c_str(), "Content", sizeof("Content") - 1)) {
				subject += buf;
				buf = "";
				getline(infile, buf);
			}
			content += buf + "\n";
		}
		else
			content += buf + "\n";
	}
	SetDlgItemText(IDC_EDIT1, (CString)subject.c_str());
	SetDlgItemText(IDC_EDIT2, (CString)content.c_str());
	SetDlgItemText(IDC_EDIT3, (CString)from.c_str());
	SetDlgItemText(IDC_EDIT4, (CString)to.c_str());

	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);// 当按钮点击完成之后.变为禁止状态.
	//delete parent;
}

