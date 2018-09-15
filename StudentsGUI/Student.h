#pragma once

#include <string>
#include <iostream>
#include <tchar.h>
#include "TypeStream.h"

class Student
{
public:
    Student();
    Student(const Student&);

    void setName(const std::basic_string<TYPESTRING>&);
    std::basic_string<TYPESTRING> getName() const;

    void setSurname(const std::basic_string<TYPESTRING>&);
    std::basic_string<TYPESTRING> getSurname() const;

    void setLastname(const std::basic_string<TYPESTRING>&);
    std::basic_string<TYPESTRING> getLastname() const;

    void setBirthYear(int);
    short int getBirthYear() const;

    void setAverageGrade(float);
    float getAverageGrade() const;

    const Student& operator=(const Student&);
    bool operator==(const Student&) const;
    bool operator!=(const Student&) const;
    bool operator>=(const Student&) const;
    bool operator<=(const Student&) const;
    bool operator>(const Student&) const;
    bool operator<(const Student&) const;

    friend listStream& operator<<(listStream&, const Student&);
    friend listInStream& operator >> (listInStream&, Student&);

private:
    int compareStudents(const Student&) const;

private:
    std::basic_string<TYPESTRING> m_Name{};
    std::basic_string<TYPESTRING> m_Surname{};
    std::basic_string<TYPESTRING> m_Lastname{};
    short int m_BirthYear;
    float m_AverageGrade;
};
