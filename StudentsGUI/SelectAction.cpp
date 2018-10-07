// SelectAction.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "SelectAction.h"
#include "afxdialogex.h"
#include "constants.h"

// SelectAction dialog

IMPLEMENT_DYNAMIC(SelectAction, CDialogEx)

SelectAction::SelectAction(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SELECT_ACTION, pParent)
{

}

SelectAction::~SelectAction()
{
}

void SelectAction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelectAction, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CHOOSE_GROUP, &SelectAction::OnBnClickedButtonChooseGroup)
    ON_BN_CLICKED(IDC_BUTTON_CHOOSE_STUDENT, &SelectAction::OnBnClickedButtonChooseStudent)
END_MESSAGE_MAP()


// SelectAction message handlers
void SelectAction::setActionName(CString name)
{
    m_ActionName = name;
}

int SelectAction::getAnswer() const
{
    return m_Answer;
}

BOOL SelectAction::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CString outTitle = __TEXT("What would you like to " + m_ActionName + "?");
    SetWindowText((LPCTSTR)outTitle);
    m_Answer = UNKNOWN_ANSWER;

    return FALSE;
}

void SelectAction::OnBnClickedButtonChooseGroup()
{
    m_Answer = GROUP_ANSWER;
    CDialogEx::OnOK();
}

void SelectAction::OnBnClickedButtonChooseStudent()
{
    m_Answer = STUDENT_ANSWER;
    CDialogEx::OnOK();
}
