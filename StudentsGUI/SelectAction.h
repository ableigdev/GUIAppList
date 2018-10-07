#pragma once


// SelectAction dialog
#include <string>
#include "TypeStream.h"

class SelectAction : public CDialogEx
{
	DECLARE_DYNAMIC(SelectAction)

public:
	SelectAction(CWnd* pParent = NULL);   // standard constructor
	virtual ~SelectAction();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SELECT_ACTION };
#endif

public:
    void setActionName(CString name);
    int getAnswer() const;

private:
    CString m_ActionName;
    int m_Answer;
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonChooseGroup();
    afx_msg void OnBnClickedButtonChooseStudent();
};
