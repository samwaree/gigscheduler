#include "parser.hpp"
#include "reader.hpp"
#include "student.hpp"
#include "instruments.hpp"
#include <string>
#include <vector>
#include <iostream>

static std::vector<Student> getStudentList(std::string fileName, std::vector<std::string> gigList) {
    std::vector<Student> studentList; //Create student vector
    

}

std::vector<std::string> Reader::getGigList(std::string fileName)
{
    std::vector<std::string> vect;
    std::ifstream f(fileName);
    aria::csv::CsvParser parser(f);

    // Adds all the fields from the second row, 25 columns in and onward
    int rowCount = 0;
    for (auto &row : parser)
    {
        int fieldCount = 0;
        if (rowCount == 1)
        {
            for (auto &field : row)
            {
                if (fieldCount >= 24)
                {
                    vect.push_back(field);
                }
                fieldCount++;
            }
        }
        rowCount++;
    }

    // The last two fields, as they are not gigs
    vect.pop_back();
    vect.pop_back();

    return vect;
}