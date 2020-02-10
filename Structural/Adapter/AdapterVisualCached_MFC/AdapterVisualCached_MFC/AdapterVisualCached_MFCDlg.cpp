
// AdapterVisualCached_MFCDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "AdapterVisualCached_MFC.h"
#include "AdapterVisualCached_MFCDlg.h"
#include "afxdialogex.h"
#include <memory>
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// MY CODE
std::vector<std::shared_ptr<VectorObject>> VectorObjects{
	std::make_shared<VectorRectangle>(10, 10, 100, 100),
	std::make_shared<VectorRectangle>(30, 30, 60, 60)
};

struct LineToPointCachingAdapter
{
	typedef std::vector<Point> Points;

	LineToPointCachingAdapter(Line& line)
	{
		boost::hash<Line> hash;
		line_hash = hash(line);
		if (cache.find(line_hash) != cache.end())
			return;

		static int count = 0;
		TRACE("%d: Generating points for line (with caching)\n", count++);

		int left = min(line.start.x, line.end.x);
		int right = max(line.start.x, line.end.x);
		int top = min(line.start.y, line.end.y);
		int bottom = max(line.start.y, line.end.y);
		int dx = right - left;
		int dy = line.end.y - line.start.y;

		if (dx == 0)
		{
			// Vertical
			for (int y = top; y <= bottom; y++)
				points.emplace_back(Point{ left, y });
		}
		else if (dy == 0)
		{
			for (int x = left; x <= right; ++x)
				points.emplace_back(Point{ x, top });
		}

		cache[line_hash] = points;
	}

	virtual Points::iterator begin() { return cache[line_hash].begin(); }
	virtual Points::iterator end() { return cache[line_hash].end(); }

private:
	Points points;

	size_t line_hash;
	static std::map<size_t, std::vector<Point>> cache;
};

std::map<size_t, std::vector<Point>> LineToPointCachingAdapter::cache;

struct LineToPointAdapter
{
	typedef std::vector<Point> Points;

	LineToPointAdapter(Line& line)
	{
		static int count = 0;
		TRACE("%d: Generating points for line\n", count++);

		int left = min(line.start.x, line.end.x);
		int right = max(line.start.x, line.end.x);
		int top = min(line.start.y, line.end.y);
		int bottom = max(line.start.y, line.end.y);
		int dx = right - left;
		int dy = line.end.y - line.start.y;

		if (dx == 0)
		{
			// Vertical
			for (int y = top; y <= bottom; y++)
				points.emplace_back(Point{ left, y });
		}
		else if (dy == 0)
		{
			for (int x = left; x <= right; ++x)
				points.emplace_back(Point{ x, top });
		}
	}

	virtual Points::iterator begin() { return points.begin(); }
	virtual Points::iterator end() { return points.end(); }

private:
	Points points;
};
// !MY CODE

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// AdapterVisualCachedMFCDlg dialog



AdapterVisualCachedMFCDlg::AdapterVisualCachedMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADAPTERVISUALCACHED_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void AdapterVisualCachedMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(AdapterVisualCachedMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// AdapterVisualCachedMFCDlg message handlers

BOOL AdapterVisualCachedMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void AdapterVisualCachedMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void AdapterVisualCachedMFCDlg::OnPaint()
{
	// MY CODE
	CPaintDC dc(this); // device context for painting
	// !MY CODE

	if (IsIconic())
	{
		// I COMMENTED OUT
		//CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		// MY CODE
		for (auto& o : VectorObjects)
		{
			for (auto& l : *o)
			{
				//LineToPointAdapter lpo{ l };
				LineToPointCachingAdapter lpo{ l };
				DrawPoints(dc, lpo.begin(), lpo.end());
			}
		}
		// !MY CODE

		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR AdapterVisualCachedMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

