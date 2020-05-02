#ifndef IDICTIONARY
#define IDICTIONARY

#include <string>

class IDictionary {
public:
    virtual void add(std::string const &word) = 0;
    virtual bool check(std::string const &word) = 0;
    virtual std::string getNameOfStructure() = 0;
    virtual ~IDictionary() {};
};

#endif