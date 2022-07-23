
// CLTDrawDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "InfoFile.h"


// CCLTDrawDlg 对话框
class CCLTDrawDlg : public CDialogEx
{
// 构造
public:
	CCLTDrawDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
	enum { IDD = IDD_CLTDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
private:
	CBrush m_showBrush; // 展示界面的笔刷，用于控制展示界面底色
	// 形状下拉框
	CComboBox m_cbxShape;
	// 边长或半径 lengthOrRad
	UINT m_LR;
	// 中心点x坐标
	UINT m_pointX;
	// 中心点Y坐标以及是否改变了y轴坐标
	UINT m_pointY, m_cacheY;
	// 图形速度
	UINT m_speed;
	// 图形上下方向选择
	BOOL m_direction;
	// 保存上一次图形的y轴坐标
	LONG m_preY;
	// 画刷变色控件
	BOOL m_changeColor;
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
