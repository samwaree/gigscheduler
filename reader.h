#ifndef READER_H
#define READER_H

#include <string>
#include "Student.h"
#include <vector>

class Reader
{
  public:
    // Reads in all the gigs from fileName, and returns a list of them
    static std::vector<std::string> getGigList(std::string fileName);
    // Reads in all the students from fileName, and returns a list of them
    static std::vector<Student> getStudentList(std::string fileName, std::vector<std::string> gigList);
};

#endif