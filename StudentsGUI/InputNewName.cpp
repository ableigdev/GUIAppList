// InputNewName.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputNewName.h"
#include "afxdialogex.h"
#include "constants.h"


// InputNewName dialog

IMPLEMENT_DYNAMIC(InputNewName, CDialogEx)

InputNewName::InputNewName(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_NAME, pParent),
    m_CStringName(new CString[STRING_SIZE])
{

}

InputNewName::~InputNewName()
{
    if (m_CStringName != NULL)
    {
        delete[] m_CStringName;
    }
}

void InputNewName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
    *m_CStringName = m_Name->c_str();
    DDX_Text(pDX, IDC_EDIT_ENTER_NAME, *m_CStringName);
}


BEGIN_MESSAGE_MAP(InputNewName, CDialogEx)
    ON_BN_CLICKED(IDOK, &InputNewName::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &InputNewName::OnBnClickedCancel)
END_MESSAGE_MAP()


// InputNewName message handlers
BOOL InputNewName::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    CString outTitle = __TEXT("Input Name of ") + m_Title;
    SetWindowText((LPCTSTR)outTitle);
    UpdateData(FALSE);
    CWnd* wnd = this->GetDlgItem(IDC_EDIT_ENTER_NAME);
    wnd->SetFocus();
    ((CEdit*)(wnd))->SetSel(0, m_CStringName->GetLength());

    return FALSE;
}

void InputNewName::OnBnClickedOk()
{
    UpdateData(TRUE);
    m_CStringName->TrimLeft();
    m_CStringName->TrimRight();

    if (*m_CStringName != __TEXT(""))
    {
        *m_Name = m_CStringName->GetString();
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

void InputNewName::setTitle(CString title)
{
    m_Title = title;
}

CString InputNewName::getTitle() const
{
    return m_Title;
}

void InputNewName::setName(std::basic_string<TYPESTRING>* name)
{
    m_Name = name;
}

std::basic_string<TYPESTRING>* InputNewName::getName() const
{
    return m_Name;
}

