#ifndef STMT_H
#define STMT_H
#include "Expr.h"
#include "Token.h"
#include <memory>
#include <string>
#include <vector>

class StmtVisitor;
class Stmt {
public:
  virtual void accept(StmtVisitor &visitor) = 0;
};

class StmtBlock;
class StmtClass;
class StmtExpression;
class StmtFunction;
class StmtIf;
class StmtReturn;
class StmtBreak;
class StmtMutDeclaration;
class StmtConstDeclaration;
class StmtWhile;
class StmtVisitor {
public:
  virtual void visitBlockStmt(StmtBlock &stmt) = 0;
  virtual void visitClassStmt(StmtClass &stmt) = 0;
  virtual void visitExpressionStmt(StmtExpression &stmt) = 0;
  virtual void visitFunctionStmt(StmtFunction &stmt) = 0;
  virtual void visitIfStmt(StmtIf &stmt) = 0;
  virtual void visitReturnStmt(StmtReturn &stmt) = 0;
  virtual void visitBreakStmt(StmtBreak &stmt) = 0;
  virtual void visitMutDeclarationStmt(StmtMutDeclaration &stmt) = 0;
  virtual void visitConstDeclarationStmt(StmtConstDeclaration &stmt) = 0;
  virtual void visitWhileStmt(StmtWhile &stmt) = 0;
};

class StmtBlock : public Stmt {
public:
  StmtBlock() {}
  std::vector<std::unique_ptr<Stmt>> statements;
  void accept(StmtVisitor &visitor) { visitor.visitBlockStmt(*this); }
};

class StmtClass : public Stmt {
public:
  std::string name;
  std::vector<StmtFunction> methods;
  void accept(StmtVisitor &visitor) { visitor.visitClassStmt(*this); }
};

class StmtExpression : public Stmt {
public:
  std::unique_ptr<Expr> expression;
  void accept(StmtVisitor &visitor) { visitor.visitExpressionStmt(*this); }
};

class StmtFunction : public Stmt {
public:
  Token name;
  std::vector<Token> parameters;
  std::unique_ptr<Stmt> body;
  void accept(StmtVisitor &visitor) { visitor.visitFunctionStmt(*this); }
};

class StmtIf : public Stmt {
public:
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> thenBranch;
  std::unique_ptr<Stmt> elseBranch;
  void accept(StmtVisitor &visitor) { visitor.visitIfStmt(*this); }
};

class StmtReturn : public Stmt {
public:
  Token keyword;
  std::unique_ptr<Expr> value;
  void accept(StmtVisitor &visitor) { visitor.visitReturnStmt(*this); }
};

class StmtBreak : public Stmt {
public:
  Token keyword;
  void accept(StmtVisitor &visitor) { visitor.visitBreakStmt(*this); }
};

class StmtMutDeclaration : public Stmt {
public:
  Token name;
  std::unique_ptr<Expr> initializer;
  void accept(StmtVisitor &visitor) { visitor.visitMutDeclarationStmt(*this); }
};

class StmtConstDeclaration : public Stmt {
public:
  Token name;
  std::unique_ptr<Expr> initializer;
  void accept(StmtVisitor &visitor) { visitor.visitConstDeclarationStmt(*this); }
};

class StmtWhile : public Stmt {
public:
  std::unique_ptr<Expr> condition;
  std::unique_ptr<Stmt> body;
  void accept(StmtVisitor &visitor) { visitor.visitWhileStmt(*this); }
};

#endif
