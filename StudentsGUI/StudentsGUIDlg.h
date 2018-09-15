
// StudentsGUIDlg.h : header file
//

#pragma once
#include "InputNewName.h"

// CStudentsGUIDlg dialog
class CStudentsGUIDlg : public CDialogEx
{
// Construction
public:
	CStudentsGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTSGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
    InputNewName Input;

    void setButtonState(WORD wID[], WORD len, BOOL state);
    void setFacultyActions(BOOL state);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonFacultyAdd();
};
