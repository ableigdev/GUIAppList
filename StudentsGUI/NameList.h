#pragma once

#include "List.h"
#include <string>

template <typename NODETYPE>
class NameList : public List<NODETYPE>
{
public:
    NameList();
    explicit NameList(const std::basic_string<TYPESTRING>&);
    explicit NameList(const NameList<NODETYPE>&);
    virtual ~NameList() = default;

    void setNameClassList(const std::basic_string<TYPESTRING>&);
    std::basic_string<TYPESTRING> getNameClassList() const;
    std::basic_string<TYPESTRING>& getNameClassList();

    const NameList<NODETYPE>& operator=(const NameList<NODETYPE>&);

    bool operator==(const NameList<NODETYPE>&) const;
    bool operator!=(const NameList<NODETYPE>&) const;
    bool operator>=(const NameList<NODETYPE>&) const;
    bool operator<=(const NameList<NODETYPE>&) const;
    bool operator>(const NameList<NODETYPE>&) const;
    bool operator<(const NameList<NODETYPE>&) const;
private:
    std::basic_string<TYPESTRING> m_NameList;
};

template <typename NODETYPE>
NameList<NODETYPE>::NameList()
{
    m_NameList.resize(80);
}

template <typename NODETYPE>
NameList<NODETYPE>::NameList(const std::basic_string<TYPESTRING>& str)
    : List(),
    m_NameList(str)
{

}

template <typename NODETYPE>
NameList<NODETYPE>::NameList(const NameList<NODETYPE>& right)
    : List(),
    m_NameList(right.m_NameList)
{
    *this = right;
}

template <typename NODETYPE>
void NameList<NODETYPE>::setNameClassList(const std::basic_string<TYPESTRING>& str)
{
    m_NameList = str;
}

template <typename NODETYPE>
std::basic_string<TYPESTRING> NameList<NODETYPE>::getNameClassList() const
{
    return m_NameList;
}

template <typename NODETYPE>
std::basic_string<TYPESTRING>& NameList<NODETYPE>::getNameClassList()
{
    return m_NameList;
}

template <typename NODETYPE>
const NameList<NODETYPE>& NameList<NODETYPE>::operator=(const NameList<NODETYPE>& right)
{
    if (this != &right)
    {
        List<NODETYPE>::operator=(right);
        m_NameList = right.m_NameList;
    }
    return *this;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator==(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) == 0;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator!=(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) != 0;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator>=(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) >= -1;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator<=(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) <= 1;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator>(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) == 1;
}

template <typename NODETYPE>
bool NameList<NODETYPE>::operator<(const NameList<NODETYPE>& rList) const
{
    return m_NameList.compare(rList.m_NameList) == -1;
}