#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H
#include <string>
#include <termcolor.hpp>

class ErrorReporter {
    void reportSystemError(std::string message);
    void reportSystemWarning(std::string message);
    
};
#endif
