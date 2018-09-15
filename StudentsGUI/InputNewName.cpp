// InputNewName.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputNewName.h"
#include "afxdialogex.h"


// InputNewName dialog

IMPLEMENT_DYNAMIC(InputNewName, CDialogEx)

InputNewName::InputNewName(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_NAME, pParent)
{

}

InputNewName::~InputNewName()
{
}

void InputNewName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_ENTER_NAME, *m_Name);
}


BEGIN_MESSAGE_MAP(InputNewName, CDialogEx)
END_MESSAGE_MAP()


// InputNewName message handlers
BOOL InputNewName::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CString OutTitle = __TEXT("Input Name of ") + Title;
    SetWindowText((LPCTSTR)OutTitle);
    UpdateData(FALSE);
    CWnd* Wnd = this->GetDlgItem(IDC_EDIT_ENTER_NAME);
    Wnd->SetFocus();
    ((CEdit*)(Wnd))->SetSel(0, m_Name->GetLength());

    return FALSE;
}