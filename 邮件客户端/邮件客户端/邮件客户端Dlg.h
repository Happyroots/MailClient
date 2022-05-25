
// 邮件客户端Dlg.h: 头文件
//

#pragma once
#include "Mail.h"
#include <vector>

// C邮件客户端Dlg 对话框
class C邮件客户端Dlg : public CDialogEx
{
// 构造
public:
	C邮件客户端Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif
	CFont* cFont;
	Mail mail;
	std::vector<string> loginInfo = {
		mail.username,
		mail.password,
		mail.sendHost,
		mail.sendHostAddr,
		mail.recHost,
		mail.recHostAddr,
	};
	std::vector <string> newMailInfo = {
		mail.EmailTo,
		mail.subject,
		mail.content,
	};


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
