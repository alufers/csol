#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H
#include <string>
#include <termcolor.hpp>
#include <iomanip>
#include "CodeLocation.h"
#include <algorithm> 

class ErrorReporter {
public:
  bool hadSystemError;
  bool hadScanningError;
  void reportSystemError(std::string message);
  void reportSystemWarning(std::string message);
  void reportScanningError(std::string message,  CodeLocation where);
  private:
    void drawCodeWindow(CodeLocation &where, std::string message);
};
#endif
