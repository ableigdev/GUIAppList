#pragma once


// InputStudentInformation dialog

class InputStudentInformation : public CDialogEx
{
	DECLARE_DYNAMIC(InputStudentInformation)

public:
	InputStudentInformation(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputStudentInformation();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
