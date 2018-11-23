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