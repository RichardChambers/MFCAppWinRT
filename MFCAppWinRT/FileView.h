
#pragma once

#include "ViewTree.h"

#include <string>


class CFileViewToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CFileView : public CDockablePane
{
// Construction
public:
	CFileView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	// choose either classview_hc.bmp or classview.bmp for the bitmap strip that
	// contains the 7 icons we are using for the images in our tree control.
	// icons are standard size in height and width (15x15 pixels) in the order of:
	//   - main root icon
	//   - tree node icon which can be opened to show nodes beneath it
	//   - folder icon which is used to indicate a folder
	//   - method icon indicating a method of a class
	//   - locked method icon
	//   - member variable icon
	//   - locked member variable icon

	enum IconList { MainRoot = 0, TreeNode = 1, FolderNode = 2, MethodNode = 3, MethodLockedNode = 4, MemberNode = 5, MemberLockedNode = 6 };

	struct ItemToInsert {
		std::wstring  label;
		int           nImage;
		int           nSelectedImage;
	};

// Attributes
protected:

	CViewTree m_wndFileView;
	CImageList m_FileViewImages;
	CFileViewToolBar m_wndToolBar;

protected:
	void FillFileView();
	void AddItemsToPane(CViewTree &m_wndFileView, void *xrayp);

// Implementation
public:
	virtual ~CFileView();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnAddItemsToPane(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()
};

