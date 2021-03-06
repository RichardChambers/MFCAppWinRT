
#pragma once

#include "ViewTree.h"

#include <string>


class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();

	// ADD_ON: enumeration listing the various types of tree control icons which
	//         correspond to the position of a control in the tree.
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

	// ADD_ON: struct used to contain the necessary data for a node in the tree control.
	struct ItemToInsert {
		std::wstring  label;            // text to be displayed with the node.
		int           nImage;           // zero based offset of the node's icon in the image, one of enum IconList above.
		int           nSelectedImage;   // zero based offset of the node's icon in the image, one of enum IconList above.
	};

protected:
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	UINT m_nCurrSort;

	void FillClassView();

	// ADD_ON: function for filling in the ClassView pane using an array of the
	//         struct ItemToInsert above. array is terminated by an entry with
	//         all zeros as in { _T(""), 0, 0 }
	void AddItemsToPane(CViewTree &xwndClassView, void *xrayp);

// Overrides
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClassAddMemberFunction();
	afx_msg void OnClassAddMemberVariable();
	afx_msg void OnClassDefinition();
	afx_msg void OnClassProperties();
	afx_msg void OnNewFolder();
	// ADD_ON: message handler for the WM_APP message containing an array of the
	//         struct ItemToInsert above. Uses method AddItemsToPane().
	afx_msg LRESULT OnAddItemsToPane(WPARAM, LPARAM);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnSort(UINT id);
	afx_msg void OnUpdateSort(CCmdUI* pCmdUI);

	DECLARE_MESSAGE_MAP()
};

