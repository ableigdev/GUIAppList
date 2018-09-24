#include "stdafx.h"
#include "Student.h"
#include "constants.h"

Student::Student()
    : m_BirthYear(0),
    m_AverageGrade(0.0)
{
    m_Name.resize(STRING_SIZE);
    m_Surname.resize(STRING_SIZE);
    m_Lastname.resize(STRING_SIZE);
}

Student::Student(const Student& someStudent)
    : m_Name(someStudent.m_Name),
    m_Surname(someStudent.m_Surname),
    m_Lastname(someStudent.m_Lastname),
    m_BirthYear(someStudent.m_BirthYear),
    m_AverageGrade(someStudent.m_AverageGrade)
{

}

void Student::setName(const std::basic_string<TYPESTRING>& name)
{
    m_Name = name;
}

std::basic_string<TYPESTRING> Student::getName() const
{
    return m_Name;
}

void Student::setSurname(const std::basic_string<TYPESTRING>& surname)
{
    m_Surname = surname;
}

std::basic_string<TYPESTRING> Student::getSurname() const
{
    return m_Surname;
}

void Student::setLastname(const std::basic_string<TYPESTRING>& lastname)
{
    m_Lastname = lastname;
}

std::basic_string<TYPESTRING> Student::getLastname() const
{
    return m_Lastname;
}

void Student::setBirthYear(int year)
{
    m_BirthYear = year;
}

short int Student::getBirthYear() const
{
    return m_BirthYear;
}

void Student::setAverageGrade(float averageGrade)
{
    m_AverageGrade = averageGrade;
}

float Student::getAverageGrade() const
{
    return m_AverageGrade;
}

const Student& Student::operator=(const Student& right)
{
    if (this != &right)
    {
        m_Name = right.m_Name;
        m_Surname = right.m_Surname;
        m_Lastname = right.m_Lastname;
        m_BirthYear = right.m_BirthYear;
        m_AverageGrade = right.m_AverageGrade;
    }

    return *this;
}

int Student::compareStudents(const Student& right) const
{
    int result = m_Surname.compare(right.m_Surname);

    if (result == 0)
    {
        result = m_Name.compare(right.m_Name);

        if (result == 0)
        {
            return m_Lastname.compare(right.m_Lastname);
        }
    }

    return result;
}

bool Student::operator==(const Student& right) const
{
    return compareStudents(right) == 0;
}

bool Student::operator!=(const Student& right) const
{
    return compareStudents(right) != 0;
}

bool Student::operator>=(const Student& right) const
{
    return compareStudents(right) != -1;
}

bool Student::operator<=(const Student& right) const
{
    return compareStudents(right) != 1;
}

bool Student::operator>(const Student& right) const
{
    return compareStudents(right) == 1;
}

bool Student::operator<(const Student& right) const
{
    return compareStudents(right) == -1;
}

listStream& operator<<(listStream& output, const Student& right)
{
    output << right.m_Surname << __T(" ") << right.m_Name << __T(" ")
        << right.m_Lastname << __T(" ") << right.m_BirthYear << __T(" ")
        << right.m_AverageGrade << std::endl;

    return output;
}

listInStream& operator >> (listInStream& input, Student& right)
{
    input >> right.m_Surname >> right.m_Name >> right.m_Lastname
        >> right.m_BirthYear >> right.m_AverageGrade;

    return input;
}
