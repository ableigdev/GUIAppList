// AddSubjectsAndMarksForStudent.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "AddSubjectsAndMarksForStudent.h"
#include "afxdialogex.h"
#include "constants.h"
#include "CommonFunctions.h"


// AddSubjectsAndMarksForStudent dialog

IMPLEMENT_DYNAMIC(AddSubjectsAndMarksForStudent, CDialogEx)

AddSubjectsAndMarksForStudent::AddSubjectsAndMarksForStudent(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD_SUBJECTS_FOR_STUDENT, pParent)
{

}

AddSubjectsAndMarksForStudent::~AddSubjectsAndMarksForStudent()
{
}

void AddSubjectsAndMarksForStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LIST_SUBJECTS, m_ListSubjects);
    DDX_Control(pDX, IDC_LIST_MARKS, m_ListMarks);
    DDX_Text(pDX, IDC_EDIT_FIND_SUBJECT, m_NameOfTheSubject);
    DDX_Text(pDX, IDC_EDIT_FIND_MARK, m_ValueOfTheMark);
}


BEGIN_MESSAGE_MAP(AddSubjectsAndMarksForStudent, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CLOSE_WINDOW, &AddSubjectsAndMarksForStudent::OnBnClickedButtonCloseWindow)
    ON_BN_CLICKED(IDC_BUTTON_ADD_STUDENT_SUBJECT, &AddSubjectsAndMarksForStudent::OnBnClickedButtonAddStudentSubject)
    ON_EN_CHANGE(IDC_EDIT_FIND_SUBJECT, &AddSubjectsAndMarksForStudent::OnEnChangeEditFindSubject)
    ON_LBN_SELCHANGE(IDC_LIST_SUBJECTS, &AddSubjectsAndMarksForStudent::OnLbnSelchangeListSubjects)
    ON_EN_CHANGE(IDC_EDIT_FIND_MARK, &AddSubjectsAndMarksForStudent::OnEnChangeEditFindMark)
    ON_LBN_SELCHANGE(IDC_LIST_MARKS, &AddSubjectsAndMarksForStudent::OnLbnSelchangeListMarks)
END_MESSAGE_MAP()


// AddSubjectsAndMarksForStudent message handlers

BOOL AddSubjectsAndMarksForStudent::OnInitDialog()
{
    UpdateData(FALSE);
    SetDefID(IDC_STATIC_CHOOSE_SUBJECT);
    TEXTMETRIC tm;
    CDC* pDC = m_ListSubjects.GetDC();
    CFont *pOldFont = pDC->SelectObject(m_ListSubjects.GetFont());
    pDC->GetTextMetrics(&tm);
    pDC->SelectObject(pOldFont);
    m_ListSubjects.ReleaseDC(pDC);
    m_FontAveChar = tm.tmAveCharWidth;
    m_MaxExtList = 0;

    if (!m_Subjects->isEmpty() && !m_Marks->isEmpty())
    {
        for (size_t i = 0; i < m_Subjects->getSize(); ++i, ++*m_Subjects)
        {
            common::CorrectScroll::correctListHScrlPart(m_ListSubjects, m_MaxExtList, m_FontAveChar, m_ListSubjects.AddString((LPCTSTR)m_Subjects->getReferencesCurrentData()));
        }
        for (size_t i = 0; i < m_Marks->getSize(); ++i, ++*m_Marks)
        {
            CString buf;
            buf.Format(__TEXT("%4.2f"), m_Marks->getReferencesCurrentData());
            m_ListMarks.AddString(buf);
        }
    }

    m_OldMarkSelect = LB_ERR;
    m_OldSubjectSelect = LB_ERR;

    CDialogEx::OnInitDialog();
    return FALSE;
}

void AddSubjectsAndMarksForStudent::OnBnClickedButtonCloseWindow()
{
    CDialogEx::OnOK();
}

void AddSubjectsAndMarksForStudent::OnBnClickedButtonAddStudentSubject()
{
    if (m_ListSubjects.GetCurSel() != LB_ERR && m_ListMarks.GetCurSel() != LB_ERR)
    {
        m_Student->setRecordBookPair(m_Subjects->getReferencesCurrentData(), m_Marks->getReferencesCurrentData());
    }
    else
    {
        MessageBox(__TEXT("Choose elements from both lists!"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    }
}

void AddSubjectsAndMarksForStudent::setSubjects(List<CString>* subjects)
{
    m_Subjects = subjects;
}

void AddSubjectsAndMarksForStudent::setMarks(List<float>* marks)
{
    m_Marks = marks;
}

void AddSubjectsAndMarksForStudent::setStudent(Student* student)
{
    m_Student = student;
}

void AddSubjectsAndMarksForStudent::OnEnChangeEditFindSubject()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_FIND_SUBJECT)))->GetLine(0, buffer)] = 0;

    if ((search = m_ListSubjects.FindString(-1, buffer)) != LB_ERR)
    {
        m_ListSubjects.SetCurSel(search);
        OnLbnSelchangeListSubjects();
    }
}

void AddSubjectsAndMarksForStudent::OnLbnSelchangeListSubjects()
{
    int selected = m_ListSubjects.GetCurSel();
    if (selected != LB_ERR && selected != m_OldSubjectSelect)
    {
        Iterator<CString> iter(m_Subjects);
        common::for_each_listbox(iter, m_ListSubjects, m_OldSubjectSelect, selected);
    }
}

void AddSubjectsAndMarksForStudent::OnEnChangeEditFindMark()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_FIND_MARK)))->GetLine(0, buffer)] = 0;

    if ((search = m_ListMarks.FindString(-1, buffer)) != LB_ERR)
    {
        m_ListMarks.SetCurSel(search);
        OnLbnSelchangeListMarks();
    }
}

void AddSubjectsAndMarksForStudent::OnLbnSelchangeListMarks()
{
    int selected = m_ListMarks.GetCurSel();
    if (selected != LB_ERR && selected != m_OldMarkSelect)
    {
        Iterator<float> iter(m_Marks);
        common::for_each_listbox(iter, m_ListMarks, m_OldMarkSelect, selected);
    }
}
