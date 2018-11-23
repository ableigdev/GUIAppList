#pragma once

#include "Iterator.h"
#include "List.h"
#include "afxwin.h"

namespace common
{
    template <typename TypeOfList>
    void for_each_listbox(Iterator<TypeOfList> list, CListBox& listbox, int& oldSelect, int& selected)
    {
        if (oldSelect == LB_ERR)
        {
            (oldSelect = selected >= (oldSelect = listbox.GetCount() - 1) >> 1 ? oldSelect : 0) == 0 ? list.getPointer()->setCurrentNodeOnTheBegin() : list.getPointer()->setCurrentNodeOnTheEnd();
        }

        for (; selected < oldSelect; --oldSelect, --list);
        for (; selected > oldSelect; ++oldSelect, ++list);
    }

    class CorrectScroll
    {
    public:
        static void correctListHScrlPart(CListBox& listBox, int& maxExtCx, int& fontAverageChar, int index = 0);
        static void correctListHScrlDel(CListBox& listBox, int& maxExtCx, int& fontAverageChar, int index);
    };
}