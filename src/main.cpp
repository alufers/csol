#include "ErrorReporter.h"
#include "Expr.h"
#include "Parser.h"
#include "Scanner.h"
#include "SourceFile.h"
#include "Stmt.h"
#include "TokenType.h"
#include <iostream>
#include <memory>
#include <termcolor.hpp>

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
    sf->scanner = std::make_shared<Scanner>(er, sf);
    sf->scanner->scan();
    /*for (auto &t : sf->scanner->tokens) {
      std::cout << TokenTypeUtils::getTokenTypeName(t.type) << " " << t.lexeme
                << "\n";
    }*/
    auto parser = std::make_unique<Parser>(er, sf);
    parser->doParse();
    std::cout << parser->root.statements.size() << std::endl;
  }
}
