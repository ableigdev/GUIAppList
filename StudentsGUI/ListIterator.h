#pragma once

#include "List.h"

template <typename NODETYPE>
class ListIterator
{
public:
    ListIterator(const List<NODETYPE>&);
    ListIterator(const ListIterator<NODETYPE>&);

    ListIterator<NODETYPE>& operator++();
    ListIterator<NODETYPE>& operator--();
    bool operator!();
    ListIterator<NODETYPE>& operator=(const ListIterator<NODETYPE>&);
    ListIterator<NODETYPE>& operator=(const List<NODETYPE>&);
    NODETYPE operator*();
private:
    typename List<NODETYPE>::ListNode<NODETYPE>* m_Ptr;
    size_t m_Index;
    size_t m_Size;
};

template <typename NODETYPE>
ListIterator<NODETYPE>::ListIterator(const List<NODETYPE>& list)
    : m_Ptr(list.firstPtr),
    m_Index(0),
    m_Size(list.m_Size)
{

}

template <typename NODETYPE>
ListIterator<NODETYPE>::ListIterator(const ListIterator<NODETYPE>& iterator)
    : m_Ptr(iterator.m_Ptr),
    m_Index(iterator.m_Index),
    m_Size(iterator.m_Size)
{

}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator=(const ListIterator<NODETYPE>& right)
{
    if (this != &right)
    {
        m_Index = right.m_Index;
        m_Size = right.m_Size;
        m_Ptr = right.m_Ptr;
    }
    return *this;
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator=(const List<NODETYPE>& right)
{
    if (this != &right)
    {
        m_Ptr = right.firstPtr;
    }
    return *this;
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator++()
{
    if (m_Ptr != 0)
    {
        m_Ptr = m_Ptr->nextPtr;
        ++m_Index;
    }
    return *this;
}

template <typename NODETYPE>
ListIterator<NODETYPE>& ListIterator<NODETYPE>::operator--()
{
    if (m_Ptr != 0)
    {
        m_Ptr = m_Ptr->prevPtr;
        --m_Index;
    }
    return *this;
}

template <typename NODETYPE>
bool ListIterator<NODETYPE>::operator!()
{
    return m_Index < m_Size;
}

template <typename NODETYPE>
NODETYPE ListIterator<NODETYPE>::operator*()
{
    if (m_Ptr == 0)
    {
        throw ReadAccessViolation();
    }
    return m_Ptr->data;
}

