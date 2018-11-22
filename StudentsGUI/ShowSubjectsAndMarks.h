#pragma once

#include "List.h"

// ShowSubjectsAndMarks dialog

class ShowSubjectsAndMarks : public CDialogEx
{
	DECLARE_DYNAMIC(ShowSubjectsAndMarks)

public:
	ShowSubjectsAndMarks(CWnd* pParent = NULL);   // standard constructor
	virtual ~ShowSubjectsAndMarks();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SHOW_SUBJECTS_AND_MARKS };
#endif
    void setRecordBook(List<std::pair<CString*, float*>>* recordBook);

private:
    List<std::pair<CString*, float*>>* m_RecordBook;
    CListBox m_RecordBookListBox;
    CString m_FindRecord;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEditFindSubjectsAndMarks();
    afx_msg void OnLbnSelchangeListSubjectsAndMarks();
    afx_msg void OnBnClickedButtonCloseShowSubjectWindow();
};
