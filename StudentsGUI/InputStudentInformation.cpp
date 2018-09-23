// InputStudentInformation.cpp : implementation fil, e
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputStudentInformation.h"
#include "afxdialogex.h"
#include "constants.h"


// InputStudentInformation dialog

IMPLEMENT_DYNAMIC(InputStudentInformation, CDialogEx)

InputStudentInformation::InputStudentInformation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INPUT_STUDENT, pParent)
{

}

InputStudentInformation::~InputStudentInformation()
{
}

void InputStudentInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    short int year = m_Student->getBirthYear();
    float grade = m_Student->getAverageGrade();
    DDX_Control(pDX, IDC_COMBO_GROUPS, m_ComboGroupList);
    DDX_Text(pDX, IDC_STUDENT_EDIT_SURNAME, (CString)m_Student->getSurname().c_str());
    DDX_Text(pDX, IDC_STUDENT_EDIT_NAME, (CString)m_Student->getName().c_str());
    DDX_Text(pDX, IDC_STUDENT_EDIT_LASTNAME, (CString)m_Student->getLastname().c_str());
    DDX_Text(pDX, IDC_STUDENT_EDIT_BIRTH_YEAR, year);
    DDV_MinMaxUInt(pDX, m_Student->getBirthYear(), 1900, 2100);
    DDX_Text(pDX, IDC_STUDENT_EDIT_AVERAGE_MARK, grade);
    DDV_MinMaxFloat(pDX, m_Student->getAverageGrade(), 0.f, 5.f);
}


BEGIN_MESSAGE_MAP(InputStudentInformation, CDialogEx)
    ON_BN_CLICKED(IDC_STUDENT_BUTTON_NEXT, &InputStudentInformation::OnBnClickedStudentButtonNext)
    ON_BN_CLICKED(IDOK, &InputStudentInformation::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &InputStudentInformation::OnBnClickedCancel)
    ON_CBN_SELCHANGE(IDC_COMBO_GROUPS, &InputStudentInformation::OnCbnSelchangeComboGroups)
END_MESSAGE_MAP()


// InputStudentInformation message handlers
void InputStudentInformation::setChangeFlag(int flag)
{
    m_ChangeFlag = flag;
}

void InputStudentInformation::setStudent(Student* student)
{
    m_Student = student;
}

void InputStudentInformation::setGroup(NameList<Student>* group)
{
    m_Group = group;
}

void InputStudentInformation::setFaculty(NameList<NameList<Student>>* faculty)
{
    m_Faculty = faculty;
}

void InputStudentInformation::setListBoxGroupList(CListBox* listBox)
{
    m_ListBoxGroupList = listBox;
}

CListBox* InputStudentInformation::getListBoxGroupList() const
{
    return m_ListBoxGroupList;
}

void InputStudentInformation::setActiveSurname()
{
    CWnd* wnd = GetDlgItem(IDC_STUDENT_EDIT_SURNAME);
    wnd->SetFocus();
    ((CEdit*)(wnd))->SetSel(0, m_Student->getSurname().size());
}

bool InputStudentInformation::checkConstruction()
{
    return m_Student->getSurname().size() > 0 && m_Student->getName().size();
}

bool InputStudentInformation::addStudent()
{
    UpdateData(FALSE);

    if (checkConstruction())
    {
        if (m_ChangeFlag == ADD)
        {
            m_Group->pushInSortList(*m_Student);
        }
        return true;
    }
    m_IsModify = true;
    MessageBox(__TEXT("Surname or name is empty"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    return false;
}

BOOL InputStudentInformation::OnInitDialog()
{
    if (m_ChangeFlag == ADD)
    {
        m_Student = &m_WorkStudent;
        m_IsModify = true;
    }

    CDialogEx::OnInitDialog();

    if (m_ChangeFlag != ADD)
    {
        m_WorkStudent = *m_Student;
        m_IsModify = false;
        GetDlgItem(IDC_STUDENT_BUTTON_NEXT)->EnableWindow(FALSE);
        SetDefID(IDOK);
        UpdateData(FALSE);
    }

    setActiveSurname();

    if (m_Faculty != NULL)
    {
        m_ComboGroupList.AddString((LPCTSTR)m_Faculty->getReferencesCurrentData().getNameClassList().c_str());
    }
    
    return FALSE;
}

void InputStudentInformation::OnBnClickedStudentButtonNext()
{
    if (UpdateData() == TRUE)
    {
        addStudent();
        setActiveSurname();
    }
}


void InputStudentInformation::OnBnClickedOk()
{
    if (UpdateData() == TRUE && addStudent())
    {
        EndDialog(IDOK);
    }
}


void InputStudentInformation::OnBnClickedCancel()
{
    if (m_IsModify)
    {
        *m_Student = m_WorkStudent;
    }
    CDialogEx::OnCancel();
}


void InputStudentInformation::OnCbnSelchangeComboGroups()
{
    // TODO: Add your control notification handler code here
}
