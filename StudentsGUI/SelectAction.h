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
    void setActionName(const std::basic_string<TYPESTRING>& name);
    void setGroupName(const std::basic_string<TYPESTRING>& name);
    void setStudentName(const std::basic_string<TYPESTRING>& name);

private:
    std::basic_string<TYPESTRING> m_ActionName {};
    std::basic_string<TYPESTRING> m_GroupName {};
    std::basic_string<TYPESTRING> m_StudentName {};
    CButton* m_SelectGroup;
    CButton* m_SelectStudent;
    
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
