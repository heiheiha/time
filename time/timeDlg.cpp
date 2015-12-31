
// timeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "time.h"
#include "timeDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtimeDlg 对话框




CtimeDlg::CtimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtimeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_time, &CtimeDlg::OnBnClickedtime)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CtimeDlg 消息处理程序

BOOL CtimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SetTimer(1,10,NULL);
	secag=-0.05;
	minag=-0.05;
	hag=-0.05;
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CtimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CtimeDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CtimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtimeDlg::OnBnClickedtime()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);
	dc.SetWindowOrg(0-150,0-150);
	CPen *oldpen;
	CPen pen(PS_SOLID,3,RGB(255,0,255));
	oldpen=dc.SelectObject(&pen);
	dc.Ellipse(-100,100,100,-100);
	dc.Ellipse(-1,-1,1,1);
	dc.TextOutW(90,-8,L"3");
	dc.TextOutW(-98,-8,L"9");
	dc.TextOutW(-8,-99.5,L"12");
	dc.TextOutW(-2,83,L"6");
	for(int i=0;i<12;i++)
	{
		double l=90,ag=i*3.1415926/6;
		double a=l*sin(ag)+1,b=-l*cos(ag)+1,c=l*sin(ag)-1,d=-l*cos(ag)-1;
		dc.Ellipse(a,b,c,d);
	}

}



void CtimeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	TRACE("X=%d,Y=%d\n",point.x,point.y);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CtimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClientDC dc(this);
	dc.SetWindowOrg(0-150,0-150);
	CPen *oldpen;
	CPen groundpen(PS_SOLID,4,RGB(255,255,255));
	CPen pen(PS_SOLID,3,RGB(color,color,color));
	oldpen=dc.SelectObject(&pen);
	dc.Ellipse(-100,100,100,-100);
	CPen ppen(PS_SOLID,3,RGB(color,color,color));
	oldpen=dc.SelectObject(&ppen);
	dc.Ellipse(-1,-1,1,1);
	dc.TextOutW(90,-8,L"3");
	dc.TextOutW(-98,-8,L"9");
	dc.TextOutW(-8,-99.5,L"12");
	dc.TextOutW(-2,83,L"6");
	for(int i=0;i<12;i++)
	{
		double l=90,ag=i*3.1415926/6;
		double a=l*sin(ag)+1,b=-l*cos(ag)+1,c=l*sin(ag)-1,d=-l*cos(ag)-1;
		dc.Ellipse(a,b,c,d);
	}


    double L1=70,L2=60,L3=50;          //miaozhen
	oldpen=dc.SelectObject(&groundpen);
	x=L1*sin(secag);
	y=-L1*cos(secag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	CPen secpen(PS_SOLID,2,RGB(150,150,150));
	oldpen=dc.SelectObject(&secpen);
	secag=secag+3.1415926/30;
	x=L1*sin(secag);
	y=-L1*cos(secag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	if(secag>=6.2831852)
		secag=-3.1415926/30;


	oldpen=dc.SelectObject(&groundpen);//fenzhen
	x=L2*sin(minag);
	y=-L2*cos(minag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	CPen minpen(PS_SOLID,3,RGB(0,255,150));
	oldpen=dc.SelectObject(&minpen);
	minag=minag+3.1415926/1800;
	x=L2*sin(minag);
	y=-L2*cos(minag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	if(minag>=6.2831852)
		minag=-3.1415926/1800;


	oldpen=dc.SelectObject(&groundpen);//shizhen
	x=L3*sin(hag);
	y=-L3*cos(hag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	CPen hpen(PS_SOLID,3,RGB(255,0,0));
	oldpen=dc.SelectObject(&hpen);
	hag=hag+3.1415926/21600;
	x=L3*sin(hag);
	y=-L3*cos(hag);
	dc.MoveTo(0,0);
	dc.LineTo(x,y);
	if(hag>=6.2831852)
		hag=-3.1415926/21600;




	CDialogEx::OnTimer(nIDEvent);
	
}
