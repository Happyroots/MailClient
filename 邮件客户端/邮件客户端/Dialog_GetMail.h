#pragma once
#include "afxdialogex.h"
#include "Mail.h"


// Dialog_GetMail 对话框

class Dialog_GetMail : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_GetMail)

public:
	Dialog_GetMail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_GetMail();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GetMail };
#endif
	Mail mail;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox combox_choosmail;
	void OnBnClickedButton1();
};
