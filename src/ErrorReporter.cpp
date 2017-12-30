#include "ErrorReporter.h"

void ErrorReporter::reportSystemError(std::string message) {
  this->hadSystemError = true;
  std::cout << termcolor::red << "error: " << termcolor::bold << message
            << termcolor::reset << "\n";
}

void ErrorReporter::reportSystemWarning(std::string message) {
  std::cout << termcolor::yellow << "warning: " << termcolor::bold << message
            << termcolor::reset << "\n";
}

void ErrorReporter::reportScanningError(std::string message,
                                        CodeLocation where) {
  this->hadScanningError = true;
  std::cout << termcolor::dark << "scanning " << termcolor::reset
            << termcolor::red << "error: " << termcolor::bold << message
            << termcolor::reset << termcolor::dark << " at line "
            << where.line + 1 << ":" << where.column + 1 << " in "
            << where.file->path << "\n"
            << termcolor::reset;
  this->drawCodeWindow(where);
}

void ErrorReporter::drawCodeWindow(CodeLocation &where) {

  std::cout << termcolor::on_white << termcolor::grey << "     "
            << where.file->path << termcolor::red << " (!)              " << termcolor::reset << "\n";
  auto lines = where.linesBefore(4);
  int lineNumber = where.line - 3;
  for (std::string &line : lines) {
    std::cout << termcolor::on_white << termcolor::grey << "  "
              << lineNumber + 1 << " " << termcolor::reset << line;
    lineNumber++;
  }
  std::cout << termcolor::red << "    ╤" << "\n";
  std::cout << termcolor::red << "    │    ┌────────────────────────┐" << "\n";
  std::cout << termcolor::red << "    └────┤ " << termcolor::bold << "Unexpected character " << termcolor::blue << "d" << termcolor::reset << termcolor::red <<  " │\n";
  std::cout << termcolor::red << "         └────────────────────────┘\n";
}
