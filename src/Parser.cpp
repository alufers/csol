#include "Parser.h"

Parser::Parser(std::shared_ptr<ErrorReporter> errorReporter,
               std::shared_ptr<SourceFile> fileToParse) {
  this->errorReporter = errorReporter;
  this->boundFile = fileToParse;
}

std::unique_ptr<Stmt> Parser::declaration() {
  if (this->matchToken(TokenType::T_MUT) ||
      this->matchToken(TokenType::T_CONST))
    return this->mutConstDeclaration();
  if (this->matchToken(TokenType::T_CONST))
    return this->functionDeclaration();
  return this->statement();
}
std::unique_ptr<Stmt> Parser::mutConstDeclaration() {
  bool mut = this->previous().type == TokenType::T_MUT;
  Token name =
      this->consume(TokenType::T_IDENTIFIER,
                    "Expected identifier after " +
                        std::string(mut ? "mut" : "const") + " declaration");
  auto initializer = std::unique_ptr<Expr>(nullptr);
  if (this->matchToken(TokenType::T_EQUAL)) {
    initializer = expression();
  }
  if (mut) {
    auto decl = std::make_unique<StmtMutDeclaration>();
    decl->name = name;
    decl->initializer = std::move(initializer);
    return decl;
  } else {
    auto decl = std::make_unique<StmtConstDeclaration>();
    decl->name = name;
    decl->initializer = std::move(initializer);
    return decl;
  }
}
std::unique_ptr<Stmt> Parser::functionDeclaration() {
  Token name = this->consume(TokenType::T_IDENTIFIER,
                             "Expected identifier after function declaration");
  std::vector<Token> parameters;
  if (this->matchToken(TokenType::T_IDENTIFIER)) {
    parameters.push_back(this->previous());
  } else if (this->matchToken(TokenType::T_LEFT_PAREN)) {
    while (this->matchToken(TokenType::T_IDENTIFIER) && !this->isAtEnd()) {
      parameters.push_back(this->previous());
      if (this->matchToken(TokenType::T_COMMA)) { // comma between parameters
        // ok, next parameter
      } else if (this->matchToken(
                     TokenType::T_RIGHT_PAREN)) { // end of parameters
        break;
      } else {
        throw ParseError("Unexpected token \"" + this->advance().lexeme +
                         "\"at function parameters declaration");
      }
    }
  }

  std::unique_ptr<Stmt> body = this->controlFlowBody();
}
std::unique_ptr<Stmt> Parser::statement() {
  if (this->matchToken(TokenType::T_LEFT_BRACE))
    return this->blockStatement();
  if (this->matchToken(TokenType::T_IF))
    return this->ifStatement();
  if (this->matchToken(TokenType::T_WHILE))
    return this->whileStatement();
  if (this->matchToken(TokenType::T_BREAK))
    return this->breakStatement();
  if (this->matchToken(TokenType::T_FOR))
    return this->forStatement();
  if (this->matchToken(TokenType::T_RETURN))
    return this->returnStatement();
  return this->expressionStatement();
}
std::unique_ptr<Stmt> Parser::blockStatement() {
  auto block = std::make_unique<StmtBlock>();

  while (!this->checkToken(TokenType::T_RIGHT_BRACE) && !this->isAtEnd()) {
    block->statements.push_back(this->declaration());
  }
  this->consume(TokenType::T_RIGHT_BRACE,
                "Expected \"}\" after block statement");
  return block;
}
std::unique_ptr<Stmt> Parser::ifStatement() {
  auto condition = this->expression();
  auto body = this->controlFlowBody();
  std::unique_ptr<Stmt> elseBody = nullptr;
  if (this->matchToken(TokenType::T_ELSE)) {
    elseBody = this->controlFlowBody();
  }
  auto ifStmt = std::make_unique<StmtIf>();
  ifStmt->condition = std::move(condition);
  ifStmt->thenBranch = std::move(body);
  ifStmt->elseBranch = std::move(elseBody);
  return ifStmt;
}
std::unique_ptr<Stmt> Parser::whileStatement() {
  auto condition = this->expression();
  auto body = this->controlFlowBody();
  auto whileStmt = std::make_unique<StmtWhile>();
  whileStmt->condition = std::move(condition);
  whileStmt->body = std::move(body);
  return whileStmt;
}
std::unique_ptr<Stmt> Parser::forStatement() {
  throw ParseError("For loop not implemented yet");
}
std::unique_ptr<Stmt> Parser::controlFlowBody() {
  if (this->matchToken(TokenType::T_LEFT_BRACE))
    return this->blockStatement();
  if (this->matchToken(TokenType::T_RETURN))
    return this->returnStatement();
  if (this->matchToken(TokenType::T_BREAK))
    return this->breakStatement();
  throw ParseError("Expected block, return or break as control flow body");
}
std::unique_ptr<Stmt> Parser::breakStatement() {
  Token keyword = this->previous();
  this->consume(TokenType::T_SEMICOLON, "Expected \";\" after break statement");
}
std::unique_ptr<Stmt> Parser::returnStatement() {
  Token keyword = this->previous();
  std::unique_ptr<Expr> value = nullptr;
  if (!this->checkToken(TokenType::T_SEMICOLON)) {
    value = this->expression();
  }
  this->consume(TokenType::T_SEMICOLON,
                "Expected \";\" after return statement");
  auto retStmt = std::make_unique<StmtReturn>();
  retStmt->keyword = std::move(keyword);
  retStmt->value = std::move(value);
  return retStmt;
}
std::unique_ptr<Stmt> Parser::expressionStatement() {
  auto value = this->expression();
  this->consume(TokenType::T_SEMICOLON,
                "Expected \";\" after expression statement");
  auto exprStmt = std::make_unique<StmtExpression>();
  exprStmt->expression = std::move(value);
  return exprStmt;
}

// expression parsing

std::unique_ptr<Expr> Parser::expression() {
  return this->assignmentExpression();
}

std::unique_ptr<Expr> Parser::assignmentExpression() {
  auto leftExpr = this->orExpression();
  if (this->matchToken(TokenType::T_EQUAL) ||
      this->matchToken(TokenType::T_PLUS_EQUAL) ||
      this->matchToken(TokenType::T_MINUS_EQUAL)) {
    if (leftExpr->canBeAssignmentTarget()) {
      auto assignExpr = std::make_unique<ExprAssign>();
      assignExpr->target = std::move(leftExpr);
      assignExpr->operation = this->previous();
      assignExpr->value = this->expression();
      return assignExpr;
    } else {
      throw ParseError("Invalid assignment target");
    }
  }
  return leftExpr;
}
std::unique_ptr<Expr> Parser::orExpression() {
  auto expr = this->andExpression();
  while (this->matchToken(TokenType::T_OR)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->andExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::andExpression() {
  auto expr = this->equalityExpression();
  while (this->matchToken(TokenType::T_AND)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->equalityExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::equalityExpression() {
  auto expr = this->comparsionExpression();
  while (this->matchToken(TokenType::T_EQUAL) ||
         this->matchToken(TokenType::T_BANG_EQUAL)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->comparsionExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::comparsionExpression() {
  auto expr = this->additionExpression();
  while (this->matchToken(TokenType::T_LESS) ||
         this->matchToken(TokenType::T_GREATER) ||
         this->matchToken(TokenType::T_LESS_EQUAL) ||
         this->matchToken(TokenType::T_BANG_EQUAL)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->additionExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::additionExpression() {
  auto expr = this->multiplicationExpression();
  while (this->matchToken(TokenType::T_MINUS) ||
         this->matchToken(TokenType::T_PLUS)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->multiplicationExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::multiplicationExpression() {
  auto expr = this->exponentiationExpression();
  while (this->matchToken(TokenType::T_STAR) ||
         this->matchToken(TokenType::T_SLASH)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->exponentiationExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::exponentiationExpression() {
  auto expr = this->unaryExpression();
  while (this->matchToken(TokenType::T_STAR_STAR)) {
    auto nextExpr = std::make_unique<ExprBinary>();
    nextExpr->left = std::move(expr);
    nextExpr->operation = this->previous();
    nextExpr->right = this->unaryExpression();
    expr = std::move(nextExpr);
  }
  return expr;
}
std::unique_ptr<Expr> Parser::unaryExpression() {
  if (this->matchToken(TokenType::T_BANG) ||
      this->matchToken(TokenType::T_MINUS)) {
    auto un = std::make_unique<ExprUnary>();
    un->operation = this->previous();
    un->right = this->unaryExpression();
    return un;
  }
  return this->callExpression();
}
std::unique_ptr<Expr> Parser::callExpression() {
  auto expr = this->postfixExpression();
  while (this->matchToken(TokenType::T_LEFT_PAREN)) {
    expr = finishCallExpression(std::move(expr));
  }
  return expr;
}
std::unique_ptr<Expr>
Parser::finishCallExpression(std::unique_ptr<Expr> calee) {
  auto callExpr = std::make_unique<ExprCall>();
  callExpr->calee = std::move(calee);
  if (!this->checkToken(TokenType::T_RIGHT_PAREN)) {
    do {
      callExpr->arguments.push_back(expression());
    } while (matchToken(TokenType::T_COMMA));
  }
  callExpr->paren = this->consume(TokenType::T_RIGHT_PAREN,
                                  "Expected \")\" after call expression");
}
std::unique_ptr<Expr> Parser::postfixExpression() {
  auto expr = this->primaryExpression();
  if (this->matchToken(TokenType::T_PLUS_PLUS) ||
      this->matchToken(TokenType::T_PLUS_PLUS)) {
    if (!expr->canBeAssignmentTarget()) {
      throw ParseError(
          "Invalid left-hand side expression in postfix operation.");
    }
    auto pexpr = std::make_unique<ExprPostfix>();
    pexpr->left = std::move(expr);
    pexpr->operation = this->previous();
    return pexpr;
  }
  return expr;
}
std::unique_ptr<Expr> Parser::primaryExpression() {
  if (this->matchToken(TokenType::T_TRUE) ||
      this->matchToken(TokenType::T_FALSE) ||
      this->matchToken(TokenType::T_NIL) ||
      this->matchToken(TokenType::T_NUMBER) ||
      this->matchToken(TokenType::T_STRING)) {
    auto litExpr = std::make_unique<ExprLiteral>();
    litExpr->value = this->previous();
    return litExpr;
  } else if (this->matchToken(TokenType::T_IDENTIFIER)) {
    auto varExpr = std::make_unique<ExprVariable>();
    varExpr->name = this->previous();
    return varExpr;
  } else if (this->matchToken(TokenType::T_LEFT_PAREN)) {
    auto groupExpr = std::make_unique<ExprGrouping>();
    groupExpr->expression = this->expression();
    this->consume(TokenType::T_RIGHT_PAREN, "Expected \")\" after expression");
    return groupExpr;
  }
  throw ParseError("Primary expression can't be matched");
}

// utility methods
void Parser::doParse() {

  this->parsedFile = this->boundFile.lock();
  if (!this->parsedFile) {
    throw std::runtime_error("File to parse deleted (couldn't lock weak_ptr)");
  }

  while (!this->isAtEnd()) {
    // this->root.statements.push_back(this->declaration());
  }

  this->parsedFile = nullptr;
}

Token Parser::advance() {
  if (!this->isAtEnd())
    this->currentToken++;
  return this->previous();
}

Token Parser::consume(TokenType tt, std::string message) {
  if (this->checkToken(tt))
    return this->advance();
  throw ParseError(message);
}

bool Parser::matchToken(TokenType tt) {
  if (this->checkToken(tt)) {
    this->advance();
    return true;
  }
  return false;
}

bool Parser::checkToken(TokenType tt) {
  if (this->isAtEnd())
    return false;
  return this->peek().type == tt;
}

Token Parser::peek() {
  return this->parsedFile->scanner->tokens[this->currentToken];
}

Token Parser::previous() {
  return this->parsedFile->scanner->tokens[this->currentToken - 1];
}

CodeLocation Parser::getLocation() { return this->peek().location; }

bool Parser::isAtEnd() { return this->peek().type == TokenType::T_EOF; }
