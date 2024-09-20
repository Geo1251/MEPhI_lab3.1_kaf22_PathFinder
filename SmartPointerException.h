#ifndef SMARTPOINTEREXCEPTION_H
#define SMARTPOINTEREXCEPTION_H

#include <exception>
#include <string>

class SmartPointerException : public std::exception {
private:
    std::string message;

public:
    explicit SmartPointerException(const std::string& msg) : message(msg) {}

    virtual const char* what() const throw() {
        return message.c_str();
    }
};

#endif // SMARTPOINTEREXCEPTION_H