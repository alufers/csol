#include <iostream>
#include <termcolor.hpp>

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cout << termcolor::yellow << termcolor::underline << "SOL "
              << termcolor::reset << termcolor::blue
              << "v0.1 (c) alufers 2017 \n\n";
    std::cout << "Usage: \n";
    std::cout << "    sol <filename>\n";
  } else {
  }
}
