
// wxCaptureDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CwxCaptureDlg �Ի���
class CwxCaptureDlg : public CDialogEx
{
// ����
public:
	CwxCaptureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WXCAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	CEdit m_EditImagePath;
	CString m_sImagePath; // ͼƬ����·��
	CStatic m_StaticXPos;
	CStatic m_StaticYPos;
	CPoint m_x, m_y; // ��������
	CString m_sFormat; // ͼƬ��ʽ
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
