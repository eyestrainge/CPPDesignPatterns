
// AdapterVisualCached_MFCDlg.h : header file
//

#pragma once

#include "Geometry.h"


// AdapterVisualCachedMFCDlg dialog
class AdapterVisualCachedMFCDlg : public CDialogEx
{
// Construction
public:
	AdapterVisualCachedMFCDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADAPTERVISUALCACHED_MFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// MY CODE
	void DrawPoints(CPaintDC& dc, std::vector<Point>::iterator begin, std::vector<Point>::iterator end)
	{
		for (auto i = begin; i != end; ++i)
			dc.SetPixel(i->x, i->y, 0);
	}
	// !MY CODE

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
