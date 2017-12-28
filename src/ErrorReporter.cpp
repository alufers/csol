#include "ErrorReporter.h"

void ErrorReporter::reportSystemError(std::string message) {
  std::cout << termcolor::on_red << "[ERROR]" << termcolor::red << message
            << termcolor::reset << "\n";
}

void ErrorReporter::reportSystemWarning(std::string message) {
  std::cout << termcolor::on_yellow << "[WARN]" << termcolor::yellow << message
            << termcolor::reset << "\n";
}
