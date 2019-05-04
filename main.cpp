#include "student.hpp"
#include "reader.hpp"
#include <iostream>

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
    std::vector<int> instrumentation;   // Vector of the desired gig instrumentation


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
    // indexed for loop so user can pick the index of the gig they want to schedule
    for (int i = 0; i < gigList.size(); i++) {
        std::cout << i + 1 << ". " << gigList.at(i) << std::endl;
    }
    std::cin >> choice;
    choice = choice - 1;    //Edit value so it is the correct index
    std::cout << std::endl;

    // Prompt for instrumentation manually in command line
    std::cout << "CHOOSE INSTRUMENTATION" << std::endl;
    std::cout << "Trumpet 1?: ";
    instrumentation.push_back(getValue());
    std::cout << "Trumpet 2?: ";
    instrumentation.push_back(getValue());
    std::cout << "Trumpet 3?: ";
    instrumentation.push_back(getValue());
    std::cout << "Trombone 1?: ";
    instrumentation.push_back(getValue());
    std::cout << "Trombone 2?: ";
    instrumentation.push_back(getValue());
    std::cout << "Trombone 3?: ";
    instrumentation.push_back(getValue());
    std::cout << "Tuba?: ";
    instrumentation.push_back(getValue());
    std::cout << "Drums?: ";
    instrumentation.push_back(getValue());
    std::cout << "Other?: ";
    instrumentation.push_back(getValue());

    for (auto &value : instrumentation) {
        std::cout << value << std::endl;
    }
    // Do some magic to get gig list
    // Print gig list and save to file
}