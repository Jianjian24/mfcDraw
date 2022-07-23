
// CLTDrawDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "InfoFile.h"


// CCLTDrawDlg �Ի���
class CCLTDrawDlg : public CDialogEx
{
// ����
public:
	CCLTDrawDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_CLTDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
private:
	CBrush m_showBrush; // չʾ����ı�ˢ�����ڿ���չʾ�����ɫ
	// ��״������
	CComboBox m_cbxShape;
	// �߳���뾶 lengthOrRad
	UINT m_LR;
	// ���ĵ�x����
	UINT m_pointX;
	// ���ĵ�Y�����Լ��Ƿ�ı���y������
	UINT m_pointY, m_cacheY;
	// ͼ���ٶ�
	UINT m_speed;
	// ͼ�����·���ѡ��
	BOOL m_direction;
	// ������һ��ͼ�ε�y������
	LONG m_preY;
	// ��ˢ��ɫ�ؼ�
	BOOL m_changeColor;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void CCLTDrawDlg::OnOK();

private:
	BOOL m_BTN_Start;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonstart();
//	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonload();
	afx_msg void OnClickedButtonsave();
	afx_msg void OnBnClickedShow();

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
