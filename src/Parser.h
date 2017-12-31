#ifndef PARSER_H
#define PARSER_H
#include "CodeLocation.h"
#include "ErrorReporter.h"
#include "Expr.h"
#include "Scanner.h"
#include "SourceFile.h"
#include "Stmt.h"
#include "Token.h"
#include "TokenType.h"
#include <memory>
#include <stdexcept>
#include <vector>

class ParseError : std::runtime_error {
  using std::runtime_error::runtime_error;
};

class Parser {
public:
  std::shared_ptr<ErrorReporter> errorReporter;
  std::shared_ptr<SourceFile> parsedFile;
  std::weak_ptr<SourceFile> boundFile;
  StmtBlock root;
  int currentToken;

  Parser(std::shared_ptr<ErrorReporter> errorReporter,
         std::shared_ptr<SourceFile> fileToParse);
  void doParse();

private:
  // parsing methods;
  std::unique_ptr<Stmt> declaration();
  std::unique_ptr<Stmt> mutConstDeclaration();
  std::unique_ptr<Stmt> functionDeclaration();
  std::unique_ptr<Stmt> statement();
  std::unique_ptr<Stmt> ifStatement();
  std::unique_ptr<Stmt> whileStatement();
  std::unique_ptr<Stmt> forStatement();
  std::unique_ptr<Stmt> controlFlowBody();
  std::unique_ptr<Stmt> breakStatement();
  std::unique_ptr<Stmt> returnStatement();
  std::unique_ptr<Stmt> blockStatement();
  std::unique_ptr<Stmt> expressionStatement();

  // expression parsing
  std::unique_ptr<Expr> expression();
  std::unique_ptr<Expr> assignmentExpression();
  std::unique_ptr<Expr> orExpression();
  std::unique_ptr<Expr> andExpression();
  std::unique_ptr<Expr> equalityExpression();
  std::unique_ptr<Expr> comparsionExpression();
  std::unique_ptr<Expr> additionExpression();
  std::unique_ptr<Expr> multiplicationExpression();
  std::unique_ptr<Expr> exponentiationExpression();
  std::unique_ptr<Expr> unaryExpression();
  std::unique_ptr<Expr> callExpression();
  std::unique_ptr<Expr> finishCallExpression(std::unique_ptr<Expr> calee);
  std::unique_ptr<Expr> postfixExpression();
  std::unique_ptr<Expr> primaryExpression();
  // utility methods:
  bool isAtEnd();
  Token consume(TokenType tt, std::string errorMessage);
  bool matchToken(TokenType tt);
  bool checkToken(TokenType tt);
  Token advance();
  Token peek();
  Token previous();
  CodeLocation getLocation();
};
#endif
