#include "student.hpp"
#include "reader.hpp"
#include <iostream>
#include <map>
#include <algorithm>
#include <functional>

// Helper method to return a user's input
int getValue() 
{
    int input;
    std::cin >> input;
    return input;
}
int main()
{
    std::string gigSurvey;              // User input path to gig survey file
    std::string vc;                     // User input path to vc file
    std::vector<std::string> gigList;   // Vector of gigs to be scheduled
    std::vector<Student> students;      // Vector of students who have given availability
    std::map<Instrument, int> instrumentation;   // Vector of the desired gig instrumentation

    // Initial welcome message and prompt for gig survey file and vc file
    std::cout << "Gig Survey File: ";
    std::cin >> gigSurvey;
    std::cout << "VC File: ";
    std::cin >> vc;
    std::cout << std::endl;

    // Call getGigList and getStudentList
    gigList = Reader::getGigList(gigSurvey);
    students = Reader::getStudentList(gigSurvey, vc, gigList);

    // Prompt to choose gig
    int choice;
    std::cout << "Select the gig you wish to schedule:" << std::endl;
    // indexed for loop so user can pick the index of the gig they want to schedule
    for (int i = 0; i < gigList.size(); i++)
    {
        std::cout << i + 1 << ". " << gigList.at(i) << std::endl;
    }
    std::cin >> choice;
    choice = choice - 1;    //Edit value so it is the correct index
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
    // Step 1. Fill map with vectors of instruments, and place all available students in the correct vectors
    // Step 2. Sort instrument vectors by the Student's VC counts, descending
    // Step 3. Fill the gig list with the amount of students specified by the instrumentation
    std::map<Instrument, std::vector<Student>> instruments;
    std::map<Instrument, std::vector<std::string>> finalList;
    Student saylix = Student("Saylix", 6, OTHER, {});
    Student knox = Student("KNox", 8, DRUMS, {});
    Student olli = Student("Olli", 2, DRUMS, {});
    Student rosie = Student("Rosie", 4, OTHER, {});
    students.push_back(rosie);
    students.push_back(olli);
    students.push_back(knox);
    students.push_back(saylix);

    // Step 1
    for (auto &student : students)
    {
        if (instruments.find(student.getInstrument()) == instruments.end())
        {
            instruments.insert({student.getInstrument(), {}});
        }
        instruments.find(student.getInstrument())->second.push_back(student);
    }
    // Steps 2 & 3
    for (std::map<Instrument, std::vector<Student>>::iterator it = instruments.begin(); it != instruments.end(); it++)
    {
        Instrument instrument = it->first;
        // Step 2
        std::sort(it->second.begin(), it->second.end());
        // Step 3
        finalList.insert({instrument, {}});
        for (int i = 0; i < it->second.size(); i++)
        {
            if (i == instrumentation.find(instrument)->second)
            {
                break;
            }
            finalList.find(instrument)->second.push_back(it->second.at(i).getName());
        }
    }
    for (std::map<Instrument, std::vector<std::string>>::iterator it = finalList.begin(); it != finalList.end(); it++)
    {
        for (int i = 0; i < it->second.size(); i++)
        {
            std::cout << it->second.at(i) << std::endl;
        }
    }


    // Print gig list and save to file
}