#ifndef EXPR_H
#define EXPR_H
#include "Token.h"
#include <vector>

class ExprVisitor;
class Expr {
public:
  virtual void accept(ExprVisitor &visitor);
};

class ExprAssign;
class ExprBinary;
class ExprCall;
class ExprGet;
class ExprGrouping;
class ExprLiteral;
class ExprSet;
class ExprSuper;
class ExprThis;
class ExprUnary;
class ExprVariable;
class ExprPostfix;
class ExprVisitor {
public:
  void visitAssignExpr(const ExprAssign &expr);
  void visitBinaryExpr(const ExprBinary &expr);
  void visitCallExpr(const ExprCall &expr);
  void visitGetExpr(const ExprGet &expr);
  void visitGroupingExpr(const ExprGrouping &expr);
  void visitLiteralExpr(const ExprLiteral &expr);
  void visitSetExpr(const ExprSet &expr);
  void visitSuperExpr(const ExprSuper &expr);
  void visitThisExpr(const ExprThis &expr);
  void visitUnaryExpr(const ExprUnary &expr);
  void visitVariableExpr(const ExprVariable &expr);
  void visitPostfixExpr(const ExprPostfix &expr);
};

class ExprAssign : public Expr {
public:
  Token name;
  Expr value;

  void accept(ExprVisitor &visitor) { visitor.visitAssignExpr(*this); }
};
class ExprBinary : public Expr {
public:
  Expr left;
  Token operation;
  Expr right;
  void accept(ExprVisitor &visitor) { visitor.visitBinaryExpr(*this); }
};
class ExprCall : public Expr {
public:
  Expr calee;
  Token paren;
  std::vector<Expr> arguments;
  void accept(ExprVisitor &visitor) { visitor.visitCallExpr(*this); }
};
class ExprGet : public Expr {
  Expr obj;
  Token name;

public:
  void accept(ExprVisitor &visitor) { visitor.visitGetExpr(*this); }
};
class ExprGrouping : public Expr {
    Expr expression;
public:
  void accept(ExprVisitor &visitor) { visitor.visitGroupingExpr(*this); }
};
class ExprLiteral : public Expr {
    Token value;
public:
  void accept(ExprVisitor &visitor) { visitor.visitLiteralExpr(*this); }
};
class ExprSet : public Expr {
public:
  void accept(ExprVisitor &visitor) { visitor.visitSetExpr(*this); }
};
class ExprSuper : public Expr {
public:
  void accept(ExprVisitor &visitor) { visitor.visitSuperExpr(*this); }
};
class ExprThis : public Expr {
public:
  void accept(ExprVisitor &visitor) { visitor.visitThisExpr(*this); }
};
class ExprUnary : public Expr {
    Token operation;
    Expr right;
public:
  void accept(ExprVisitor &visitor) { visitor.visitUnaryExpr(*this); }
};
class ExprVariable : public Expr {
    Token name;
public:
  void accept(ExprVisitor &visitor) { visitor.visitVariableExpr(*this); }
};
class ExprPostfix : public Expr {
    Token operation;
    Expr left;
public:
  void accept(ExprVisitor &visitor) { visitor.visitPostfixExpr(*this); }
};
#endif
