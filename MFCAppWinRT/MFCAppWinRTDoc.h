
// MFCAppWinRTDoc.h : interface of the CMFCAppWinRTDoc class
//


#pragma once

#include <vector>

class CMFCAppWinRTDoc : public CDocument
{
protected: // create from serialization only
	CMFCAppWinRTDoc();
	DECLARE_DYNCREATE(CMFCAppWinRTDoc)

// Attributes
public:

// Operations
public:
	const wchar_t * getLinePtr(int iLine);
	size_t   getLineCount(void) { return myList.size(); }

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCAppWinRTDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector <std::wstring > myList;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
