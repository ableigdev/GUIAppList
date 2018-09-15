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
    ON_BN_CLICKED(IDOK, &InputNewName::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &InputNewName::OnBnClickedCancel)
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

void InputNewName::OnBnClickedOk()
{
    UpdateData(TRUE);
    m_Name->TrimLeft();
    m_Name->TrimRight();

    if (*m_Name != __TEXT(""))
    {
        CDialogEx::OnOK();
    }
    else
    {
        this->MessageBox(__TEXT("You must not enter empty strings!"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    }
}


void InputNewName::OnBnClickedCancel()
{
    CDialogEx::OnCancel();
}
