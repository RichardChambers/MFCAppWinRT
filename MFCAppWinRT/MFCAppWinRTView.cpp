
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

CMFCAppWinRTView::CMFCAppWinRTView()
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

void CMFCAppWinRTView::OnDraw(CDC* /*pDC*/)
{
	CMFCAppWinRTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
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

	// Create a structure to populate and retrieve the extra message info.

	//  see https://msdn.microsoft.com/en-us/library/windows/desktop/dd371578(v=vs.85).aspx

	GESTUREINFO gi = { 0 };

	gi.cbSize = sizeof(GESTUREINFO);

	BOOL bResult = GetGestureInfo((HGESTUREINFO)lParam, &gi);
	BOOL bHandled = FALSE;

	if (bResult) {
		// now interpret the gesture
		switch (gi.dwID) {
		case GID_ZOOM:
			// Code for zooming goes here     
			bHandled = TRUE;
			break;
		case GID_PAN:
			// Code for panning goes here
			bHandled = TRUE;
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