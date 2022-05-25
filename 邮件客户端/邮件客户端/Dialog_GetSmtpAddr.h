#pragma once
#include "afxdialogex.h"
#include "Mail.h"


// Dialog_GetSmtpAddr 对话框

class Dialog_GetSmtpAddr : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_GetSmtpAddr)

public:
	Dialog_GetSmtpAddr(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_GetSmtpAddr();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GetSmtpAddr };
#endif
	Mail mail;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
};
