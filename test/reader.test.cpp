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

    auto vect1 = Reader::getStudentList(fileName, "vc.csv");
    for (auto itr = vect1.begin(); itr != vect1.end(); itr++) {
        std::cout << itr -> getName() << " : ";
        std::cout << itr -> getVC() << " : ";
        std::cout << itr -> getInstrument() << " : ";
        for (int i = 0; i < 4; i++) 
        {
            std::cout << itr -> isAvailable(i) << " ";
        }
        std::cout << std::endl;
    }
}