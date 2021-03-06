
// MFCAppWinRTDoc.cpp : implementation of the CMFCAppWinRTDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCAppWinRT.h"
#endif

#include "MainFrm.h"
#include "MFCAppWinRTDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCAppWinRTDoc

IMPLEMENT_DYNCREATE(CMFCAppWinRTDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCAppWinRTDoc, CDocument)
END_MESSAGE_MAP()


// CMFCAppWinRTDoc construction/destruction

CMFCAppWinRTDoc::CMFCAppWinRTDoc()
{
	// TODO: add one-time construction code here

}

CMFCAppWinRTDoc::~CMFCAppWinRTDoc()
{
}

BOOL CMFCAppWinRTDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	myList.clear();
	myList = { L"anteater",  L"bear",      L"cougar",
		L"dingo",     L"elephant",  L"falcon",
		L"gazelle",   L"hyena",     L"iguana",
		L"jackal",    L"kangaroo",  L"llama",
		L"moose",     L"newt",      L"octopus",
		L"penguin",   L"quail",     L"rat",
		L"squid",     L"tortoise",  L"urus",
		L"vole",      L"walrus",    L"xylophone",
		L"yak",       L"zebra"
		};

	CMainFrame *p = dynamic_cast <CMainFrame *> (AfxGetMainWnd());

	if (p) {
		p->SendMessageToOutputWnd(WM_APP, COutputWnd::OutputBuild, (LPARAM)_T("this is a test from OnNewDocument()."));
	}
	return TRUE;
}




// CMFCAppWinRTDoc serialization

void CMFCAppWinRTDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCAppWinRTDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCAppWinRTDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCAppWinRTDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCAppWinRTDoc diagnostics

#ifdef _DEBUG
void CMFCAppWinRTDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCAppWinRTDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

const wchar_t * CMFCAppWinRTDoc::getLinePtr(int iLine)
{
	if (iLine < myList.size())
		return myList[iLine].c_str();
	else
		return nullptr;
}

// CMFCAppWinRTDoc commands
