
// wxCaptureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "wxCapture.h"
#include "wxCaptureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CwxCaptureDlg 对话框



CwxCaptureDlg::CwxCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WXCAPTURE_DIALOG, pParent)
	, m_sImagePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CwxCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_IMAGE_PATH, m_EditImagePath);
	DDX_Text(pDX, IDC_EDIT_IMAGE_PATH, m_sImagePath);
	DDX_Control(pDX, IDC_STATIC_X, m_StaticXPos);
	DDX_Control(pDX, IDC_STATIC_Y, m_StaticYPos);
	DDX_Control(pDX, IDC_COMBO_FORMAT, m_ComboFormat);
	DDX_Control(pDX, IDC_STATIC_INFO, m_StaticInfo);
}

BEGIN_MESSAGE_MAP(CwxCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_FORMAT, &CwxCaptureDlg::OnCbnSelchangeComboFormat)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()

const CString FORMAT[] = { L"jpg", L"png", L"bmp", L"tif", L"gif" };

// CwxCaptureDlg 消息处理程序

BOOL CwxCaptureDlg::OnInitDialog()
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

	ShowWindow(SW_NORMAL);

	// TODO: 在此添加额外的初始化代码
	for (int i=0;i<5;i++)
	{
		m_ComboFormat.InsertString(i, FORMAT[i]);
	}
	m_sFormat = FORMAT[0];
	m_ComboFormat.SetWindowTextW(m_sFormat);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CwxCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CwxCaptureDlg::OnPaint()
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
HCURSOR CwxCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CwxCaptureDlg::OutputDebugInfo(CString info) {
	m_StaticInfo.SetWindowTextW(info);
	OutputDebugString(CString(L"===> ")+info);
	UpdateData(FALSE);
}

BOOL CwxCaptureDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message==WM_LBUTTONDBLCLK&&pMsg->hwnd==m_EditImagePath.GetSafeHwnd())
	{
		BROWSEINFO bi;
		TCHAR Buffer[512];
		CString dir;
		bi.hwndOwner = NULL;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = Buffer;// 此参数如为NULL则不能显示对话框 
		bi.lpszTitle = _T("选择输出目录");
		bi.ulFlags = BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.iImage = 0;
		LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
		if (pIDList)
		{
			SHGetPathFromIDList(pIDList, Buffer);
			dir = Buffer;
			m_sImagePath = dir;
			UpdateData(FALSE);
			SetFocus();
		}
		OutputDebugInfo(CString("选择截图保存路径: ") + dir+L"\n");
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CwxCaptureDlg::OnOperatorSelect()
{
	static auto flag = 0;
	char tmp[100];
	if (flag % 2 == 0){
		GetCursorPos(&m_x);
		sprintf_s(tmp, "X: %d,%d", m_x.x, m_x.y);
		m_StaticXPos.SetWindowText(CString(tmp));
	}
	else {
		GetCursorPos(&m_y);
		sprintf_s(tmp, "Y: %d,%d", m_y.x, m_y.y);
		m_StaticYPos.SetWindowText(CString(tmp));
	}
	OutputDebugInfo(L"选择截图区域 "+CString(tmp)+L"\n");
	flag++;
	UpdateData(FALSE);
}

CString CurrentTime()
{
	CTime time = CTime::GetCurrentTime();
	CString curTime;
	curTime.Format(L"%04d-%02d-%02d %02d-%02d-%02d",
		time.GetYear(),
		time.GetMonth(),
		time.GetDay(),
		time.GetHour(),
		time.GetMinute(),
		time.GetSecond());
	return curTime;
}

void CwxCaptureDlg::OnOperatorCapture()
{
	if (m_sImagePath==""||(m_y.x == 0 && m_y.y == 0)) {
		MessageBox(L"请选择存储位置和截图区域!");
		return;
	}
	static int id = 1;
	char name[100];
	USES_CONVERSION;
	sprintf_s(name, "%s_%d.%s", W2A(CurrentTime()), id++, W2A(m_sFormat));
	OutputDebugInfo(L"截图操作: "+CString(name)+L"\n");
	SaveAsJPG(CString(name));
}

void CwxCaptureDlg::SaveAsJPG(CString name)
{
	HWND hwnd = ::GetDesktopWindow();
	HDC hDC = ::GetDC(hwnd);  

	HDC hDCMem = ::CreateCompatibleDC(hDC); 
	int width = m_y.x - m_x.x, height = m_y.y - m_x.y;
	HBITMAP hBitMap = ::CreateCompatibleBitmap(hDC, width, height);  
	HBITMAP hOldMap = (HBITMAP)::SelectObject(hDCMem, hBitMap); 

	::BitBlt(hDCMem, 0, 0, width, height, hDC, m_x.x, m_x.y, SRCCOPY); 

	CImage image;
	if (hBitMap == NULL) {
		OutputDebugInfo(L"创建内存图片失败\n");
		MessageBox(L"创建内存图片失败,截屏区域设置错误?");
		return;
	}
	image.Attach(hBitMap);
	if (image.IsNull()|| image.Save(m_sImagePath + CString("/") + name) != S_OK) {
		OutputDebugInfo(L"截图 \"" + name + L"\" 失败\n");
		MessageBox(L"截图失败，请重试!");
	}
	image.Detach();

	::SelectObject(hDCMem, hOldMap);
	::DeleteObject(hBitMap);
	::DeleteDC(hDCMem);
	::DeleteDC(hDC);
}

void CwxCaptureDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	switch (nHotKeyId) {
	case 1000:
		OnOperatorSelect();
		break;
	case 1001:
		OnOperatorCapture();
		break;
	default:
		break;
	}

	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}


int CwxCaptureDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	RegisterHotKey(this->GetSafeHwnd(), 1000, MOD_CONTROL| MOD_SHIFT, 'S');
	RegisterHotKey(this->GetSafeHwnd(), 1001, MOD_CONTROL | MOD_SHIFT, 'C');
	return 0;
}


void CwxCaptureDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	UnregisterHotKey(this->GetSafeHwnd(), 1000);
	UnregisterHotKey(this->GetSafeHwnd(), 1001);
}


void CwxCaptureDlg::OnCbnSelchangeComboFormat()
{
	UpdateData(TRUE);
	m_sFormat=FORMAT[m_ComboFormat.GetCurSel()];
	OutputDebugInfo(L"截图类型: " + m_sFormat + L"\n");
}


BOOL CwxCaptureDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	CAboutDlg dlg;
	return dlg.DoModal();
}
