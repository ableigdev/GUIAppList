// InputSubjects.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputSubjects.h"
#include "afxdialogex.h"
#include "CommonFunctions.h"
#include "Iterator.h"


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
    DDX_Control(pDX, IDC_LIST_SUBJECT_INPUT_WINDOW, m_SubjectsList);
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
    ON_LBN_SELCHANGE(IDC_LIST_SUBJECT_INPUT_WINDOW, &InputSubjects::OnLbnSelchangeListSubjectInputWindow)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_SELECTED_SUBJECT, &InputSubjects::OnBnClickedButtonDeleteSelectedSubject)
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
            common::CorrectScroll::correctListHScrlPart(m_SubjectsList, m_MaxExtList, m_FontAveChar, m_SubjectsList.AddString((LPCTSTR)m_CurrentNameOfTheSubject));
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
    UpdateData(FALSE);
    m_SubjectsList.ResetContent();
    TEXTMETRIC tm;
    CDC* pDC = m_SubjectsList.GetDC();
    CFont *pOldFont = pDC->SelectObject(m_SubjectsList.GetFont());
    pDC->GetTextMetrics(&tm);
    pDC->SelectObject(pOldFont);
    m_SubjectsList.ReleaseDC(pDC);
    m_FontAveChar = tm.tmAveCharWidth;
    m_CurrentNameOfTheSubject = __TEXT("");
    m_CurrentValueOfTheMark = 0;
    m_MaxExtList = 0;
    m_OldSubjectSelect = LB_ERR;
    SetDefID(IDC_STATIC_ADD_DATA);
    GetDlgItem(IDC_BUTTON_DELETE_SELECTED_SUBJECT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_ADD_SUBJECT)->SetFocus();

    CDialogEx::OnInitDialog();

    if (!m_Subjects.isEmpty())
    {
        for (size_t i = 0; i < m_Subjects.getSize(); ++i, ++m_Subjects)
        {
            common::CorrectScroll::correctListHScrlPart(m_SubjectsList, m_MaxExtList, m_FontAveChar, m_SubjectsList.AddString((LPCTSTR)m_Subjects.getReferencesCurrentData()));
        }
        m_Subjects.setCurrentNodeOnTheBegin();
    }

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
    m_Subjects.setCurrentNodeOnTheBegin();
    CDialogEx::OnOK();
}

void InputSubjects::OnLbnSelchangeListSubjectInputWindow()
{
    int selected = m_SubjectsList.GetCurSel();
    if (selected != LB_ERR && selected != m_OldSubjectSelect)
    {
        Iterator <CString> iter(&m_Subjects);
        common::for_each_listbox(iter, m_SubjectsList, m_OldSubjectSelect, selected);
    }
    GetDlgItem(IDC_BUTTON_DELETE_SELECTED_SUBJECT)->EnableWindow(TRUE);
}

void InputSubjects::OnBnClickedButtonDeleteSelectedSubject()
{
    CString str = m_Subjects.getValueCurrentData();
    m_Subjects.deleteElement(str);
    common::CorrectScroll::correctListHScrlDel(m_SubjectsList, m_MaxExtList, m_FontAveChar, m_SubjectsList.GetCurSel());
    m_Subjects.setCurrentNodeOnTheBegin();
    GetDlgItem(IDC_BUTTON_DELETE_SELECTED_SUBJECT)->EnableWindow(FALSE);
}
