
// StudentsGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "StudentsGUIDlg.h"
#include "afxdialogex.h"
#include "constants.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _LEN(VAR, BT)\
		sizeof(VAR) >> (sizeof(BT) >> 1)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentsGUIDlg dialog



CStudentsGUIDlg::CStudentsGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STUDENTSGUI_DIALOG, pParent)
{
    m_OldGroupSelect = LB_ERR;
    m_StudentName = __TEXT("");
    m_GroupName = __TEXT("");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentsGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_LIST_STUD_INFO, m_ListStudInfo);
    DDX_Control(pDX, IDC_LIST_STUDENTS, m_ListStudents);
    DDX_Control(pDX, IDC_LIST_GROUPS, m_ListGroups);
    DDX_Text(pDX, IDC_EDIT_STUDENT, m_StudentName);
    DDX_Text(pDX, IDC_EDIT_GROUP, m_GroupName);
    DDV_MaxChars(pDX, m_GroupName, 7);
}

BEGIN_MESSAGE_MAP(CStudentsGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_FACULTY_ADD, &CStudentsGUIDlg::OnBnClickedButtonFacultyAdd)
    ON_BN_CLICKED(IDC_BUTTON_FACULTY_CHANGE, &CStudentsGUIDlg::OnBnClickedButtonFacultyChange)
    ON_BN_CLICKED(IDC_BUTTON_FACULTY_GET, &CStudentsGUIDlg::OnBnClickedButtonFacultyGet)
    ON_BN_CLICKED(IDC_BUTTON_FACULTY_DELETE, &CStudentsGUIDlg::OnBnClickedButtonFacultyDelete)
    ON_BN_CLICKED(IDC_BUTTON_ADD_STUDENTS, &CStudentsGUIDlg::OnBnClickedButtonAddStudents)
    ON_BN_CLICKED(IDC_BUTTON_DELETE, &CStudentsGUIDlg::OnBnClickedButtonDelete)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_STUDENTS, &CStudentsGUIDlg::OnBnClickedButtonDeleteAllStudents)
    ON_BN_CLICKED(IDC_BUTTON_ADD_GROUP, &CStudentsGUIDlg::OnBnClickedButtonAddGroup)
    ON_BN_CLICKED(IDC_BUTTON_DELETE_ALL_GROUP, &CStudentsGUIDlg::OnBnClickedButtonDeleteAllGroup)
    ON_EN_CHANGE(IDC_EDIT_STUDENT, &CStudentsGUIDlg::OnEnChangeEditStudent)
    ON_LBN_SELCHANGE(IDC_LIST_STUDENTS, &CStudentsGUIDlg::OnLbnSelchangeListStudents)
    ON_EN_CHANGE(IDC_EDIT_GROUP, &CStudentsGUIDlg::OnEnChangeEditGroup)
    ON_LBN_SELCHANGE(IDC_LIST_GROUPS, &CStudentsGUIDlg::OnLbnSelchangeListGroups)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CStudentsGUIDlg::OnBnClickedButtonChange)
END_MESSAGE_MAP()


// CStudentsGUIDlg message handlers

BOOL CStudentsGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

    m_InputStudInform.setListBoxGroupList(&m_ListGroups);
    m_Student = NULL;
    m_InputStudInform.setStudent(m_Student);

    TEXTMETRIC tm;
    CDC* pDC = m_ListStudents.GetDC();
    CFont *pOldFont = pDC->SelectObject(m_ListStudents.GetFont());
    pDC->GetTextMetrics(&tm);
    pDC->SelectObject(pOldFont);
    m_ListStudents.ReleaseDC(pDC);
    m_FontAveChar = tm.tmAveCharWidth;
    m_MaxExtListStud = 0;
    m_MaxExtListGroup = 0;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStudentsGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStudentsGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStudentsGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStudentsGUIDlg::deleteStudentList()
{
    deleteStudentInformationList();
    m_ListStudents.ResetContent();
    CorrectListHScrlPart(m_ListStudents, m_MaxExtListStud);
}

void CStudentsGUIDlg::deleteStudentInformationList()
{
    m_ListStudInfo.ResetContent();
    CorrectListHScrl(m_ListStudInfo);
}

void CStudentsGUIDlg::deleteAllLists()
{
    deleteGroupList();
    deleteStudentList();
}

void CStudentsGUIDlg::setFacultyActions(BOOL state)
{
    WORD wID[] = 
    { 
        IDC_BUTTON_FACULTY_CHANGE, 
        IDC_BUTTON_FACULTY_DELETE,
        IDC_BUTTON_FACULTY_GET,
        IDC_BUTTON_ADD_GROUP
    };
    setButtonState(wID, _LEN(wID, WORD), state);
    setAddFacultyActions(!state);
}

BOOL CStudentsGUIDlg::setGroupActions(BOOL state)
{
    WORD wID[] =
    {
        IDC_EDIT_GROUP,
        IDC_LIST_GROUPS
    };
    setButtonState(wID, _LEN(wID, WORD), state);
    return state;
}

void CStudentsGUIDlg::setButtonState(WORD wID[], WORD len, BOOL state)
{
    for (WORD i = 0; i < len; ++i)
    {
        GetDlgItem(wID[i])->EnableWindow(state);
    }
}

BOOL CStudentsGUIDlg::setStudentActions(BOOL state)
{
    WORD wID[] = 
    {
        IDC_BUTTON_ADD_STUDENTS,
        IDC_EDIT_STUDENT,
        IDC_LIST_STUDENTS,
        IDC_LIST_STUD_INFO
    };
    setButtonState(wID, _LEN(wID, WORD), state);
    return state;
}

void CStudentsGUIDlg::setSelectedActions(BOOL state)
{
    WORD wID[] =
    {
        IDC_BUTTON_DELETE,
        IDC_BUTTON_CHANGE
    };
    setButtonState(wID, _LEN(wID, WORD), state);
}

void CStudentsGUIDlg::setAddFacultyActions(BOOL state)
{
    WORD wID[] =
    {
        IDC_BUTTON_FACULTY_ADD
    };
    setButtonState(wID, _LEN(wID, WORD), state);
}

void CStudentsGUIDlg::disableFaculty()
{
    setStudentActions(FALSE);
    setFacultyActions(FALSE);
}

void CStudentsGUIDlg::showString(Student& student)
{
    CorrectListHScrlPart(m_ListStudents, m_MaxExtListStud, m_ListStudents.AddString((LPCTSTR)getStudentString(student).c_str()));
}

void CStudentsGUIDlg::showStudent()
{
    deleteStudentList();
    if (!m_Faculty.isEmpty())
    {
        m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
        if (!m_CurrentGroup->isEmpty())
        {
            m_CurrentGroup->setCurrentNodeOnTheBegin();
            for (size_t i = 0; i < m_CurrentGroup->getSize(); ++i)
            {
                m_Student = &m_CurrentGroup->getReferencesCurrentData();
                showString(*m_Student);
                m_CurrentGroup->operator++();
            }
            m_CurrentGroup->setCurrentNodeOnTheBegin();
            m_Student = &m_CurrentGroup->getReferencesCurrentData();
            showStudentInformation(*m_Student);
            m_OldStudSelect = LB_ERR;
        }
    }
}

int CStudentsGUIDlg::setNewSelect(CListBox& listBox, int& maxExtCx)
{
    int currentSelect = listBox.GetCurSel();
    CorrectListHScrlDel(listBox, maxExtCx, currentSelect);
    
    if (currentSelect != 0)
    {
        --currentSelect;
    }

    listBox.SetCurSel(currentSelect);
    return currentSelect;
}

int CStudentsGUIDlg::changeItem(CListBox& listBox, int& maxExtCx, const std::basic_string<TYPESTRING>& name)
{
    int currentSelect = listBox.GetCurSel();
    if (currentSelect != LB_ERR)
    {
        CorrectListHScrlDel(listBox, maxExtCx, currentSelect);
        listBox.SetCurSel(currentSelect = listBox.AddString(name.c_str()));
        CorrectListHScrlPart(listBox, maxExtCx, currentSelect);
    }
    return currentSelect;
}

void CStudentsGUIDlg::deleteStudent()
{
    m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
    m_CurrentGroup->deleteElement(m_CurrentGroup->getValueCurrentData());
    if (!m_CurrentGroup)
    {
        m_Student = &m_CurrentGroup->getReferencesCurrentData();
        m_OldStudSelect = setNewSelect(m_ListStudents, m_MaxExtListStud);
        showStudentInformation(*m_Student);
    }
    else
    {
        deleteStudentList();
        setStudentActions(FALSE);
    }
}

void CStudentsGUIDlg::modifyStudent()
{
    m_InputStudInform.setChangeFlag(CHANGE);
    m_InputStudInform.setStudent(m_Student);

    if (m_InputStudInform.DoModal() == IDOK)
    {
        m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
        m_CurrentGroup->sortCurrentNodePtr();
        m_OldStudSelect = changeItem(m_ListStudents, m_MaxExtListStud, m_Student->getSurname().c_str());
        showStudentInformation(*m_Student);
    }
}

void CStudentsGUIDlg::showStudentInformation(const Student& student)
{
    CString buf;
    deleteStudentInformationList();

    buf.Format(__TEXT("Surname              : %s"), student.getSurname().c_str());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Name                   : %s"), student.getName().c_str());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Lastname             : %s"), student.getLastname().c_str());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Birth Year             : %i"), student.getBirthYear());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Average Grade    : %4.2f"), student.getAverageGrade());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    
    CorrectListHScrl(m_ListStudInfo);
}

void CStudentsGUIDlg::CorrectListHScrl(CListBox& listBox)
{
    int dx = 0;
    if (listBox.GetCount() > 0)
    {
        CDC* pDC = listBox.GetDC();
        CFont* pOldFont = pDC->SelectObject(listBox.GetFont());
        CString str;
        CSize sz;

        for (int i = 0; i < listBox.GetCount(); i++)
        {
            listBox.GetText(i, str);
            sz = pDC->GetTextExtent(str);
            if (sz.cx > dx)
            {
                dx = sz.cx;
            }
        }
        pDC->SelectObject(pOldFont);
        listBox.ReleaseDC(pDC);
        dx += m_FontAveChar;
    }
    listBox.SetHorizontalExtent(dx);
}

void CStudentsGUIDlg::CorrectListHScrlPart(CListBox& listBox, int& maxExtCx, int index)
{
    bool isModify = true;
    if (listBox.GetCount() > 0)
    {
        CDC* pDC = listBox.GetDC();
        CFont* pOldFont = pDC->SelectObject(listBox.GetFont());
        CString str;
        CSize sz;

        listBox.GetText(index, str);
        sz = pDC->GetTextExtent(str);

        if ((isModify = sz.cx + m_FontAveChar > maxExtCx))
        {
            maxExtCx = sz.cx + m_FontAveChar;
        }
        pDC->SelectObject(pOldFont);
        listBox.ReleaseDC(pDC);
    }
    else
    {
        maxExtCx = 0;
    }
    if (isModify)
    {
        listBox.SetHorizontalExtent(maxExtCx);
    }
}

void CStudentsGUIDlg::CorrectListHScrlDel(CListBox& listBox, int& maxExtCx, int index)
{
    CDC* pDC = listBox.GetDC();
    CFont* pOldFont = pDC->SelectObject(listBox.GetFont());
    CString str;
    CSize sz;

    listBox.GetText(index, str);
    sz = pDC->GetTextExtent(str);
    listBox.DeleteString(index);
    if (sz.cx + m_FontAveChar == maxExtCx)
    {
        maxExtCx = 0;
        for (int i = 0; i < listBox.GetCount(); i++)
        {
            listBox.GetText(i, str);
            sz = pDC->GetTextExtent(str);

            if (sz.cx > maxExtCx)
            {
                maxExtCx = sz.cx;
            }
        }
        maxExtCx += m_FontAveChar;
        listBox.SetHorizontalExtent(maxExtCx);
    }
    pDC->SelectObject(pOldFont);
    listBox.ReleaseDC(pDC);
}

int CStudentsGUIDlg::getStudentSelect() const
{
    return m_ListStudents.GetCurSel();
}

int CStudentsGUIDlg::getGroupSelect() const
{
    return m_ListGroups.GetCurSel();
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyAdd()
{
    m_InputNewName.setTitle(__TEXT("Faculty"));
    m_InputNewName.setName(&m_Faculty.getNameClassList());

    deleteAllLists();

    if (m_InputNewName.DoModal() == TRUE)
    {
        setFacultyActions(TRUE);
    }
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyChange()
{
    m_InputNewName.setName(&m_Faculty.getNameClassList());
    m_InputNewName.DoModal();
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyGet()
{
    MessageBox(m_Faculty.getNameClassList().c_str(), __TEXT("Faculty name"), MB_ICONINFORMATION);
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyDelete()
{
    OnBnClickedButtonDeleteAllGroup();
    disableFaculty();
    m_Faculty.deleteAllElements();
}


void CStudentsGUIDlg::OnBnClickedButtonAddStudents()
{
    auto firstSelect = getGroupSelect();
    m_InputStudInform.setFaculty(&m_Faculty);
    m_InputStudInform.setChangeFlag(ADD);
    m_InputStudInform.setCurrentBranchIndex(firstSelect);
    m_InputStudInform.DoModal();
    auto selected = m_InputStudInform.getCurrentSelectedGroup();
    showGroups();
    
    if (selected != LB_ERR)
    {
        m_ListGroups.SetCurSel(selected);
        OnLbnSelchangeListGroups();
    }
}

void CStudentsGUIDlg::OnBnClickedButtonDelete()
{
    doAction(std::bind(&CStudentsGUIDlg::deleteSelectedGroup, this), std::bind(&CStudentsGUIDlg::deleteSelectedStudent, this), __TEXT("delete"));
}

void CStudentsGUIDlg::deleteSelectedStudent()
{
    m_CurrentGroup->deleteElement(*m_Student);
    if (!m_CurrentGroup->isEmpty())
    {
        m_CurrentGroup->setCurrentNodeOnTheBegin();
        m_Student = &m_CurrentGroup->getReferencesCurrentData();
    }
    else
    {
        deleteStudentList();
        setSelectedActions(FALSE);
        m_Student = NULL;
        GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
    }
    showStudent();
}

void CStudentsGUIDlg::deleteSelectedGroup()
{
    setSelectedActions(FALSE);
    GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
    m_Faculty.deleteElement(*m_CurrentGroup);
    if (!m_Faculty.isEmpty())
    {
        m_Faculty.setCurrentNodeOnTheBegin();
        m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
    }
    else
    {
        GetDlgItem(IDC_BUTTON_DELETE_ALL_GROUP)->EnableWindow(FALSE);
        deleteGroupList();
        deleteStudentList();
        setStudentActions(FALSE);
        setSelectedActions(FALSE);
        m_CurrentGroup = NULL;
    }
    showGroups();
    showStudent();
}

void CStudentsGUIDlg::OnBnClickedButtonDeleteAllStudents()
{
    m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
    m_CurrentGroup->deleteAllElements();
    deleteStudentList();
    setSelectedActions(TRUE);
    GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
    m_StudentName = __TEXT("");
    UpdateData(FALSE);
}

void CStudentsGUIDlg::OnBnClickedButtonAddGroup()
{
    NameList<Student> newGroup;
    m_InputNewName.setTitle(__TEXT("Group"));
    m_InputNewName.setName(&newGroup.getNameClassList());

    if (m_InputNewName.DoModal() == TRUE)
    {
        deleteAllLists();
        m_Faculty.pushInSortList(newGroup);
        setGroupActions(TRUE);
        setStudentActions(TRUE);
        setSelectedActions(FALSE);
        GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_DELETE_ALL_GROUP)->EnableWindow(TRUE);
    }
    showGroups();
}

void CStudentsGUIDlg::OnBnClickedButtonDeleteAllGroup()
{
    setStudentActions(FALSE);
    setGroupActions(FALSE);
    GetDlgItem(IDC_BUTTON_DELETE_ALL_GROUP)->EnableWindow(FALSE);
    GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT_GROUP)->SetWindowTextW(__TEXT(""));
    GetDlgItem(IDC_EDIT_STUDENT)->SetWindowTextW(__TEXT(""));
    setSelectedActions(FALSE);
    deleteStudentList();
    deleteGroupList();
    m_Faculty.deleteAllElements();
}

void CStudentsGUIDlg::OnEnChangeEditStudent()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_STUDENT)))->GetLine(0, buffer)] = 0;
    
    if ((search = m_ListStudents.FindString(-1, buffer)) != LB_ERR)
    {
        m_ListStudents.SetCurSel(search);
        OnLbnSelchangeListStudents();
    }
}

void CStudentsGUIDlg::OnLbnSelchangeListStudents()
{
    int selected = getStudentSelect();

    if (selected != LB_ERR && selected != m_OldStudSelect)
    {

        if (m_OldStudSelect == LB_ERR)
        {
            if ((m_OldStudSelect = selected >= (m_OldStudSelect = m_ListStudents.GetCount() - 1) >> 1 ? m_OldStudSelect : 0) == 0)
            {
                m_CurrentGroup->setCurrentNodeOnTheBegin();
            }
            else
            {
                m_CurrentGroup->setCurrentNodeOnTheEnd();
            }
        }

        for (; selected < m_OldStudSelect; --m_OldStudSelect, m_CurrentGroup->operator--());
        for (; selected > m_OldStudSelect; ++m_OldStudSelect, m_CurrentGroup->operator++());

        m_Student = &m_CurrentGroup->getReferencesCurrentData();
        showStudentInformation(*m_Student);
        setSelectedActions(TRUE);
    }
    GetDlgItem(IDC_BUTTON_CHANGE)->SetFocus();
    SetDefID(IDC_BUTTON_CHANGE);
}

void CStudentsGUIDlg::OnEnChangeEditGroup()
{
    int search;
    TCHAR buffer[MIN_BUF_SIZE];
    buffer[((CEdit*)(GetDlgItem(IDC_EDIT_GROUP)))->GetLine(0, buffer)] = 0;

    if ((search = m_ListGroups.FindString(-1, buffer)) != LB_ERR)
    {
        m_ListGroups.SetCurSel(search);
        OnLbnSelchangeListGroups();
    }
}

void CStudentsGUIDlg::OnLbnSelchangeListGroups()
{
    // TODO: Add your control notification handler code here
    int selected = getGroupSelect();

    if (selected != LB_ERR && selected != m_OldGroupSelect)
    {

        if (m_OldGroupSelect == LB_ERR)
        {
            if ((m_OldGroupSelect = selected >= (m_OldGroupSelect = m_ListGroups.GetCount() - 1) >> 1 ? m_OldGroupSelect : 0) == 0)
            {
                m_Faculty.setCurrentNodeOnTheBegin();
            }
            else
            {
                m_Faculty.setCurrentNodeOnTheEnd();
            }
        }

        for (; selected < m_OldGroupSelect; --m_OldGroupSelect, --m_Faculty);
        for (; selected > m_OldGroupSelect; ++m_OldGroupSelect, ++m_Faculty);

        m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
        showStudent();
        setSelectedActions(TRUE);
        if (m_Faculty.getReferencesCurrentData().isEmpty())
        {
            GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(FALSE);
        }
        else
        {
            GetDlgItem(IDC_BUTTON_DELETE_ALL_STUDENTS)->EnableWindow(TRUE);
        }
    }
    GetDlgItem(IDC_BUTTON_CHANGE)->SetFocus();
    SetDefID(IDC_BUTTON_CHANGE);
}

void CStudentsGUIDlg::showGroups()
{
    deleteGroupList();
    if (setGroupActions(!m_Faculty.isEmpty()))
    {
        m_Faculty.setCurrentNodeOnTheBegin();
        for (size_t i = 0; i < m_Faculty.getSize(); ++i)
        {
            m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
            showString(*m_CurrentGroup);
            ++m_Faculty;
        }
        m_Faculty.setCurrentNodeOnTheBegin();
        m_CurrentGroup = &m_Faculty.getReferencesCurrentData();
        m_OldGroupSelect = LB_ERR;
    }
}

void CStudentsGUIDlg::showString(NameList<Student>& group)
{
    CorrectListHScrlPart(m_ListGroups, m_MaxExtListGroup, m_ListGroups.AddString((LPCTSTR)group.getNameClassList().c_str()));
}

void CStudentsGUIDlg::deleteGroupList()
{
    m_ListGroups.ResetContent();
    CorrectListHScrlPart(m_ListGroups, m_MaxExtListGroup);
}

void CStudentsGUIDlg::OnBnClickedButtonChange()
{
    doAction(std::bind(&CStudentsGUIDlg::changeSelectedGroup, this), std::bind(&CStudentsGUIDlg::changeSelectedStudent, this), __TEXT("change"));
}

void CStudentsGUIDlg::changeSelectedGroup()
{
    m_InputNewName.setTitle(__TEXT("Group"));
    m_InputNewName.setName(&m_CurrentGroup->getNameClassList());
    if (m_InputNewName.DoModal() == TRUE)
    {
        m_Faculty.sort();
        auto select = changeItem(m_ListGroups, m_MaxExtListGroup, m_CurrentGroup->getNameClassList());
        auto selectStudent = m_Student != NULL && m_CurrentGroup->findValue(*m_Student) ? changeItem(m_ListStudents, m_MaxExtListStud, getStudentString(*m_Student)) : LB_ERR;
        showGroups();
        m_ListGroups.SetCurSel(select);
        OnLbnSelchangeListGroups();
        if (selectStudent != LB_ERR)
        {
            m_ListStudents.SetCurSel(selectStudent);
        }
    }
}

void CStudentsGUIDlg::changeSelectedStudent()
{
    m_InputStudInform.setFaculty(&m_Faculty);
    m_InputStudInform.setCurrentBranchIndex(getGroupSelect());
    m_InputStudInform.setStudent(m_Student);
    m_InputStudInform.setChangeFlag(CHANGE);
    if (m_InputStudInform.DoModal() == TRUE)
    {
        m_CurrentGroup->sort();
        auto select = changeItem(m_ListStudents, m_MaxExtListStud, getStudentString(*m_Student));
        showStudent();
        m_ListStudents.SetCurSel(select);
        OnLbnSelchangeListStudents();
    }
}

std::basic_string<TYPESTRING> CStudentsGUIDlg::getStudentString(Student& student)
{
    auto str(student.getSurname());
    auto lastName(student.getLastname());
    lastName.erase(std::remove(lastName.begin(), lastName.end(), __TEXT(' ')), lastName.end());
    str.append(__TEXT(" ")).append(student.getName().substr(0, 1)).append(__TEXT(". "));
    if (!lastName.empty())
    {
        str.append(lastName.substr(0, 1)).append(__TEXT("."));
    }
    return str;
}

void CStudentsGUIDlg::doAction(std::function<void()> groupAction, std::function<void()> studentAction, CString actionName)
{
    int selectedStudent = getStudentSelect();
    int selectedGroup = getGroupSelect();

    if (selectedGroup != LB_ERR && selectedStudent != LB_ERR)
    {
        m_SelectAction.setActionName(actionName);
        if (m_SelectAction.DoModal() == TRUE)
        {
            if (m_SelectAction.getAnswer() == GROUP_ANSWER)
            {
                groupAction();
            }
            else
            {
                studentAction();
            }
            return;
        }
    }

    if (selectedGroup != LB_ERR && selectedStudent == LB_ERR)
    {
        groupAction();
        return;
    }

    if (selectedGroup == LB_ERR && selectedStudent != LB_ERR)
    {
        studentAction();
    }
}
