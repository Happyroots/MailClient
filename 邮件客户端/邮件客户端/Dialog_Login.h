#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Mail.h"

// Dialog_Login 对话框

class Dialog_Login : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_Login)

public:
	Dialog_Login(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_Login();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Login };
#endif
	Mail mail;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString	邮箱用户名;
	CString	授权码;
	CString	SMTP服务器域名;
	CString	SMTP服务器地址;
	CString	POP3服务器域名;
	CString	POP3服务器地址;
	std::vector <CString> info = {
		邮箱用户名,
		授权码,
		SMTP服务器地址,
		POP3服务器地址,
	};

	//CEdit 邮箱用户名;
	//CString testStr;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedlogin();
	afx_msg void OnBnClickedCancel();
};
