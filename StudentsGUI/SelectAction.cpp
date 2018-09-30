// SelectAction.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "SelectAction.h"
#include "afxdialogex.h"


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
END_MESSAGE_MAP()


// SelectAction message handlers
void SelectAction::setActionName(const std::basic_string<TYPESTRING>& name)
{
    m_ActionName = name;
}

void SelectAction::setGroupName(const std::basic_string<TYPESTRING>& name)
{
    m_GroupName = name;
}

void SelectAction::setStudentName(const std::basic_string<TYPESTRING>& name)
{
    m_StudentName = name;
}