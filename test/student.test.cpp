#include "..\student.hpp"
#include "..\instruments.hpp"
#include <iostream>
#include <assert.h>

int main()
{
    std::string name = "Test";
    Instrument instrument = DRUMS;
    int vc = 10;
    std::vector<int> availability;
    availability.push_back(0);
    availability.push_back(1);
    Student test(name, vc, instrument, availability);
    assert(test.getName().compare("Test") == 0);
    assert(test.getInstrument() == DRUMS);
    assert(test.getVC() == 10);
    assert(test.isAvailable(0) == false);
    assert(test.isAvailable(1));
}