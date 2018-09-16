
// StudentsGUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "StudentsGUIDlg.h"
#include "afxdialogex.h"
#include "constants.h"

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
    CWnd* wnd = GetDlgItem(IDC_BUTTON_FACULTY_ADD);
    if (wnd != NULL)
    {
        wnd->SetFocus();
    }
    disableFaculty();
    setSelectedActions();

    CString* str = new CString[50];
    //Input.Title = __TEXT("group");
    //Input.m_Name = str;

    m_InputStudInform.setListBoxGroupList(&m_ListGroups);
    m_InputNewName.setTitle(__TEXT("group"));
    //m_InputNewName.setName((CString*)m_Group.getNameClassList().c_str());
    m_InputNewName.setName(str);
    m_InputStudInform.setGroup(&m_Group);
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
    setSelectedActions();
    GetDlgItem(IDC_BUTTON_ADD_STUDENTS)->SetFocus();
}

void CStudentsGUIDlg::deleteStudentInformationList()
{
    m_ListStudInfo.ResetContent();
    CorrectListHScrl(m_ListStudInfo);
}

void CStudentsGUIDlg::deleteAllLists()
{
    deleteStudentList();
}

void CStudentsGUIDlg::setFacultyActions(BOOL state)
{
    WORD wID[] = 
    { 
        IDC_BUTTON_FACULTY_CHANGE, 
        IDC_BUTTON_FACULTY_DELETE,
        IDC_BUTTON_FACULTY_GET,
        IDC_BUTTON_ADD_STUDENTS
    };
    setButtonState(wID, _LEN(wID, WORD), TRUE);
    setAddFacultyActions(!state);
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
        IDC_BUTTON_DELETE_ALL_STUDENTS,
        IDC_EDIT_STUDENT,
        IDC_LIST_STUDENTS,
        IDC_LIST_STUD_INFO
    };
    setButtonState(wID, _LEN(wID, WORD), state);
    return state;
}

void CStudentsGUIDlg::setSelectedActions()
{
    WORD wID[] =
    {
        IDC_BUTTON_DELETE,
        IDC_BUTTON_CHANGE
    };
    setButtonState(wID, _LEN(wID, WORD), getStudentSelect() != LB_ERR);
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


// TODO: Need refactor
void CStudentsGUIDlg::OutStr(Student& student)
{
    CorrectListHScrlPart(m_ListStudents, m_MaxExtListStud, m_ListStudents.AddString((LPCTSTR)student.getName().c_str()));
}

void CStudentsGUIDlg::showStudent()
{
    deleteStudentList();
    if (setStudentActions(!m_Group))
    {
        m_Group.setCurrentNodeOnTheBegin();
        for (size_t i = 0; i < m_Group.getSize(); ++i)
        {
            m_Student = &m_Group.getReferencesCurrentData();
            OutStr(*m_Student);
            ++m_Group;
        }
        m_Group.setCurrentNodeOnTheBegin();
        m_Student = &m_Group.getReferencesCurrentData();
        showStudentInformation(*m_Student);
        m_OldStudSelect = LB_ERR;
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
    CorrectListHScrlDel(listBox, maxExtCx, currentSelect);
    listBox.SetCurSel(currentSelect = listBox.AddString(name.c_str()));
    CorrectListHScrlPart(listBox, maxExtCx, currentSelect);
    return currentSelect;
}

void CStudentsGUIDlg::deleteStudent()
{
    m_Group.deleteElement(m_Group.getValueCurrentData());
    if (!m_Group)
    {
        m_Student = &m_Group.getReferencesCurrentData();
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
        m_Group.sortCurrentNodePtr();
        m_OldStudSelect = changeItem(m_ListStudents, m_MaxExtListStud, m_Student->getSurname().c_str());
        showStudentInformation(*m_Student);
    }
}

void CStudentsGUIDlg::showStudentInformation(const Student& student)
{
    CString buf;
    deleteStudentInformationList();

    buf.Format(__TEXT("Surname      : %s"), student.getSurname());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Name      : %s"), student.getName());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Lastname      : %s"), student.getLastname());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Birth Year      : %i"), student.getBirthYear());
    m_ListStudInfo.AddString((LPCTSTR)buf);
    buf.Format(__TEXT("Average Grade      : %s"), student.getAverageGrade());
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

void CStudentsGUIDlg::OnBnClickedButtonFacultyAdd()
{
    deleteAllLists();

    if (m_InputNewName.DoModal() == TRUE)
    {
        setFacultyActions(TRUE);
    }

    SetFocus();
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyChange()
{
    m_InputNewName.DoModal();
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyGet()
{
    MessageBox(m_Group.getNameClassList().c_str(), __TEXT("Faculty name"));
}

void CStudentsGUIDlg::OnBnClickedButtonFacultyDelete()
{
    // TODO: OnButtonDeleteallstud();
    disableFaculty();
}


void CStudentsGUIDlg::OnBnClickedButtonAddStudents()
{
    // TODO: Add your control notification handler code here
    m_InputStudInform.setChangeFlag(ADD);
    m_InputStudInform.DoModal();
    showStudent();
}

void CStudentsGUIDlg::OnBnClickedButtonDelete()
{
    // TODO: Add your control notification handler code here
    deleteStudent();
}

void CStudentsGUIDlg::OnBnClickedButtonDeleteAllStudents()
{
    // TODO: Add your control notification handler code here
    m_Group.deleteAllElements();
    deleteStudentList();
    setStudentActions(FALSE);
    m_StudentName = __TEXT("");
    UpdateData(FALSE);
}
