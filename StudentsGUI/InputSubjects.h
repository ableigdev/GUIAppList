#pragma once

#include "List.h"

// InputSubjects dialog

class InputSubjects : public CDialogEx
{
	DECLARE_DYNAMIC(InputSubjects)

public:
	InputSubjects(CWnd* pParent = NULL);   // standard constructor
	virtual ~InputSubjects();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT_SUBJECTS_ADD_MARKS };
#endif

    List<CString> getListOfSubjects() const;
    List<CString>& getListOfSubjects();
    List<float> getListOfMarks() const;
    List<float>& getListOfMarks();

private:
    void setActiveMarkEdit();
    void setActiveSubjectEdit();

private:
    List<CString> m_Subjects;
    List<float> m_Marks;
    CListBox m_SubjectsList;
    CString m_CurrentNameOfTheSubject;
    float m_CurrentValueOfTheMark;
    int m_FontAveChar;
    int m_MaxExtList;
    int m_OldSubjectSelect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonAddMark();
    afx_msg void OnBnClickedButtonAddSubject();
    afx_msg void OnBnClickedButtonCloseInputSubjectWindow();
    afx_msg void OnLbnSelchangeListSubjectInputWindow();
    afx_msg void OnBnClickedButtonDeleteSelectedSubject();
};
