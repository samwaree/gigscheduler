#include "parser.hpp"
#include "reader.hpp"
#include "student.hpp"
#include "instruments.hpp"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

const int FIRST_GIG_DATA_ROW = 3;
const int FIRST_VC_DATA_ROW = 1;
const int NAME_COL = 18;
const int INSTRUMENT_COL = 20;
const int FIRST_GIG_COL = 24;
const int NUM_EXTRA_COLS = 2;

// Define a static dictionary to convert instrument strings into instruments
Instrument getEnumFromString(std::string instrumentString) {
    static std::map < std::string,
    Instrument > enumMap {
        {
            "Trumpet 1",
            TRUMPET1
        }, {
            "Trumpet 2",
            TRUMPET2
        }, {
            "Trumpet 3",
            TRUMPET3
        }, {
            "Trombone 1",
            BONE1
        }, {
            "Trombone 2",
            BONE2
        }, {
            "Trombone 3",
            BONE3
        }, {
            "Tuba",
            TUBA
        }, {
            "Drums",
            DRUMS
        }, {"Other", OTHER}
    };

    return enumMap[instrumentString];

}

// Convert Yes and No into 1 and 0. Everything else results in -1
int getNumResponse(std::string response) {
    if (response == "Yes") {
        return 1;
    } else if (response == "No") {
        return 0;
    } else { // Parsing failed
        return -1;
    }
}

// Produce a vector of Student objects from <gigFileName> and <vcFileName>
std::vector<Student> Reader::getStudentList(
        std::string gigFileName, std::string vcFileName) {
    std::vector<Student> studentVector;

    // Create a parser object from the gig survey results
    std::ifstream gigStream(gigFileName);
    aria::csv::CsvParser gigParser(gigStream);

    // Loop through each row in the csv file
    int rowCount = 0;
     // Only take data from rows that aren't headers
    for (auto & row : gigParser) {
         // Record the student's gig responses in a vector
        if (rowCount >= FIRST_GIG_DATA_ROW) {
            std::vector<int> availability;
            for (int i = FIRST_GIG_COL; i < row.size() - NUM_EXTRA_COLS; i++) {
                availability.push_back(getNumResponse(row[i]));
            }
            // Create a new student with all of the information that we get
            // from the gig survey leaving VC at 0 and add it to the vector
            studentVector.push_back(Student(row[NAME_COL], 0, 
                getEnumFromString(row[INSTRUMENT_COL]), availability));
        }
        rowCount ++;
    }

    // Close the file stream
    gigStream.close();


    // Loop through each student in the vector and update their VC
    // Create a Parser from the VC file
    for (Student & student : studentVector) {
        std::ifstream vcStream(vcFileName);
        aria::csv::CsvParser vcParser(vcStream);

        int rowCount1 = 0;
        // Find the row in the file that has a name matching the student's
        aria::csv::CsvParser::iterator rowItr = std::find_if(
            vcParser.begin(), vcParser.end(), 
            [&](std::vector < std::string > const & row) -> bool {
            return row[0] == student.getName();
        });

        // If a name is found, update the student with the file's VC value
        if (rowItr != vcParser.end()) {
            student.setVC(std::stoi(( * rowItr)[2]));
        }

        // Clase the file Stream
        vcStream.close();
    }

    return studentVector;
}

std::vector < std::string > Reader::getGigList(std::string fileName) {
    std::vector < std::string > vect;
    std::ifstream f(fileName);
    aria::csv::CsvParser parser(f);

    // Adds all the fields from the second row, 25 columns in and onward
    int rowCount = 0;
    for (auto & row : parser) {
        int fieldCount = 0;
        if (rowCount == 1) {
            for (auto & field : row) {
                if (fieldCount >= 24) {
                    vect.push_back(field);
                }
                fieldCount ++;
            }
        }
        rowCount ++;
    }

    // The last two fields, as they are not gigs
    vect.pop_back();
    vect.pop_back();

    return vect;
}
