#include "student.hpp"
#include "reader.hpp"
#include <iostream>

int main()
{
    std::string gigSurvey;              // User input path to gig survey file
    std::string vc;                     // User input path to vc file
    std::vector<std::string> gigList;   // Vector of gigs to be scheduled
    std::vector<Student> students;      // Vector of students who have given availability


    // Initial welcome message and prompt for gig survey file and vc file
    std::cout << "Gig Survey File: ";
    std::cin >> gigSurvey;
    std::cout << "VC File: ";
    std::cin >> vc;

    // Call getGigList and getStudentList
    gigList = Reader::getGigList(gigSurvey);
    students = Reader::getStudentList(gigSurvey, vc, gigList);

    // Prompt to choose gig
    int choice;
    std::cout << "Select the gig you wish to schedule:" << std::endl;
    // indexed for loop so user can pick the index of the gig they want to schedule
    for (int i = 0; i < gigList.size(); i++) {
        std::cout << i + 1 << " " << gigList.at(i);
    }
    std::cin >> choice;
    std::cout  << gigList.at(choice);

    // Prompt for instrumentation manually in command line
    // Do some magic to get gig list
    // Print gig list and save to file
}