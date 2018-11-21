#pragma once

#include "List.h"

template <typename TypeOfClass>
class Iterator
{
public:
    explicit Iterator(List<TypeOfClass>* list);
    ~Iterator() = default;

    List<TypeOfClass>& operator++();
    List<TypeOfClass>& operator--();
    List<TypeOfClass>* getPointer();

private:
    List<TypeOfClass>* m_List;
};

template <typename TypeOfClass>
Iterator<TypeOfClass>::Iterator(List<TypeOfClass>* list)
    : m_List(list)
{

}

template <typename TypeOfClass>
List<TypeOfClass>& Iterator<TypeOfClass>::operator++()
{
    return ++*m_List;
}

template <typename TypeOfClass>
List<TypeOfClass>& Iterator<TypeOfClass>::operator--()
{
    return --*m_List;
}

template <typename TypeOfClass>
List<TypeOfClass>* Iterator<TypeOfClass>::getPointer()
{
    return m_List;
}