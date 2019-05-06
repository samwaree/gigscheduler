#ifndef STUDENT_H 
#define STUDENT_H 
#include <string > 
#include <vector > 
#include "instruments.hpp" 

class Student {
    private: 
    std::string name; // Student's name
    int vc; // The amount of vc a student has
    Instrument instrument; // Their instrument
    std::vector<int> availability; // A binary vector, 
                                   // where each index is a gig,
                                   // and 1 if they are available, 0 if not
    public: 
    // Constructor for student
    Student(std::string name, int vc, Instrument instrument, 
        std::vector<int> availability);
    std::string getName();
    int getVC();
    void setVC(int vc);
    Instrument getInstrument();
    bool isAvailable(int index);
};

// Overloaded < operator to use in sorting algorithm in main
bool operator<(Student &s1, Student &s2);

#endif