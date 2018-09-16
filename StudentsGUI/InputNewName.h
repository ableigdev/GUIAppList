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

    void setTitle(CString title);
    CString getTitle() const;
    void setName(CString* name);
    CString* getName() const;

private:
    CString m_Title;
    CString	*m_Name;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
};
