#include "student.hpp"
#include "reader.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>

// Helper method to return a user's input
int getValue()
{
    int input;
    std::cin >> input;
    return input;
}
int main()
{
    std::string gigSurvey;            // User input path to gig survey file
    std::string vc;                   // User input path to vc file
    std::vector<std::string> gigList; // Vector of gigs to be scheduled
    std::vector<Student> students;    // Vector of available students
    std::map<Instrument, int> instrumentation;
    // Vector of the desired instrumentation

    // Initial welcome message and prompt for gig survey file and vc file
    std::cout << "Gig Survey File: ";
    std::cin >> gigSurvey;
    std::cout << "VC File: ";
    std::cin >> vc;
    std::cout << std::endl;

    // Call getGigList and getStudentList
    gigList = Reader::getGigList(gigSurvey);
    students = Reader::getStudentList(gigSurvey, vc);

    // Prompt to choose gig
    int choice;
    std::cout << "Select the gig you wish to schedule:" << std::endl;
    // indexed for loop so user can pick gig's index they want to schedule
    for (int i = 0; i < gigList.size(); i++)
    {
        std::cout << i + 1 << ". " << gigList.at(i) << std::endl;
    }
    std::cin >> choice;
    choice = choice - 1; // Edit value so it is the correct index
    std::cout << std::endl;

    // Prompt for instrumentation manually in command line
    std::cout << "CHOOSE INSTRUMENTATION" << std::endl;
    std::cout << "Trumpet 1?: ";
    instrumentation.insert({TRUMPET1, getValue()});
    std::cout << "Trumpet 2?: ";
    instrumentation.insert({TRUMPET2, getValue()});
    std::cout << "Trumpet 3?: ";
    instrumentation.insert({TRUMPET3, getValue()});
    std::cout << "Trombone 1?: ";
    instrumentation.insert({BONE1, getValue()});
    std::cout << "Trombone 2?: ";
    instrumentation.insert({BONE2, getValue()});
    std::cout << "Trombone 3?: ";
    instrumentation.insert({BONE3, getValue()});
    std::cout << "Tuba?: ";
    instrumentation.insert({TUBA, getValue()});
    std::cout << "Drums?: ";
    instrumentation.insert({DRUMS, getValue()});
    std::cout << "Other?: ";
    instrumentation.insert({OTHER, getValue()});

    // Do some magic to get gig list
    // Algorithm is hardcoded here to have access to the user's choice
    // Step 1. Fill map with vectors of instruments,
    // and place all available students in their instrument vectors
    // Step 2. Sort each instrument vector by student's VC count, descending
    // Step 3. Fill the gig list with the number of students
    // specified by the instrumentation
    std::map<Instrument, std::vector<Student>> instruments; //student vec's
    std::map<Instrument, std::vector<std::string>> finalListVec;
    //Vectors of chosen students

    // Step 1
    for (auto &student : students)
    {
        //Create instrument vector if not in map
        if (instruments.find(student.getInstrument()) == instruments.end())
        {
            instruments.insert({student.getInstrument(), {}});
        }
        //Add student to their appropriate instrument if they are available
        if (student.isAvailable(choice))
        {
            instruments.find(
                           student.getInstrument())
                ->second.push_back(student);
        }
    }
    // Steps 2 & 3
    for (std::map<Instrument, std::vector<Student>>::iterator it =
             instruments.begin();
         it != instruments.end(); it++)
    {
        Instrument instrument = it->first; // Instrument for readability
        // Step 2
        std::sort(it->second.begin(), it->second.end()); // Sort by VC
        // Step 3
        // Create new vector of the current instrument to fill
        finalListVec.insert({instrument, {}});
        for (int i = 0; i < it->second.size(); i++)
        {
            if (i == instrumentation.find(instrument)->second)
            {
                // Stop loop if we have reached our instrumentation limit
                break;
            }
            // Place student into the final instrument vector
            finalListVec.find(instrument)->second.push_back(it->second.at(i).getName());
        }
    }

    // Print gig list
    std::cout << "Final Gig List:" << std::endl;
    // Indexed for loop to call the instruments in order of their enumeration
    std::vector<std::string> finalList;
    for (int i = 0; i < 9; i++)
    {
        // Variable declarations for readability
        Instrument instrument = static_cast<Instrument>(i);
        std::vector<std::string> students =
            finalListVec.find(instrument)->second;
        int capacity = instrumentation.find(instrument)->second;
        // Place all available students in the Final List
        for (auto &string : students)
        {
            finalList.push_back(string);
        }
        // If we have fewer available students than instrumentation asks for,
        // Add "need *instrument*" statements
        if (students.size() < instrumentation.find(instrument)->second)
        {
            for (int j = 0; j < capacity - students.size(); j++)
            {
                finalList.push_back("Need " + textOfEnum(instrument));
            }
        }
    }

    //Print out the Final List and save to output file
    std::ofstream out("output.txt");
    for (auto &string : finalList)
    {
        out << string << std::endl;
        std::cout << string << std::endl;
    }
    out.close();
    std::cout << "Final List printed to output.txt" << std::endl;
}
