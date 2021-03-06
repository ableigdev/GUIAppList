#pragma once

#include "NameList.h"
#include "Student.h"

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

    void setChangeFlag(int flag);
    void setCurrentBranchIndex(int index);
    void setStudent(Student* student);
    void setGroup(NameList<Student>* group);
    void setFaculty(NameList<NameList<Student>>* faculty);
    void setListBoxGroupList(CListBox*);
    CListBox* getListBoxGroupList() const;
    int getCurrentSelectedGroup() const;

private:
    void setActiveSurname();
    bool checkConstruction();
    bool addStudent();
    void setBeginState(NameList<Student>*);

private:
    CComboBox m_ComboGroupList;
    CListBox* m_ListBoxGroupList;
    NameList<Student>* m_Group;
    NameList<NameList<Student>>* m_Faculty;
    Student* m_Student;
    Student m_WorkStudent;
    int m_ChangeFlag;
    bool m_IsModify;
    int m_CurrentGroupIndex;
    CString m_Surname;
    CString m_Name;
    CString m_Lastname;
    short m_BirthYear;
    float m_AverageGrade;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedStudentButtonNext();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
};
