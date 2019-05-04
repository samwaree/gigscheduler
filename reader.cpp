<<<<<<< HEAD
//#include "csv.h"
=======
>>>>>>> 34d00d579e23ce8f500198dfffffdf39127f1812
#include "parser.hpp"
#include "reader.hpp"
#include "student.hpp"
#include "instruments.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>

const int FIRST_DATA_ROW = 3;
const int NAME_COL = 18;
const int INSTRUMENT_COL = 20;
const int FIRST_GIG_COL = 24;
const int NUM_EXTRA_COLS = 2;

Instrument getEnumFromString(std::string instrumentString) {
    // Define a static dictionary to convert instrument strings into instruments
    static std::map<std::string, Instrument> enumMap {
        {"Trumpet 1", TRUMPET1},
        {"Trumpet 2", TRUMPET2},
        {"Trumpet 3", TRUMPET3},
        {"Trombone 1", BONE1},
        {"Trombone 2", BONE2},
        {"Trombone 3", BONE3},
        {"Tuba", TUBA},
        {"Drums", DRUMS},
        {"Other", OTHER}
    };

    return enumMap[instrumentString];

}

int getNumResponse(std::string response) {
    if (response == "Yes")
    {
        return 1;
    }
    else if (response == "No")
    {
        return 0;
    }
    else //For Testing
    {
        // Parsing failed
        return -1;
    }
}

std::vector<Student> Reader::getStudentList(std::string gigFileName, std::string vcFileName)
{
    std::vector<Student> studentVector;
    std::ifstream gigStream(gigFileName);
    aria::csv::CsvParser gigParser(gigStream);

    int rowCount = 0;
    for (auto &row : gigParser)
    {
        if (rowCount >= FIRST_DATA_ROW) 
        {
            std::vector<int> availability;
            for (int i = FIRST_GIG_COL; i < row.size() - NUM_EXTRA_COLS; i++) {
                availability.push_back(getNumResponse(row[i]));
            }
            studentVector.push_back(Student(row[NAME_COL], 0, getEnumFromString(row[INSTRUMENT_COL]), availability));
        }
        rowCount++;
    }

    return studentVector;
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