#pragma once
#include "afxdialogex.h"
#include <vector>
#include "Mail.h"

// Dialog_newMail 对话框

class Dialog_newMail : public CDialogEx
{
	DECLARE_DYNAMIC(Dialog_newMail)

public:
	Dialog_newMail(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Dialog_newMail();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NewMail };
#endif
	CString RCPT;
	CString 主题;
	CString 内容;
	std::vector<CString> info{
		RCPT, //这个是值
		主题,	
		内容,	
	};
	Mail mail;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
