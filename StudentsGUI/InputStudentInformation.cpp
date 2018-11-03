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

    CString surname = m_Student->getSurname().c_str();
    CString name = m_Student->getName().c_str();
    CString lastname = m_Student->getLastname().c_str();
    short int year = m_Student->getBirthYear();
    float grade = m_Student->getAverageGrade();

    DDX_Control(pDX, IDC_COMBO_GROUPS, m_ComboGroupList);
    DDX_Text(pDX, IDC_STUDENT_EDIT_SURNAME, surname);
    m_Student->setSurname(surname.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_NAME, name);
    m_Student->setName(name.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_LASTNAME, lastname);
    m_Student->setLastname(lastname.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_BIRTH_YEAR, year);
    DDV_MinMaxUInt(pDX, year, 1900, 2100);
    m_Student->setBirthYear(year);

    DDX_Text(pDX, IDC_STUDENT_EDIT_AVERAGE_MARK, grade);
    DDV_MinMaxFloat(pDX, grade, 0.f, 5.f);
    m_Student->setAverageGrade(grade);
}


BEGIN_MESSAGE_MAP(InputStudentInformation, CDialogEx)
    ON_BN_CLICKED(IDC_STUDENT_BUTTON_NEXT, &InputStudentInformation::OnBnClickedStudentButtonNext)
    ON_BN_CLICKED(IDOK, &InputStudentInformation::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &InputStudentInformation::OnBnClickedCancel)
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
    ((CEdit*)(wnd))->SetSel(0, static_cast<int>(m_Student->getSurname().size()));
}

void InputStudentInformation::setCurrentBranchIndex(int index)
{
    m_CurrentGroupIndex = index;
}

bool InputStudentInformation::checkConstruction()
{
    return m_Student->getSurname().size() > 0 && m_Student->getName().size();
}

bool InputStudentInformation::addStudent()
{
    UpdateData(FALSE);

    auto currentSelect = m_ComboGroupList.GetCurSel();

    if (checkConstruction())
    {
        if (m_ChangeFlag == ADD)
        {
            m_Faculty->setCurrentNodeOnTheBegin();
            for (size_t i = 0; i < m_Faculty->getSize(); ++i)
            {
                if (i == currentSelect)
                {
                    m_Faculty->getReferencesCurrentData().pushInSortList(*m_Student);
                    break;
                }
                m_Faculty->operator++();
            }
        }
        return true;
    }
    MessageBox(__TEXT("Surname or name is empty"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    
    m_IsModify = true;
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
        GetDlgItem(IDC_COMBO_GROUPS)->EnableWindow(FALSE);
        SetDefID(IDOK);
        UpdateData(FALSE);
    }

    setActiveSurname();

    if (m_Faculty)
    {
        m_Faculty->setCurrentNodeOnTheBegin();
        for (size_t i = 0; i < m_Faculty->getSize(); ++i)
        {
            m_ComboGroupList.AddString((LPCTSTR)m_Faculty->getReferencesCurrentData().getNameClassList().c_str());
            m_Faculty->operator++();
        }
        m_Faculty->setCurrentNodeOnTheBegin();
        m_ComboGroupList.SetCurSel(m_CurrentGroupIndex != LB_ERR ? m_CurrentGroupIndex : 0);
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
