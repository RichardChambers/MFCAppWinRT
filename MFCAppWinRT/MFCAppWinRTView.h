
// MFCAppWinRTView.h : interface of the CMFCAppWinRTView class
//

#pragma once


class CMFCAppWinRTView : public CView
{
protected: // create from serialization only
	CMFCAppWinRTView();
	DECLARE_DYNCREATE(CMFCAppWinRTView)

// Attributes
public:
	CMFCAppWinRTDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
	POINTS  m_lastXY;
	int     m_iLine;
	BOOL    m_isOverpan;
	long    m_xOverpan;
	long    m_yOverpan;
	short   m_lastY;
	SCROLLINFO   m_si;

public:
	virtual ~CMFCAppWinRTView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg LRESULT OnGesture(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MFCAppWinRTView.cpp
inline CMFCAppWinRTDoc* CMFCAppWinRTView::GetDocument() const
   { return reinterpret_cast<CMFCAppWinRTDoc*>(m_pDocument); }
#endif

