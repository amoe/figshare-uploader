#ifndef PERSON_HH
#define PERSON_HH

#include <string>

using std::string;

struct Person {
    Person(bool hasName, string name): hasName(hasName), name(name) { }

    bool hasName;
    string name;
};

#endif /* PERSON_HH */
