
// timeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "time.h"
#include "timeDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CtimeDlg �Ի���




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


// CtimeDlg ��Ϣ�������

BOOL CtimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	SetTimer(1,10,NULL);
	secag=-0.05;
	minag=-0.05;
	hag=-0.05;
	

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtimeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtimeDlg::OnBnClickedtime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACE("X=%d,Y=%d\n",point.x,point.y);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CtimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
