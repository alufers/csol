#ifndef ERROR_REPORTER_H
#define ERROR_REPORTER_H
#include <string>
#include <termcolor.hpp>
#include "CodeLocation.h"
class ErrorReporter {
public:
  bool hadSystemError;
  bool hadScanningError;
  void reportSystemError(std::string message);
  void reportSystemWarning(std::string message);
  void reportScanningError(std::string message,  CodeLocation where);
  private:
    void drawCodeWindow(CodeLocation &where);
};
#endif
