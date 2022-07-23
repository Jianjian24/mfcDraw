
// CLTDrawDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CLTDraw.h"
#include "CLTDrawDlg.h"
#include "afxdialogex.h"
#include <math.h>

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
// CCLTDrawDlg 对话框

CCLTDrawDlg::CCLTDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCLTDrawDlg::IDD, pParent)
	, m_BTN_Start(FALSE)
	, m_LR(50)
	, m_pointX(100)
	, m_pointY(100)
	, m_speed(10)
	, m_direction(TRUE)
	, m_changeColor(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_showBrush.CreateSolidBrush(RGB(0, 0, 255)); // 显示组框的画刷
	m_preY = m_pointY;
	m_cacheY = m_pointY;
}

void CCLTDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTONSTART, m_BTN_Start);
	DDX_Control(pDX, IDC_COMBO1, m_cbxShape);
	DDX_Text(pDX, IDC_EDIT1, m_LR);
	DDX_Text(pDX, IDC_EDIT2, m_pointX);
	DDX_Text(pDX, IDC_EDIT3, m_pointY);
	DDX_Text(pDX, IDC_EDIT4, m_speed);
}

BEGIN_MESSAGE_MAP(CCLTDrawDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONSTART, &CCLTDrawDlg::OnClickedButtonstart)
	ON_BN_CLICKED(IDC_BUTTONLOAD, &CCLTDrawDlg::OnBnClickedButtonload)
	ON_BN_CLICKED(IDC_BUTTONSAVE, &CCLTDrawDlg::OnClickedButtonsave)
	ON_BN_CLICKED(IDC_SHOW, &CCLTDrawDlg::OnBnClickedShow)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CCLTDrawDlg 消息处理程序

BOOL CCLTDrawDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	m_cbxShape.AddString(TEXT("圆"));
	m_cbxShape.AddString(TEXT("正方形"));

	m_cbxShape.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCLTDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCLTDrawDlg::OnPaint()
{
	TRACE("\n开始绘图\n");
	CPaintDC dc(this);

	CBrush myBrush;
	// 选择笔刷颜色
	if (m_changeColor == TRUE)
	{
		myBrush.CreateSolidBrush(RGB(0, 0, 255));
		dc.SelectObject(&myBrush);
	}
	else
	{
		myBrush.CreateSolidBrush(RGB(255, 0, 0));
		dc.SelectObject(&myBrush);
	}

	CRect rect;
	GetDlgItem(IDC_SHOW)->GetWindowRect(&rect);
	ScreenToClient(&rect); // 坐标转换

	UpdateData(TRUE); // 将控件内容同步到变量里

	// 判断Y轴是否改变,改变了的话记录新的位置，更改缓存地址
	if (m_cacheY != m_pointY)
	{
		m_cacheY = m_pointY;
		m_preY = m_pointY;
	}

	if (m_speed <= 0)
	{
		TRACE("\m m_speed is : %d\n", m_speed);
		m_speed = 1;
	}
	int indexCombobox = m_cbxShape.GetCurSel();
	UINT a = 0; // 2*a^2 = c^2 用于计算圆心到矩形边的距离或者正方形中心点到边缘的距离

	if (indexCombobox == 0)
	{
		a = (UINT)sqrt(double(m_LR * m_LR / 2));
		// 坐标转换之后的中心点
		LONG tempX = rect.left + m_pointX,
			tempY = rect.top + m_preY;
		// 坐标转换之后的框的两个定位坐标
		LONG l = tempX - a, t = tempY - a
			, r = tempX + a, b = tempY + a;

		dc.Ellipse(l, t, r, b);

	}
	else if (indexCombobox == 1)
	{
		a = (UINT)m_LR / 2;
		// 坐标转换之后的中心点
		LONG tempX = rect.left + m_pointX,
			tempY = rect.top + m_preY;
		// 坐标转换之后的框的两个定位坐标
		LONG l = tempX - a, t = tempY - a
			, r = tempX + a, b = tempY + a;

		dc.Rectangle(l, t, r, b);
	}
	else
	{
		ASSERT(1 == 0);// 出错中断
	}
	if (m_direction)
	{
		if ((rect.top + m_preY - a) > rect.top + m_speed)
		{
			m_preY = m_preY - m_speed;
		}
		else
		{
			m_direction = (!m_direction);
			m_preY = m_preY + m_speed;
			//ASSERT(m_direction == FALSE);
		}
	}
	if (!m_direction)
	{
		ASSERT(m_direction == FALSE);
		if ((rect.top + m_preY + a) < (rect.top + rect.Height() - m_speed))
		{
			m_preY = m_preY + m_speed;
		}
		else
		{
			m_direction = (!m_direction);
			m_preY = m_preY - m_speed;
		}
	}
	TRACE("\n m_speed is %d \n", m_speed);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCLTDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCLTDrawDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	TRACE("\n是一个定时器\n");
}

void CCLTDrawDlg::OnClickedButtonstart()
{
	// TODO: Add your control notification handler code here
	// TODO: 在此添加控件通知处理程序代码
	m_BTN_Start = !m_BTN_Start;
	CWnd* MyWnd = GetDlgItem(IDC_BUTTONSTART);
	if (m_BTN_Start == true)//按钮被按下
	{
		MyWnd->SetWindowText(L"停止");
		SetTimer(1, 1000, NULL);
	}
	else
	{
		MyWnd->SetWindowText(L"启动");
		KillTimer(1);
	}
}

void CCLTDrawDlg::OnBnClickedButtonload()
{
	// TODO: Add your control notification handler code here
	CInfoFile file;
	file.LoadInfo();
	m_cbxShape.SetCurSel(file.msg.shape);
	m_LR = file.msg.lengthOrRad;
	m_pointX = file.msg.x;
	m_pointY = file.msg.y;
	m_speed = file.msg.speed;
	UpdateData(FALSE); // 把变量内容更新到控件上
}

void CCLTDrawDlg::OnClickedButtonsave()
{
	// TODO: Add your control notification handler code here
	CInfoFile file;
	UpdateData(TRUE); // 把控件内容更新到变量上
	file.msg.shape = m_cbxShape.GetCurSel();
	file.msg.lengthOrRad = m_LR;
	file.msg.x = m_pointX;
	file.msg.y = m_pointY;
	file.msg.speed = m_speed;
	file.SaveInfo();
	MessageBox(L"保存成功");
}

// 用于取消editControl的回车退出情况
void CCLTDrawDlg::OnOK()
{
}

void CCLTDrawDlg::OnBnClickedShow()
{
	// TODO: Add your control notification handler code here
	m_changeColor = (!m_changeColor);
}

void CCLTDrawDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnLButtonUp(nFlags, point);
	m_changeColor = (!m_changeColor);
}
