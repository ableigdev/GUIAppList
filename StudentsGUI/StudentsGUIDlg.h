
// StudentsGUIDlg.h : header file
//

#pragma once
#include "InputNewName.h"
#include "InputStudentInformation.h"
#include "Student.h"
#include "NameList.h"
#include "SelectAction.h"

// CStudentsGUIDlg dialog
class CStudentsGUIDlg : public CDialogEx
{
// Construction
public:
	CStudentsGUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTSGUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


private:
    InputNewName m_InputNewName;
    InputStudentInformation m_InputStudInform;
    NameList<Student>* m_CurrentGroup;
    NameList <NameList<Student>> m_Faculty;
    Student* m_Student;
    SelectAction m_SelectAction;

    int m_FontAveChar;
    int m_MaxExtListStud;
    int m_MaxExtListGroup;
    int m_OldStudSelect;
    int m_OldGroupSelect;

    CListBox m_ListStudInfo;
    CListBox m_ListStudents;
    CListBox m_ListGroups;

    CString m_StudentName;
    CString m_GroupName;
// Implementation
protected:
	HICON m_hIcon;
    
    void deleteStudentList();
    void deleteStudentInformationList();
    void deleteAllLists();
    void deleteGroupList();
    void deleteSelectedStudent();
    void deleteSelectedGroup();

    void changeSelectedStudent();
    void changeSelectedGroup();

    void setButtonState(WORD wID[], WORD len, BOOL state);
    
    BOOL setStudentActions(BOOL state);
    void setFacultyActions(BOOL state);
    BOOL setGroupActions(BOOL state);
    void setAddFacultyActions(BOOL state);
    void setSelectedActions(BOOL state);

    void disableFaculty();
    
    void showStudent();
    void showStudentInformation(const Student& student);
    void showGroups();
    
    int setNewSelect(CListBox& listBox, int& maxExtCx);
    int changeItem(CListBox& listBox, int& maxExtCx, const std::basic_string<TYPESTRING>& name); // TODO: Need to refactor

    void showString(Student& student); 
    void showString(NameList<Student>& group);

    void CorrectListHScrl(CListBox &ListBox);
    void CorrectListHScrlPart(CListBox &ListBox, int &MaxExtCx, int Index = 0);
    void CorrectListHScrlDel(CListBox &ListBox, int &MaxExtCx, int Index);

    void deleteStudent();
    void modifyStudent();

    inline int getStudentSelect() const;
    inline int getGroupSelect() const;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonFacultyAdd();
    afx_msg void OnBnClickedButtonFacultyChange();
    afx_msg void OnBnClickedButtonFacultyGet();
    afx_msg void OnBnClickedButtonFacultyDelete();
    afx_msg void OnBnClickedButtonAddStudents();
    afx_msg void OnBnClickedButtonDelete();
    afx_msg void OnBnClickedButtonDeleteAllStudents();
    afx_msg void OnBnClickedButtonAddGroup();
    afx_msg void OnBnClickedButtonDeleteAllGroup();
    afx_msg void OnEnChangeEditStudent();
    afx_msg void OnLbnSelchangeListStudents();
    afx_msg void OnEnChangeEditGroup();
    afx_msg void OnLbnSelchangeListGroups();
    afx_msg void OnBnClickedButtonChange();
};
