#pragma once


// InputNewName dialog

class InputNewName : public CDialogEx
{
	DECLARE_DYNAMIC(InputNewName)

public:
	InputNewName(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputNewName();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAME };
#endif

    CString Title;
    CString	*m_Name;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
