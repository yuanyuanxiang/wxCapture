
// wxCapture.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CwxCaptureApp: 
// �йش����ʵ�֣������ wxCapture.cpp
//

class CwxCaptureApp : public CWinApp
{
public:
	CwxCaptureApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CwxCaptureApp theApp;