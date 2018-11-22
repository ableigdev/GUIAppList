// ShowSubjectsAndMarks.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "ShowSubjectsAndMarks.h"
#include "afxdialogex.h"
#include "constants.h"


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
    DDX_Text(pDX, IDC_EDIT_FIND_SUBJECTS_AND_MARKS, m_FindRecord);
}


BEGIN_MESSAGE_MAP(ShowSubjectsAndMarks, CDialogEx)
    ON_EN_CHANGE(IDC_EDIT_FIND_SUBJECTS_AND_MARKS, &ShowSubjectsAndMarks::OnEnChangeEditFindSubjectsAndMarks)
    ON_LBN_SELCHANGE(IDC_LIST_SUBJECTS_AND_MARKS, &ShowSubjectsAndMarks::OnLbnSelchangeListSubjectsAndMarks)
    ON_BN_CLICKED(IDC_BUTTON_CLOSE_SHOW_SUBJECT_WINDOW, &ShowSubjectsAndMarks::OnBnClickedButtonCloseShowSubjectWindow)
END_MESSAGE_MAP()


// ShowSubjectsAndMarks message handlers
BOOL ShowSubjectsAndMarks::OnInitDialog()
{
    UpdateData(FALSE);
    m_RecordBookListBox.ResetContent();
    m_FindRecord = __TEXT("");
    if (m_RecordBook != NULL)
    {
        for (size_t i = 0; i < m_RecordBook->getSize(); ++i, ++*m_RecordBook)
        {
            CString buf;
            buf.Format(__TEXT("%s %4.2f"), *m_RecordBook->getReferencesCurrentData().first, *m_RecordBook->getReferencesCurrentData().second);
            m_RecordBookListBox.AddString(buf);
        }
        m_RecordBook->setCurrentNodeOnTheBegin();
    }
    CDialogEx::OnInitDialog();
    return FALSE;
}

void ShowSubjectsAndMarks::setRecordBook(List<std::pair<CString*, float*>>* recordBook)
{
    m_RecordBook = recordBook;
}

void ShowSubjectsAndMarks::OnEnChangeEditFindSubjectsAndMarks()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_FIND_SUBJECTS_AND_MARKS)))->GetLine(0, buffer)] = 0;

    if ((search = m_RecordBookListBox.FindString(-1, buffer)) != LB_ERR)
    {
        m_RecordBookListBox.SetCurSel(search);
    }
}


void ShowSubjectsAndMarks::OnLbnSelchangeListSubjectsAndMarks()
{
    // TODO: Add your control notification handler code here
}


void ShowSubjectsAndMarks::OnBnClickedButtonCloseShowSubjectWindow()
{
    CDialogEx::OnOK();
}
