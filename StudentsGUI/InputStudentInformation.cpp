// InputStudentInformation.cpp : implementation file
//

#include "stdafx.h"
#include "StudentsGUI.h"
#include "InputStudentInformation.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(InputStudentInformation, CDialogEx)
END_MESSAGE_MAP()


// InputStudentInformation message handlers
