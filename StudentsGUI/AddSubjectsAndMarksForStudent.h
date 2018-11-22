#pragma once

#include "List.h"
#include "Student.h"
#include "Iterator.h"

// AddSubjectsAndMarksForStudent dialog

class AddSubjectsAndMarksForStudent : public CDialogEx
{
	DECLARE_DYNAMIC(AddSubjectsAndMarksForStudent)

public:
	AddSubjectsAndMarksForStudent(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddSubjectsAndMarksForStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SUBJECTS_FOR_STUDENT };
#endif

    void setSubjects(List<CString>* subjects);
    void setMarks(List<float>* marks);
    void setStudent(Student* student);

private:
    template <typename TypeOfList>
    void for_each_listbox(Iterator<TypeOfList> list, CListBox& listbox, int& oldSelect, int& selected);

private:
    List<CString>* m_Subjects;
    List<float>* m_Marks;
    Student* m_Student;
    CListBox m_ListSubjects;
    CListBox m_ListMarks;
    CString m_NameOfTheSubject;
    CString m_ValueOfTheMark;
    int m_OldSubjectSelect;
    int m_OldMarkSelect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonCloseWindow();
    afx_msg void OnBnClickedButtonAddStudentSubject();
    afx_msg void OnEnChangeEditFindSubject();
    afx_msg void OnLbnSelchangeListSubjects();
    afx_msg void OnEnChangeEditFindMark();
    afx_msg void OnLbnSelchangeListMarks();
};
