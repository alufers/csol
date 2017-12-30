#ifndef PARSER_H
#define PARSER_H
#include "SourceFile.h"
#include "Token.h"
#include <vector>
#include "Stmt.h"
#include "Expr.h"
class Parser {
public:
  std::vector<Token> tokens;
  std::shared_ptr<SourceFile> parsedFile;
  std::weak_ptr<SourceFile> boundFile;
  Parser(std::shared_ptr<SourceFile> fileToParse);
  void parse();
};
#endif
