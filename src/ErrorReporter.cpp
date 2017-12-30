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
  this->drawCodeWindow(where, message);
}

void ErrorReporter::drawCodeWindow(CodeLocation &where, std::string message) {

  auto lines = where.linesBefore(4);
  int lineNumber = where.line - 3;
  // compute the width of the window
  int maxLineLength = 0;
  for (std::string &line : lines) {
    if (line.size() > maxLineLength) {
      maxLineLength = line.size();
    }
  }

  // print the header
  std::cout << termcolor::on_white << termcolor::grey << "     "
            << where.file->path << termcolor::red << " (!) ";

  for (int i = 0;
       i < std::min((int)(maxLineLength - (where.file->path.size() + 5)),
                    10); // 5 is the length of (!)
       i++) {
    std::cout << " ";
  }

  std::cout << termcolor::reset << "\n";

  const int lineNumberPadding = 4;

  if (lineNumber != 0) { // print ... when not writing form the first line
    std::cout << termcolor::on_white << termcolor::dark << termcolor::grey
              << std::setw(lineNumberPadding) << "..." << " " << termcolor::reset
              << "\n";
  }

  // draw line number indicators
  for (std::string &line : lines) {
    if (lineNumber == where.line) { // highlight line in red
      std::cout << termcolor::on_red << termcolor::white;
    } else {
      std::cout << termcolor::on_white << termcolor::grey;
    }
    // draw the line number indicator
    std::cout << std::setw(lineNumberPadding) << lineNumber + 1 << " "
              << termcolor::reset << line;

    lineNumber++;
  }
  /*
  std::cout << termcolor::red << "    ╤"
            << "\n";
  std::cout << termcolor::red << "    │    ┌────────────────────────┐"
            << "\n";
  std::cout << termcolor::red << "    └────┤ " << termcolor::bold
            << "Unexpected character " << termcolor::blue << "d"
            << termcolor::reset << termcolor::red << " │\n";
  std::cout << termcolor::red << "         └────────────────────────┘\n";*/
}
