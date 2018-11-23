// ShowSubjectsAndMarks.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "ShowSubjectsAndMarks.h"
#include "afxdialogex.h"
#include "constants.h"
#include "CommonFunctions.h"


// ShowSubjectsAndMarks dialog

IMPLEMENT_DYNAMIC(ShowSubjectsAndMarks, CDialogEx)

ShowSubjectsAndMarks::ShowSubjectsAndMarks(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SHOW_SUBJECTS_AND_MARKS, pParent)
{

}

ShowSubjectsAndMarks::~ShowSubjectsAndMarks()
{
}

void ShowSubjectsAndMarks::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LIST_SUBJECTS_AND_MARKS, m_RecordBookListBox);
    DDX_Control(pDX, IDC_LIST_STUDENTS_MARKS, m_MarkListBox);
    DDX_Text(pDX, IDC_EDIT_FIND_SUBJECTS_AND_MARKS, m_FindRecord);
}


BEGIN_MESSAGE_MAP(ShowSubjectsAndMarks, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CLOSE_SHOW_SUBJECT_WINDOW, &ShowSubjectsAndMarks::OnBnClickedButtonCloseShowSubjectWindow)
    ON_EN_CHANGE(IDC_EDIT_FIND_SUBJECTS_IN_SHOW_WINDOW, &ShowSubjectsAndMarks::OnEnChangeEditFindSubjectsInShowWindow)
    ON_LBN_SELCHANGE(IDC_LIST_STUDENTS_MARKS, &ShowSubjectsAndMarks::OnLbnSelchangeListStudentsMarks)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_SUBJECT_FROM_RECORDBOOK, &ShowSubjectsAndMarks::OnBnClickedButtonDeleteSubjectFromRecordbook)
    ON_LBN_SELCHANGE(IDC_LIST_STUDENTS_SUBJECTS_IN_SHOW_WINDOW, &ShowSubjectsAndMarks::OnLbnSelchangeListStudentsSubjectsInShowWindow)
END_MESSAGE_MAP()


// ShowSubjectsAndMarks message handlers
BOOL ShowSubjectsAndMarks::OnInitDialog()
{
    UpdateData(FALSE);
    m_RecordBookListBox.ResetContent();
    TEXTMETRIC tm;
    CDC* pDC = m_RecordBookListBox.GetDC();
    CFont *pOldFont = pDC->SelectObject(m_RecordBookListBox.GetFont());
    pDC->GetTextMetrics(&tm);
    pDC->SelectObject(pOldFont);
    m_RecordBookListBox.ReleaseDC(pDC);
    m_FontAveChar = tm.tmAveCharWidth;
    m_MaxExtList = 0;
    m_OldSubjectSelect = LB_ERR;
    m_OldMarkSelect = LB_ERR;
    SetDefID(IDC_STATIC_SUBJECTS_AND_MARKS);
    m_RecordBookListBox.ResetContent();
    m_MarkListBox.ResetContent();
    m_FindRecord = __TEXT("");
    if (m_RecordBook != NULL)
    {
        for (size_t i = 0; i < m_RecordBook->getSize(); ++i, ++*m_RecordBook)
        {
            int index = m_RecordBookListBox.AddString((LPCTSTR)m_RecordBook->getReferencesCurrentData().first);
            common::CorrectScroll::correctListHScrlPart(m_RecordBookListBox, m_MaxExtList, m_FontAveChar, index);
            CString buf;
            buf.Format(__TEXT("%4.2f"), m_RecordBook->getReferencesCurrentData().second);
            m_MarkListBox.InsertString(index, buf);
        }
        m_RecordBook->setCurrentNodeOnTheBegin();
    }
    CDialogEx::OnInitDialog();
    return FALSE;
}

void ShowSubjectsAndMarks::setRecordBook(List<std::pair<CString, float>>* recordBook)
{
    m_RecordBook = recordBook;
}

void ShowSubjectsAndMarks::OnBnClickedButtonCloseShowSubjectWindow()
{
    CDialogEx::OnOK();
}

void ShowSubjectsAndMarks::OnEnChangeEditFindSubjectsInShowWindow()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_FIND_SUBJECTS_IN_SHOW_WINDOW)))->GetLine(0, buffer)] = 0;

    if ((search = m_RecordBookListBox.FindString(-1, buffer)) != LB_ERR)
    {
        m_RecordBookListBox.SetCurSel(search);
        OnLbnSelchangeListStudentsSubjectsInShowWindow();
    }
}

void ShowSubjectsAndMarks::OnLbnSelchangeListStudentsSubjectsInShowWindow()
{
    int selected = m_RecordBookListBox.GetCurSel();
    if (selected != LB_ERR && selected != m_OldSubjectSelect)
    {
        Iterator<std::pair<CString, float>> iter(m_RecordBook);
        common::for_each_listbox(iter, m_RecordBookListBox, m_OldSubjectSelect, selected);
        if (m_MarkListBox.GetCurSel() != selected)
        {
            m_MarkListBox.SetCurSel(selected);
            OnLbnSelchangeListStudentsMarks();
        }
    }
    GetDlgItem(IDC_BUTTON_DELETE_SUBJECT_FROM_RECORDBOOK)->EnableWindow(TRUE);
}

void ShowSubjectsAndMarks::OnLbnSelchangeListStudentsMarks()
{
    int selected = m_MarkListBox.GetCurSel();
    if (selected != LB_ERR && selected != m_OldMarkSelect && m_RecordBookListBox.GetCurSel() != selected)
    {
        m_RecordBookListBox.SetCurSel(selected);
        OnLbnSelchangeListStudentsSubjectsInShowWindow();
    }
}

void ShowSubjectsAndMarks::OnBnClickedButtonDeleteSubjectFromRecordbook()
{
    auto record = m_RecordBook->getValueCurrentData();
    m_RecordBook->deleteElement(record);
    common::CorrectScroll::correctListHScrlDel(m_RecordBookListBox, m_MaxExtList, m_FontAveChar, m_RecordBookListBox.GetCurSel());
    common::CorrectScroll::correctListHScrlDel(m_MarkListBox, m_MaxExtList, m_FontAveChar, m_MarkListBox.GetCurSel());
    m_RecordBook->setCurrentNodeOnTheBegin();
    m_OldSubjectSelect = LB_ERR;
    m_OldMarkSelect = LB_ERR;
    GetDlgItem(IDC_BUTTON_DELETE_SUBJECT_FROM_RECORDBOOK)->EnableWindow(FALSE);
    if (m_RecordBook->isEmpty())
    {
        GetDlgItem(IDC_EDIT_FIND_SUBJECTS_IN_SHOW_WINDOW)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST_STUDENTS_SUBJECTS_IN_SHOW_WINDOW)->EnableWindow(FALSE);
        GetDlgItem(IDC_LIST_STUDENTS_MARKS)->EnableWindow(FALSE);
    }
}