
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
