// InputStudentInformation.cpp : implementation fil, e
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputStudentInformation.h"
#include "afxdialogex.h"
#include "constants.h"
#include <algorithm>


// InputStudentInformation dialog

IMPLEMENT_DYNAMIC(InputStudentInformation, CDialogEx)

InputStudentInformation::InputStudentInformation(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_INPUT_STUDENT, pParent)
{
    m_Surname = __TEXT("");
    m_Name = __TEXT("");
    m_Lastname = __TEXT("");
    m_BirthYear = 0;
    m_AverageGrade = 0.0;
}

InputStudentInformation::~InputStudentInformation()
{
}

void InputStudentInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    m_Surname = m_Student->getSurname().c_str();
    m_Name = m_Student->getName().c_str();
    m_Lastname = m_Student->getLastname().c_str();
    m_BirthYear = m_Student->getBirthYear();
    m_AverageGrade = m_Student->getAverageGrade();

    DDX_Control(pDX, IDC_COMBO_GROUPS, m_ComboGroupList);
    DDX_Text(pDX, IDC_STUDENT_EDIT_SURNAME, m_Surname);
    m_Surname.TrimLeft();
    m_Surname.TrimRight();
    m_Student->setSurname(m_Surname.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_NAME, m_Name);
    m_Name.TrimLeft();
    m_Name.TrimRight();
    m_Student->setName(m_Name.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_LASTNAME, m_Lastname);
    m_Lastname.TrimLeft();
    m_Lastname.TrimRight();
    m_Student->setLastname(m_Lastname.GetString());

    DDX_Text(pDX, IDC_STUDENT_EDIT_BIRTH_YEAR, m_BirthYear);
    DDV_MinMaxUInt(pDX, m_BirthYear, 1900, 2100);
    m_Student->setBirthYear(m_BirthYear);

    DDX_Text(pDX, IDC_STUDENT_EDIT_AVERAGE_MARK, m_AverageGrade);
    DDV_MinMaxFloat(pDX, m_AverageGrade, 0.f, 5.f);
    m_Student->setAverageGrade(m_AverageGrade);
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

int InputStudentInformation::getCurrentSelectedGroup() const
{
    return m_CurrentGroupIndex;
}

bool InputStudentInformation::checkConstruction()
{
    return !m_Student->getSurname().empty() && !m_Student->getName().empty();
}

bool InputStudentInformation::addStudent()
{
    UpdateData(FALSE);

    m_CurrentGroupIndex = m_ComboGroupList.GetCurSel();

    if (checkConstruction())
    {
        if (m_ChangeFlag == ADD)
        {
            m_Faculty->setCurrentNodeOnTheBegin();
            for (size_t i = 0; i < m_CurrentGroupIndex; ++i, ++*m_Faculty);
            m_Faculty->getReferencesCurrentData().pushInSortList(*m_Student);
        }
        return true;
    }
    MessageBox(__TEXT("Surname or name is empty"), __TEXT("Error"), MB_OK | MB_ICONSTOP);
    m_Student->getSurname().empty() ? GetDlgItem(IDC_STUDENT_EDIT_SURNAME)->SetFocus() : GetDlgItem(IDC_STUDENT_EDIT_NAME)->SetFocus();
    
    m_IsModify = true;
    return false;
}

BOOL InputStudentInformation::OnInitDialog()
{
    if (m_ChangeFlag == ADD)
    {
        m_Student = &m_WorkStudent;
        m_IsModify = true;
        SetDefID(IDC_STUDENT_BUTTON_NEXT);
        SetWindowText(__TEXT("Input Student Information"));
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
        SetWindowText(__TEXT("Change Student Information"));
    }

    setActiveSurname();

    if (m_Faculty)
    {
        auto currentGroup = &m_Faculty->getReferencesCurrentData();
        m_Faculty->setCurrentNodeOnTheBegin();
        for (int i = 0; i < m_Faculty->getSize(); ++i, ++*m_Faculty)
        {
            m_ComboGroupList.AddString((LPCTSTR)m_Faculty->getReferencesCurrentData().getNameClassList().c_str());
        }
        //m_Faculty->setCurrentNodeOnTheBegin();
        m_ComboGroupList.SetCurSel(m_CurrentGroupIndex != LB_ERR ? m_CurrentGroupIndex : 0);
        setBeginState(currentGroup);
    }
    
    return FALSE;
}

void InputStudentInformation::OnBnClickedStudentButtonNext()
{
    if (UpdateData() == TRUE && addStudent())
    {
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

void InputStudentInformation::setBeginState(NameList<Student>* group)
{
    while (&m_Faculty->getReferencesCurrentData() != group)
    {
        ++*m_Faculty;
    }
}
