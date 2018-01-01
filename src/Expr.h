#ifndef EXPR_H
#define EXPR_H
#include "Token.h"
#include <memory>
#include <vector>

class ExprVisitor;
class Expr {
public:
  virtual void accept(ExprVisitor &visitor) = 0;
  virtual bool canBeAssignmentTarget() = 0;
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
  virtual void visitAssignExpr(ExprAssign &expr) = 0;
  virtual void visitBinaryExpr(ExprBinary &expr) = 0;
  virtual void visitCallExpr(ExprCall &expr) = 0;
  virtual void visitGetExpr(ExprGet &expr) = 0;
  virtual void visitGroupingExpr(ExprGrouping &expr) = 0;
  virtual void visitLiteralExpr(ExprLiteral &expr) = 0;
  virtual void visitSetExpr(ExprSet &expr) = 0;
  virtual void visitSuperExpr(ExprSuper &expr) = 0;
  virtual void visitThisExpr(ExprThis &expr) = 0;
  virtual void visitUnaryExpr(ExprUnary &expr) = 0;
  virtual void visitVariableExpr(ExprVariable &expr) = 0;
  virtual void visitPostfixExpr(ExprPostfix &expr) = 0;
};

class ExprAssign : public Expr {
public:
  std::unique_ptr<Expr> target;
  Token operation;
  std::unique_ptr<Expr> value;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitAssignExpr(*this); }
};
class ExprBinary : public Expr {
public:
  std::unique_ptr<Expr> left;
  Token operation;
  std::unique_ptr<Expr> right;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitBinaryExpr(*this); }
};
class ExprCall : public Expr {
public:
  std::unique_ptr<Expr> calee;
  Token paren;
  std::vector<std::unique_ptr<Expr>> arguments;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitCallExpr(*this); }
};
class ExprGet : public Expr {
public:
  std::unique_ptr<Expr> obj;
  Token name;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitGetExpr(*this); }
};
class ExprGrouping : public Expr {
public:
  std::unique_ptr<Expr> expression;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitGroupingExpr(*this); }
};
class ExprLiteral : public Expr {
public:
  Token value;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitLiteralExpr(*this); }
};
class ExprSet : public Expr {
public:
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitSetExpr(*this); }
};
class ExprSuper : public Expr {
public:
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitSuperExpr(*this); }
};
class ExprThis : public Expr {
public:
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitThisExpr(*this); }
};
class ExprUnary : public Expr {
public:
  Token operation;
  std::unique_ptr<Expr> right;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitUnaryExpr(*this); }
};
class ExprVariable : public Expr {
public:
  Token name;
  bool canBeAssignmentTarget() { return true; }
  void accept(ExprVisitor &visitor) { visitor.visitVariableExpr(*this); }
};
class ExprPostfix : public Expr {

public:
  Token operation;
  std::unique_ptr<Expr> left;
  bool canBeAssignmentTarget() { return false; }
  void accept(ExprVisitor &visitor) { visitor.visitPostfixExpr(*this); }
};
#endif
