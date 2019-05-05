#include "student.hpp"
#include <string>
#include "instruments.hpp"

Student::Student(std::string name, int vc, Instrument instrument, std::vector<int> availability)
{
    this->name = name;
    this->vc = vc;
    this->instrument = instrument;
    this->availability = availability;
}

std::string Student::getName()
{
    return this->name;
}

int Student::getVC()
{
    return this->vc;
}

Instrument Student::getInstrument()
{
    return this->instrument;
}

bool Student::isAvailable(int index)
{
    return this->availability[index];
}

bool operator<(Student &s1, Student &s2)
{
    return s1.getVC() > s2.getVC();
}