
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "FileView.h"
#include "ClassView.h"
#include "OutputWnd.h"
#include "PropertiesWnd.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	// ADD_ON: helper functions so that we can send messages to various windows and panes in the UI.
	//         We must send messages because the UI can only be updated from the main UI thread of MFC.
	//         Trying to update MFC controls and windows from threads other than an MFC UI thread causes problems.
	//         We are using SendMessage() however SendMessage() is synchronous and can cause problems with C++11 threads
	//         which do a join() in the case of std::thread or a get() in the case of std::async in order to finish
	//         the thread by capturing its result. If the std:thread uses SendMessage() then it is unable to reach
	//         the synchronization point of the join() until the SendMessage() returns. The concurrency namespace
	//         threads do not have this problem.
	LRESULT  SendMessageToFileView(UINT msgId, WPARAM wParam, LPARAM lParam) { return m_wndFileView.SendMessage(msgId, wParam, lParam); }
	LRESULT  SendMessageToClassView(UINT msgId, WPARAM wParam, LPARAM lParam) { return m_wndClassView.SendMessage(msgId, wParam, lParam); }
	LRESULT  SendMessageToOutputWnd(UINT msgId, WPARAM wParam, LPARAM lParam) { return m_wndOutput.SendMessage(msgId, wParam, lParam); }

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL LoadFrame(UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = nullptr, CCreateContext* pContext = nullptr);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;
	CFileView         m_wndFileView;
	CClassView        m_wndClassView;
public:
	COutputWnd        m_wndOutput;
	CPropertiesWnd    m_wndProperties;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnGesture(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
};


