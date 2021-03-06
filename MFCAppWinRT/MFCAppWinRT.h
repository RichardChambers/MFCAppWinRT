
// MFCAppWinRT.h : main header file for the MFCAppWinRT application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCAppWinRTApp:
// See MFCAppWinRT.cpp for the implementation of this class
//

class CMFCAppWinRTApp : public CWinAppEx
{
public:
	CMFCAppWinRTApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCAppWinRTApp theApp;
