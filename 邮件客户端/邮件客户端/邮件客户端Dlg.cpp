
// 邮件客户端Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "邮件客户端.h"
#include "邮件客户端Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "Dialog_Login.h"
#include "Dialog_newMail.h"
#include "Dialog_GetSmtpAddr.h"
#include "Dialog_GetPop3Addr.h"
#include "Dialog_GetMail.h"


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C邮件客户端Dlg 对话框



C邮件客户端Dlg::C邮件客户端Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

//动态数据交换
void C邮件客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C邮件客户端Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &C邮件客户端Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &C邮件客户端Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C邮件客户端Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C邮件客户端Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C邮件客户端Dlg::OnBnClickedButton4)


	ON_BN_CLICKED(IDC_BUTTON5, &C邮件客户端Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// C邮件客户端Dlg 消息处理程序

BOOL C邮件客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//cFont = new CFont;
	//cFont->CreateFont(40,            // nHeight 
	//	0,           // nWidth 
	//	0,           // nEscapement 
	//	0,           // nOrientation 
	//	FW_BOLD,     // nWeight 
	//	FALSE,        // bItalic 斜体
	//	FALSE,       // bUnderline 
	//	0,           // cStrikeOut 
	//	ANSI_CHARSET,              // nCharSet 
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision 
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision 
	//	DEFAULT_QUALITY,           // nQuality 
	//	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
	//	_T("Arial"));              // lpszFac
	//CWnd* pWnd = GetDlgItem(IDC_STATIC_subject);
	//pWnd->SetFont(cFont);
	//pWnd = GetDlgItem(IDC_STATIC_content);
	//pWnd->SetFont(cFont);
	//pWnd = GetDlgItem(IDC_STATIC_choosemail);
	//pWnd->SetFont(cFont);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C邮件客户端Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C邮件客户端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
	}

	//添加代码对话框背景贴图
	CPaintDC   dc(this);
	CRect   rect0;
	GetClientRect(&rect0);    //获取对话框长宽      
	CDC   dcBmp;             //定义并创建一个内存设备环境
	dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_GetmailBack);    //载入资源中图片
	BITMAP   m_bitmap;                         //图片变量               
	bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
	//将位图选入临时内存设备环境
	CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
	//调用函数显示图片StretchBlt显示形状可变
	dc.StretchBlt(0, 0, rect0.Width(), rect0.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C邮件客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void C邮件客户端Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

//写信
void C邮件客户端Dlg::OnBnClickedButton4()
{
	Dialog_newMail dlg;
	dlg.mail = mail; //暂时使用的
	//dlg.ShowDialog();
	if (dlg.DoModal() == IDOK)
	{
	}
	//for (int i = 0; i < newMailInfo.size(); i++) {
	//	if (dlg.info[i] != "") {
	//		newMailInfo[i] = CT2A(dlg.info[i].GetString());
	//		//MessageBox(CString(loginInfo[i].c_str()));
	//	}
	//}
	//if(dlg.info[0] != "" )
	//	mail.EmailTo = CT2A(dlg.info[0].GetString());
	//if (dlg.info[1] != "" ) {
	//	mail.subject = CT2A(dlg.info[1].GetString());
	//}
	//if (dlg.info[2] != "") {
	//	mail.content = CT2A(dlg.info[2].GetString());
	//}
	//mail.SendMail();
	//CDialogEx::OnCancel();
}



//登录
void C邮件客户端Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog_Login dlg ;
	//dlg.ShowDialog();
	dlg.mail = mail;
	if (dlg.DoModal() == IDOK) //打开对话框并存储相应数据
	{
		//for (int i = 0; i < loginInfo.size(); i++) {
		//	if ( dlg.info[i] ) {
		//		loginInfo[i] = CT2A(dlg.info[i].GetString()); 
		//		MessageBox(CString(loginInfo[i].c_str()));
		//	}
		//}
	}
	//for (int i = 0; i < loginInfo.size(); i++) {
	//	if (dlg.info[i] != "") {
	//		loginInfo[i] = CT2A(dlg.info[i].GetString());
	//		//MessageBox(CString(loginInfo[i].c_str()));
	//	}
	//}
	mail = dlg.mail;
	//CDialogEx::OnCancel();
}


//获取和修改SMTP服务器地址
void C邮件客户端Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog_GetSmtpAddr dlg;
	if (dlg.DoModal() == IDOK);
	mail.sendHost = dlg.mail.sendHost;
	mail.sendHostAddr = dlg.mail.sendHostAddr;
}

//获取和修改POP3服务器地址
void C邮件客户端Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog_GetPop3Addr dlg;
	if (dlg.DoModal() == IDOK);
	mail.recHost = dlg.mail.recHost;
	mail.recHostAddr = dlg.mail.recHostAddr;
}


//收件箱
void C邮件客户端Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	Dialog_GetMail dlg;

	//无模式对话框也假死
	//Dialog_GetMail* pDlg = new Dialog_GetMail;
	//if (pDlg->m_hWnd == NULL) {
	//	pDlg->Create(IDD_DIALOG_GetMail);
	//}
	//pDlg->ShowWindow(SW_SHOW);


	dlg.mail = mail;
	if (dlg.DoModal() == IDOK) {
	}
}
