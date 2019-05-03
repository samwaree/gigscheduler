#include "../reader.hpp"
#include <iostream>
#include <assert.h>
#include <string>

int main()
{
    std::string fileName = "test.csv";
    auto vect = Reader::getGigList(fileName);
    for (auto itr = vect.begin(); itr != vect.end(); itr++)
    {
        std::cout << *itr;
        std::cout << "\n";
    }
    assert(vect.size() == 4);
}