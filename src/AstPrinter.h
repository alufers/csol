#ifndef AST_PRINTER
#define AST_PRINTER
#include "Expr.h"
#include "Stmt.h"
#include <iostream>
#include <memory>

class AstPrinter : public StmtVisitor,  public ExprVisitor {
public:
  void printStatement(Stmt &stmt);
  void printExpr(Expr &expr);

  void printPointerUniqueName(void *ptr);

  void visitBlockStmt(StmtBlock &stmt);
  void visitClassStmt(StmtClass &stmt);
  void visitExpressionStmt(StmtExpression &stmt);
  void visitFunctionStmt(StmtFunction &stmt);
  void visitIfStmt(StmtIf &stmt);
  void visitReturnStmt(StmtReturn &stmt);
  void visitBreakStmt(StmtBreak &stmt);
  void visitMutDeclarationStmt(StmtMutDeclaration &stmt);
  void visitConstDeclarationStmt(StmtConstDeclaration &stmt);
  void visitWhileStmt(StmtWhile &stmt);

  void visitAssignExpr(ExprAssign &expr);
  void visitBinaryExpr(ExprBinary &expr);
  void visitCallExpr(ExprCall &expr);
  void visitGetExpr(ExprGet &expr);
  void visitGroupingExpr(ExprGrouping &expr);
  void visitLiteralExpr(ExprLiteral &expr);
  void visitSetExpr(ExprSet &expr);
  void visitSuperExpr(ExprSuper &expr);
  void visitThisExpr(ExprThis &expr);
  void visitUnaryExpr(ExprUnary &expr);
  void visitVariableExpr(ExprVariable &expr);
  void visitPostfixExpr(ExprPostfix &expr);
};

#endif
