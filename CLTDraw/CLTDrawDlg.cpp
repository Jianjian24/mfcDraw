
// CLTDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CLTDraw.h"
#include "CLTDrawDlg.h"
#include "afxdialogex.h"
#include <math.h>

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
// CCLTDrawDlg �Ի���

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
	m_showBrush.CreateSolidBrush(RGB(0, 0, 255)); // ��ʾ���Ļ�ˢ
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


// CCLTDrawDlg ��Ϣ�������

BOOL CCLTDrawDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_cbxShape.AddString(TEXT("Բ"));
	m_cbxShape.AddString(TEXT("������"));

	m_cbxShape.SetCurSel(0);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCLTDrawDlg::OnPaint()
{
	TRACE("\n��ʼ��ͼ\n");
	CPaintDC dc(this);

	CBrush myBrush;
	// ѡ���ˢ��ɫ
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
	ScreenToClient(&rect); // ����ת��

	UpdateData(TRUE); // ���ؼ�����ͬ����������

	// �ж�Y���Ƿ�ı�,�ı��˵Ļ���¼�µ�λ�ã����Ļ����ַ
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
	UINT a = 0; // 2*a^2 = c^2 ���ڼ���Բ�ĵ����αߵľ���������������ĵ㵽��Ե�ľ���

	if (indexCombobox == 0)
	{
		a = (UINT)sqrt(double(m_LR * m_LR / 2));
		// ����ת��֮������ĵ�
		LONG tempX = rect.left + m_pointX,
			tempY = rect.top + m_preY;
		// ����ת��֮��Ŀ��������λ����
		LONG l = tempX - a, t = tempY - a
			, r = tempX + a, b = tempY + a;

		dc.Ellipse(l, t, r, b);

	}
	else if (indexCombobox == 1)
	{
		a = (UINT)m_LR / 2;
		// ����ת��֮������ĵ�
		LONG tempX = rect.left + m_pointX,
			tempY = rect.top + m_preY;
		// ����ת��֮��Ŀ��������λ����
		LONG l = tempX - a, t = tempY - a
			, r = tempX + a, b = tempY + a;

		dc.Rectangle(l, t, r, b);
	}
	else
	{
		ASSERT(1 == 0);// �����ж�
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCLTDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCLTDrawDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	TRACE("\n��һ����ʱ��\n");
}

void CCLTDrawDlg::OnClickedButtonstart()
{
	// TODO: Add your control notification handler code here
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_BTN_Start = !m_BTN_Start;
	CWnd* MyWnd = GetDlgItem(IDC_BUTTONSTART);
	if (m_BTN_Start == true)//��ť������
	{
		MyWnd->SetWindowText(L"ֹͣ");
		SetTimer(1, 1000, NULL);
	}
	else
	{
		MyWnd->SetWindowText(L"����");
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
	UpdateData(FALSE); // �ѱ������ݸ��µ��ؼ���
}

void CCLTDrawDlg::OnClickedButtonsave()
{
	// TODO: Add your control notification handler code here
	CInfoFile file;
	UpdateData(TRUE); // �ѿؼ����ݸ��µ�������
	file.msg.shape = m_cbxShape.GetCurSel();
	file.msg.lengthOrRad = m_LR;
	file.msg.x = m_pointX;
	file.msg.y = m_pointY;
	file.msg.speed = m_speed;
	file.SaveInfo();
	MessageBox(L"����ɹ�");
}

// ����ȡ��editControl�Ļس��˳����
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
