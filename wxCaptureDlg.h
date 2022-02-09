
// wxCaptureDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CwxCaptureDlg 对话框
class CwxCaptureDlg : public CDialogEx
{
// 构造
public:
	CwxCaptureDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WXCAPTURE_DIALOG };
#endif

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
	CEdit m_EditImagePath;
	CString m_sImagePath; // 图片保存路径
	CStatic m_StaticXPos;
	CStatic m_StaticYPos;
	CPoint m_x, m_y; // 截屏区域
	CString m_sFormat; // 图片格式
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnOperatorSelect();
	afx_msg void OnOperatorCapture();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	void SaveAsJPG(CString name);
	CComboBox m_ComboFormat;
	void OutputDebugInfo(CString info);
	afx_msg void OnCbnSelchangeComboFormat();
	CStatic m_StaticInfo;
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};
