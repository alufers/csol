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
  virtual void visitAssignExpr(const ExprAssign &expr);
  virtual void visitBinaryExpr(const ExprBinary &expr);
  virtual void visitCallExpr(const ExprCall &expr);
  virtual void visitGetExpr(const ExprGet &expr);
  virtual void visitGroupingExpr(const ExprGrouping &expr);
  virtual void visitLiteralExpr(const ExprLiteral &expr);
  virtual void visitSetExpr(const ExprSet &expr);
  virtual void visitSuperExpr(const ExprSuper &expr);
  virtual void visitThisExpr(const ExprThis &expr);
  virtual void visitUnaryExpr(const ExprUnary &expr);
  virtual void visitVariableExpr(const ExprVariable &expr);
  virtual void visitPostfixExpr(const ExprPostfix &expr);
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
