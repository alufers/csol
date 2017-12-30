#include <iostream>
#include <termcolor.hpp>
#include <memory>
#include "SourceFile.h"
#include "ErrorReporter.h"
#include "Scanner.h"
#include "TokenType.h"

int main(int argc, char **argv) {
  if (argc <= 1) {
    std::cout << termcolor::yellow << termcolor::underline << "SOL "
              << termcolor::reset << termcolor::blue
              << "v0.1 (c) alufers 2017 \n\n";
    std::cout << "Usage: \n";
    std::cout << "    sol <filename>\n";
  } else {
  
    auto er = std::make_shared<ErrorReporter>();
    auto sf = std::make_shared<SourceFile>(argv[1]);
    Scanner s = Scanner(er, sf);
    s.scan();
    for(auto &t : s.tokens) {
      //std::cout << TokenTypeUtils::getTokenTypeName(t.type) << " " << t.lexeme << "\n";
    }
  }
}
