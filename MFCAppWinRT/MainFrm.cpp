
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MFCAppWinRT.h"

#include "MainFrm.h"

// ADD_ON: include files for using the concurrency namespace.
//#include <experimental\resumable>
#include <pplawait.h>

#include <future>

#pragma comment(lib, "windowsapp")
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Web.Syndication.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_WM_SETTINGCHANGE()
	ON_MESSAGE(WM_GESTURE, &CMainFrame::OnGesture)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

// ADD_ON: this is the content to be put into the ClassView tree pane.
//         this is a tree structure.
CClassView::ItemToInsert xray2[] = {
	{ _T("CFakeMainProject"), CClassView::MainRoot, CClassView::MainRoot },
		{ _T("CFakeAboutDlg"), CClassView::TreeNode, CClassView::TreeNode },
			{ _T("CFakeAboutDlg()"), CClassView::MethodNode, CClassView::MethodNode },
		{ _T("CFakeApp"), CClassView::TreeNode, CClassView::TreeNode },
			{ _T("CFakeApp()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("InitInstance()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("OnAppAbout()"), CClassView::MethodNode, CClassView::MethodNode },
		{ _T("CFakeAppDoc"), CClassView::TreeNode, CClassView::TreeNode },
			{ _T("CFakeAppDoc()"), CClassView::MethodLockedNode, CClassView::MethodLockedNode },
			{ _T("~CFakeAppDoc()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("OnNewDocument()"), CClassView::MethodNode, CClassView::MethodNode },
		{ _T("CFakeAppView"), CClassView::TreeNode, CClassView::TreeNode },
			{ _T("CFakeAppView()"), CClassView::MethodLockedNode, CClassView::MethodLockedNode },
			{ _T("~CFakeAppView()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("GetDocument()"), CClassView::MethodNode, CClassView::MethodNode },
		{ _T("CFakeAppFrame"), CClassView::TreeNode, CClassView::TreeNode },
			{ _T("CFakeAppFrame()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("~CFakeAppFrame()"), CClassView::MethodNode, CClassView::MethodNode },
			{ _T("m_wndMenuBar"), CClassView::MemberLockedNode, CClassView::MemberLockedNode },
			{ _T("m_wndToolBar"), CClassView::MemberLockedNode, CClassView::MemberLockedNode },
			{ _T("m_wndStatusBar"), CClassView::MemberLockedNode, CClassView::MemberLockedNode },
		{ _T("Globals"), CClassView::FolderNode, CClassView::FolderNode },
			{ _T("theFakeApp"), CClassView::MemberNode, CClassView::MemberNode },
	{ _T(""), 0, 0 }
};

CClassView::ItemToInsert xray3[] = {
	{ _T("CAdditionalDelay"), CClassView::TreeNode, CClassView::TreeNode },
		{ _T("CAdditionalDelayMethod()"), CClassView::MethodNode, CClassView::MethodNode },
	{ _T(""), 0, 0 }
};

// a simple function that uses with concurrency::create_task()
// to create a task that simulates a lengthy task that is
// run on a different thread.
concurrency::task<int> mySleepTaskAsync()
{
	return concurrency::create_task([]() {
		Sleep(7000);
		return 5;
	});

}

// a simple function that when used with concurrency::create_task()
// can be used with co_await to simulate a lengthy task that is
// run on a different thread.
int mySleepTaskAsyncInt()
{
		Sleep(7000);
		return 5;
}

// An example of a function that can be used with co_await which
// uses the C++11 Standard Library with the std::packaged_task<>
// with the get_future() method to obtain a std::future<> that can
// be used with co_await.
std::future<int> mySleepTaskStdFutureInt(int a)
{
	// create the task to prepare it for running.
	std::packaged_task<int(int)> task([](int kk) {
		Sleep(7000);
		return 455 * kk;
	});

	// start the task running and return the future
	return task(a), task.get_future();
}



#include <experimental/generator>

std::experimental::generator<int> makeSomeInts(int kCount)
{
	for (int i = 0; i < kCount; i++) {
		co_yield i;
	}
}

winrt::Windows::Foundation::IAsyncAction myTaskMain(CMainFrame *p)
{
	// See https://channel9.msdn.com/events/Build/2018/BRK2425?term=uwp%20C++&lang-en=true

//	winrt::apartment_context ui_thread; // Capture calling context.

	winrt::Windows::Foundation::Uri uri(L"http://kennykerr.ca/feed");
	winrt::Windows::Web::Syndication::SyndicationClient client;
	winrt::Windows::Web::Syndication::SyndicationFeed feed = co_await client.RetrieveFeedAsync(uri);

	co_await winrt::resume_background();  // switch context to background thread to make UI responsive.

	int jkjk = co_await mySleepTaskStdFutureInt(3);

	int jj = co_await concurrency::create_task(mySleepTaskAsyncInt);  // test of rolling my own async function for use with co_await.

	int jj2 = co_await mySleepTaskAsync();        // a different way of doing an async function

	int jj3 = co_await concurrency::create_task([]() {      // still another way of an async function with a lambda
					Sleep(7000);
					return 5;
				});

	auto t1 = co_await std::async(std::launch::async, mySleepTaskAsyncInt);

	for (int kkk : makeSomeInts(10)) {
		int lll = kkk + 5;
	}

//	Sleep(15000);
//	co_await ui_thread; // Switch back to calling context.

	for (winrt::Windows::Web::Syndication::SyndicationItem item : feed.Items())
	{
		winrt::hstring title = item.Title().Text();
		p->SendMessageToOutputWnd(WM_APP, COutputWnd::OutputBuild, (LPARAM)title.c_str());  // print a string to an output window in the output pane.
//		p->m_wndOutput.AddTextLine(COutputWnd::OutputBuild, title.c_str());  // print a string to an output window in the output pane.
	}
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// Allow user-defined toolbars operations:
	InitUserToolbars(nullptr, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these five lines if you don't want the toolbar and menubar to be dockable
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Load menu item image (not placed on any standard toolbars):
	CMFCToolBar::AddToolBarForImageCollection(IDR_MENU_IMAGES, theApp.m_bHiColorIcons ? IDB_MENU_IMAGES_24 : 0);

	// create docking windows
	if (!CreateDockingWindows())
	{
		TRACE0("Failed to create docking windows\n");
		return -1;
	}

	m_wndFileView.EnableDocking(CBRS_ALIGN_ANY);
	m_wndClassView.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndFileView);
	CDockablePane* pTabbedBar = nullptr;
	m_wndClassView.AttachToTabWnd(&m_wndFileView, DM_SHOW, TRUE, &pTabbedBar);
	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);
	m_wndProperties.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndProperties);


	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// enable quick (Alt+drag) toolbar customization
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == nullptr)
	{
		// load user-defined toolbar images
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// enable menu personalization (most-recently used commands)
	// TODO: define your own basic commands, ensuring that each pulldown menu has at least one basic command.
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_FILE_NEW);
	lstBasicCommands.AddTail(ID_FILE_OPEN);
	lstBasicCommands.AddTail(ID_FILE_SAVE);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_EDIT_CUT);
	lstBasicCommands.AddTail(ID_EDIT_PASTE);
	lstBasicCommands.AddTail(ID_EDIT_UNDO);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_SORTING_SORTALPHABETIC);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYTYPE);
	lstBasicCommands.AddTail(ID_SORTING_SORTBYACCESS);
	lstBasicCommands.AddTail(ID_SORTING_GROUPBYTYPE);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	// ADD_ON: use the concurrency namespace threading to create the ClassView content.
	//         This spins off a task that waits five seconds then posts a message to the
	//         ClassView tree pane with the content to post into that pane.
	//         Then we spin off a second task to follow with an additional node to the displayed tree.
	concurrency::create_task([this]() { Sleep(5000);  this->SendMessageToClassView(WM_APP, 1, (LPARAM)xray2); }); 
	concurrency::create_task([this]() { Sleep(10000);  this->SendMessageToClassView(WM_APP, 1, (LPARAM)xray3); });
#if 1
	m_wndOutput.AddTextLine(COutputWnd::OutputBuild, _T("Calling myTaskMain() "));
	myTaskMain(this);
#else
	concurrency::create_task([this]() {
		winrt::init_apartment();

		Sleep(5000);

		winrt::Windows::Foundation::Uri uri(L"http://kennykerr.ca/feed");
		winrt::Windows::Web::Syndication::SyndicationClient client;
		winrt::Windows::Web::Syndication::SyndicationFeed feed = client.RetrieveFeedAsync(uri).get();
		for (winrt::Windows::Web::Syndication::SyndicationItem item : feed.Items())
		{
			winrt::hstring title = item.Title().Text();
			this->SendMessageToOutputWnd(WM_APP, COutputWnd::OutputBuild, (LPARAM)title.c_str());  // print a string to an output window in the output pane.
		}
		winrt::uninit_apartment();
	});
#endif

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;

	// Create class view
	CString strClassView;
	bNameValid = strClassView.LoadString(IDS_CLASS_VIEW);
	ASSERT(bNameValid);
	if (!m_wndClassView.Create(strClassView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_CLASSVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Class View window\n");
		return FALSE; // failed to create
	}

	// Create file view
	CString strFileView;
	bNameValid = strFileView.LoadString(IDS_FILE_VIEW);
	ASSERT(bNameValid);
	if (!m_wndFileView.Create(strFileView, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_FILEVIEW, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create File View window\n");
		return FALSE; // failed to create
	}

	// Create output window
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Output window\n");
		return FALSE; // failed to create
	}

	// Create properties window
	CString strPropertiesWnd;
	bNameValid = strPropertiesWnd.LoadString(IDS_PROPERTIES_WND);
	ASSERT(bNameValid);
	if (!m_wndProperties.Create(strPropertiesWnd, this, CRect(0, 0, 200, 200), TRUE, ID_VIEW_PROPERTIESWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties window\n");
		return FALSE; // failed to create
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hFileViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_FILE_VIEW_HC : IDI_FILE_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndFileView.SetIcon(hFileViewIcon, FALSE);

	HICON hClassViewIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_CLASS_VIEW_HC : IDI_CLASS_VIEW), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndClassView.SetIcon(hClassViewIcon, FALSE);

	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	HICON hPropertiesBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PROPERTIES_WND_HC : IDI_PROPERTIES_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndProperties.SetIcon(hPropertiesBarIcon, FALSE);

}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// base class does the real work

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// enable customization button for all user toolbars
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != nullptr)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
}


LRESULT  CMainFrame::OnGesture(WPARAM wParam, LPARAM lParam)
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