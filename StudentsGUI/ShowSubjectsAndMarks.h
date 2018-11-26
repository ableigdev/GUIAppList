#pragma once

#include "List.h"
#include "Student.h"

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
    void setRecordBook(List<std::pair<CString, float>>* recordBook);
    void setStudent(Student* student);

private:
    List<std::pair<CString, float>>* m_RecordBook;
    Student* m_Student;
    CListBox m_RecordBookListBox;
    CListBox m_MarkListBox;
    CString m_FindRecord;
    int m_FontAveChar;
    int m_MaxExtList;
    int m_OldSubjectSelect;
    int m_OldMarkSelect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonCloseShowSubjectWindow();
    afx_msg void OnEnChangeEditFindSubjectsInShowWindow();
    afx_msg void OnLbnSelchangeListStudentsMarks();
    afx_msg void OnBnClickedButtonDeleteSubjectFromRecordbook();
    afx_msg void OnLbnSelchangeListStudentsSubjectsInShowWindow();
};
