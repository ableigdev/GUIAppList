// InputSubjects.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputSubjects.h"
#include "afxdialogex.h"


// InputSubjects dialog

IMPLEMENT_DYNAMIC(InputSubjects, CDialogEx)

InputSubjects::InputSubjects(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INPUT_SUBJECTS_ADD_MARKS, pParent)
{

}

InputSubjects::~InputSubjects()
{
}

void InputSubjects::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MARK, m_CurrentValueOfTheMark);
    DDV_MinMaxFloat(pDX, m_CurrentValueOfTheMark, 0.f, 5.f);

    DDX_Text(pDX, IDC_EDIT_SUBJECT, m_CurrentNameOfTheSubject);
    m_CurrentNameOfTheSubject.TrimLeft();
    m_CurrentNameOfTheSubject.TrimRight();
}


BEGIN_MESSAGE_MAP(InputSubjects, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD_MARK, &InputSubjects::OnBnClickedButtonAddMark)
    ON_BN_CLICKED(IDC_BUTTON_ADD_SUBJECT, &InputSubjects::OnBnClickedButtonAddSubject)
    ON_BN_CLICKED(IDC_BUTTON_CLOSE_INPUT_SUBJECT_WINDOW, &InputSubjects::OnBnClickedButtonCloseInputSubjectWindow)
END_MESSAGE_MAP()


// InputSubjects message handlers
void InputSubjects::setActiveMarkEdit()
{
    CWnd* wnd = GetDlgItem(IDC_EDIT_MARK);
    wnd->SetFocus();
    ((CEdit*)(wnd))->SetSel(0, 2);
}

void InputSubjects::setActiveSubjectEdit()
{
    CWnd* wnd = GetDlgItem(IDC_EDIT_SUBJECT);
    wnd->SetFocus();
    ((CEdit*)(wnd))->SetSel(0, m_CurrentNameOfTheSubject.GetLength());
}

void InputSubjects::OnBnClickedButtonAddMark()
{
    if (UpdateData() == TRUE)
    {
        if (!m_Marks.findValue(m_CurrentValueOfTheMark))
        {
            m_Marks.pushInSortList(m_CurrentValueOfTheMark);
        }
        else
        {
            MessageBox(__TEXT("The mark exists in the list"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
        }
    }
    setActiveMarkEdit();
}

void InputSubjects::OnBnClickedButtonAddSubject()
{
    UpdateData(TRUE);
    if (!m_CurrentNameOfTheSubject.IsEmpty())
    {
        if (!m_Subjects.findValue(m_CurrentNameOfTheSubject))
        {
            m_Subjects.pushInSortList(m_CurrentNameOfTheSubject);
        }
        else
        {
            MessageBox(__TEXT("The subject exists in the list"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
        }
    }
    else
    {
        MessageBox(__TEXT("You can't input the empty string!"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    }
    setActiveSubjectEdit();
}

BOOL InputSubjects::OnInitDialog()
{
    SetDefID(IDC_BUTTON_ADD_MARK);
    m_CurrentNameOfTheSubject = __TEXT("");
    m_CurrentValueOfTheMark = 0;
    CDialogEx::OnInitDialog();

    return FALSE;
}

List<CString> InputSubjects::getListOfSubjects() const
{
    return m_Subjects;
}

List<CString>& InputSubjects::getListOfSubjects()
{
    return m_Subjects;
}

List<float> InputSubjects::getListOfMarks() const
{
    return m_Marks;
}

List<float>& InputSubjects::getListOfMarks() 
{
    return m_Marks;
}

void InputSubjects::OnBnClickedButtonCloseInputSubjectWindow()
{
    CDialogEx::OnOK();
}
