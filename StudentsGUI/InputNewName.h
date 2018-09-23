#pragma once


// InputNewName dialog
#include "TypeStream.h"
#include <string>

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
    void setName(std::basic_string<TYPESTRING>* name);
    std::basic_string<TYPESTRING>* getName() const;

private:
    CString m_Title;
    CString	*m_CStringName;
    std::basic_string<TYPESTRING>* m_Name;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
};
