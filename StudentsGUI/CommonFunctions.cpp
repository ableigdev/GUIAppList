#include "stdafx.h"
#include "CommonFunctions.h"

void common::CorrectScroll::correctListHScrlPart(CListBox& listBox, int& maxExtCx, int& fontAverageChar, int index)
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

        if ((isModify = sz.cx + fontAverageChar > maxExtCx))
        {
            maxExtCx = sz.cx + fontAverageChar;
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

CString common::getStudentString(Student& student)
{
    CString str1(student.getSurname().c_str());
    str1.Append(__TEXT(" "));
    str1.Append(student.getName().substr(0, 1).c_str());
    str1.Append(__TEXT(". "));
    if (!student.getLastname().empty())
    {
        str1.Append(student.getLastname().substr(0, 1).c_str());
        str1.Append(__TEXT("."));
    }
    return str1;
}

void common::CorrectScroll::correctListHScrlDel(CListBox& listBox, int& maxExtCx, int& fontAverageChar, int index)
{
    CDC* pDC = listBox.GetDC();
    CFont* pOldFont = pDC->SelectObject(listBox.GetFont());
    CString str;
    CSize sz;

    listBox.GetText(index, str);
    sz = pDC->GetTextExtent(str);
    listBox.DeleteString(index);
    if (sz.cx + fontAverageChar == maxExtCx)
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
        maxExtCx += fontAverageChar;
        listBox.SetHorizontalExtent(maxExtCx);
    }
    pDC->SelectObject(pOldFont);
    listBox.ReleaseDC(pDC);
}