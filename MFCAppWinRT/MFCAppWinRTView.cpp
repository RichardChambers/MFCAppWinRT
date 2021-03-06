
// MFCAppWinRTView.cpp : implementation of the CMFCAppWinRTView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAppWinRT.h"
#endif

#include "MFCAppWinRTDoc.h"
#include "MFCAppWinRTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppWinRTView

IMPLEMENT_DYNCREATE(CMFCAppWinRTView, CView)

BEGIN_MESSAGE_MAP(CMFCAppWinRTView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAppWinRTView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(WM_GESTURE, &CMFCAppWinRTView::OnGesture)
END_MESSAGE_MAP()

// CMFCAppWinRTView construction/destruction

CMFCAppWinRTView::CMFCAppWinRTView() : m_lastXY {0}, m_iLine(0),
		m_isOverpan(0), m_xOverpan(0), m_yOverpan(0), m_lastY(0),
		m_si{ 0 }
{
	// TODO: add construction code here

}

CMFCAppWinRTView::~CMFCAppWinRTView()
{
}

BOOL CMFCAppWinRTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCAppWinRTView drawing

void CMFCAppWinRTView::OnDraw(CDC* pDC)
{
	CMFCAppWinRTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// A pointer to a RECT structure that receives the client coordinates.
	// The left and top members are zero.
	// The right and bottom members contain the width and height of the window. 
	RECT  clientRect{ 0 };
	GetClientRect(&clientRect);

	TEXTMETRIC tm;
	GetTextMetrics(pDC->m_hDC, &tm);
	int xChar = tm.tmAveCharWidth;
	int xUpper = (tm.tmPitchAndFamily & TMPF_FIXED_PITCH ? 3 : 2) * xChar / 2;   // figure upper limit for average character width
	int yChar = tm.tmHeight + tm.tmExternalLeading;                              // text line height.
	int lineGapHeight = yChar / 4;

	int iLine = m_iLine;
	const wchar_t *pLine;
	RECT  rect = { 10, 0, 400, yChar };    // rectangle for our line of text

	while (pLine = pDoc->getLinePtr(iLine++)) {
		pDC->DrawText(pLine, &rect, 0);
		rect.top = rect.bottom + lineGapHeight;
		rect.bottom = rect.top + yChar;
		// if we move outside of our visible range of text then just break.
		if (rect.top > clientRect.bottom) break;
	}
	if (pLine) TRACE1("last line %s\n", pLine);
}


// CMFCAppWinRTView printing


void CMFCAppWinRTView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAppWinRTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCAppWinRTView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCAppWinRTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCAppWinRTView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCAppWinRTView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCAppWinRTView diagnostics

#ifdef _DEBUG
void CMFCAppWinRTView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAppWinRTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAppWinRTDoc* CMFCAppWinRTView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAppWinRTDoc)));
	return (CMFCAppWinRTDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAppWinRTView message handlers


LRESULT  CMFCAppWinRTView::OnGesture(WPARAM wParam, LPARAM lParam)
{

	CMFCAppWinRTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return DefWindowProc(WM_GESTURE, wParam, lParam);

	// Create a structure to populate and retrieve the extra message info.

	//  see https://msdn.microsoft.com/en-us/library/windows/desktop/dd371578(v=vs.85).aspx

	//  see also https://docs.microsoft.com/en-us/windows/desktop/wintouch/legacy-support-for-panning-with-scrollbars
	//  and https://docs.microsoft.com/en-us/windows/desktop/wintouch/guide-multi-touch-gestures

	GESTUREINFO gi = { 0 };

	gi.cbSize = sizeof(GESTUREINFO);

	BOOL     bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);
	BOOL     bHandled = FALSE;
	size_t   maxLines = pDoc->getLineCount();

	if (bResult) {
																					 // now interpret the gesture
		switch (gi.dwID) {
		case GID_BEGIN:
			m_lastXY = gi.ptsLocation;    // These coordinates are always relative to the origin of the screen.
			CloseGestureInfoHandle((HGESTUREINFO)lParam);
			TRACE2("GID_BEGIN: gi.ptsLocation %d, %d\n", gi.ptsLocation.x, gi.ptsLocation.y);
			break;
		case GID_ZOOM:
			// Code for zooming goes here     
			bHandled = TRUE;
			break;
		case GID_PAN:
			// Code for panning goes here
			bHandled = TRUE;

			m_yOverpan -= m_lastY - gi.ptsLocation.y;
			m_lastY = gi.ptsLocation.y;

			if (gi.dwFlags & GF_BEGIN) {
				BeginPanningFeedback(m_hWnd);
				m_yOverpan = 0;
				TRACE2("   gi.dwFlags & GF_BEGIN: gi.ptsLocation %d, %d\n", gi.ptsLocation.x, gi.ptsLocation.y);
			}
			else if (gi.dwFlags & GF_END) {
				EndPanningFeedback(m_hWnd, TRUE);
				m_yOverpan = 0;
				TRACE2("   gi.dwFlags & GF_END: gi.ptsLocation %d, %d\n", gi.ptsLocation.x, gi.ptsLocation.y);
			}

			if (m_si.nPos == m_si.nMin || m_si.nPos >= (m_si.nMax - m_si.nPage)) {
				// we reached the bottom / top, pan
				UpdatePanningFeedback(m_hWnd, 0, m_yOverpan, gi.dwFlags & GF_INERTIA);
			}
			UpdateWindow();
			break;
		case GID_ROTATE:
			// Code for rotation goes here
			bHandled = TRUE;
			break;
		case GID_TWOFINGERTAP:
			// Code for two-finger tap goes here
			bHandled = TRUE;
			{
				LPARAM xy = gi.ptsLocation.x | (gi.ptsLocation.y << 16);
				PostMessage(WM_CONTEXTMENU, (WPARAM)this->m_hWnd, xy);
			}
			break;
		case GID_PRESSANDTAP:
			// Code for roll over goes here
			bHandled = TRUE;
			TRACE2("GID_PRESSANDTAP:: gi.ptsLocation %d, %d\n", gi.ptsLocation.x, gi.ptsLocation.y);
			break;
		default:
			// A gesture was not recognized
			break;
		}
	}
	else {
		DWORD dwErr = GetLastError();
		if (dwErr > 0) {
			//MessageBoxW(hWnd, L"Error!", L"Could not retrieve a GESTUREINFO structure.", MB_OK);
		}
	}

	if (bHandled) {
		return 0;
	}
	else {
		return DefWindowProc(WM_GESTURE, wParam, lParam);
	}

}