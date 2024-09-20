#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
public:
    std::string name;
    int age;

    Person(std::string name, int age) : name(name), age(age) {}
};

#endif //PERSON_H