#include "AstPrinter.h"

void AstPrinter::printStatement(Stmt &stmt) { stmt.accept(*this); }
void AstPrinter::printExpr(Expr &expr) { expr.accept(*this); }
void AstPrinter::printPointerUniqueName(void *ptr) {
  std::cout << "p_" << (long)ptr;
}

void AstPrinter::visitBlockStmt(StmtBlock &stmt) {
  this->printPointerUniqueName(&stmt);
  std::cout << " [label=\"BlockStmt\" shape=\"box\"];\n";
  for (auto &s : stmt.statements) {
    this->printPointerUniqueName(&stmt);
    std::cout << "->";
    this->printPointerUniqueName(s.get());
    std::cout << ";\n";
    this->printStatement(*s);
  }
}
void AstPrinter::visitClassStmt(StmtClass &stmt) {}
void AstPrinter::visitExpressionStmt(StmtExpression &stmt) {
  this->printPointerUniqueName(&stmt);
  std::cout << " [label=\"ExpressionStmt\" shape=\"box\"];\n";
  this->printPointerUniqueName(&stmt);
  std::cout << "->";
  this->printPointerUniqueName(stmt.expression.get());
  std::cout << ";\n";
  this->printExpr(*stmt.expression);
}
void AstPrinter::visitFunctionStmt(StmtFunction &stmt) {}
void AstPrinter::visitIfStmt(StmtIf &stmt) {}
void AstPrinter::visitReturnStmt(StmtReturn &stmt) {}
void AstPrinter::visitBreakStmt(StmtBreak &stmt) {}
void AstPrinter::visitMutDeclarationStmt(StmtMutDeclaration &stmt) {}
void AstPrinter::visitConstDeclarationStmt(StmtConstDeclaration &stmt) {}
void AstPrinter::visitWhileStmt(StmtWhile &stmt) {}
void AstPrinter::visitAssignExpr(ExprAssign &expr) {}
void AstPrinter::visitBinaryExpr(ExprBinary &expr) {
  this->printPointerUniqueName(&expr);
  std::cout << " [label= < BinaryExpr <B>" << expr.operation.lexeme
            << "</B> >];\n";
  this->printPointerUniqueName(&expr);
  std::cout << "->";
  this->printPointerUniqueName(expr.left.get());
  std::cout << " [label=left];\n";
  this->printExpr(*expr.left);

  this->printPointerUniqueName(&expr);
  std::cout << "->";
  this->printPointerUniqueName(expr.right.get());
  std::cout << " [label=right];\n";
  this->printExpr(*expr.right);
}
void AstPrinter::visitCallExpr(ExprCall &expr) {}
void AstPrinter::visitGetExpr(ExprGet &expr) {}
void AstPrinter::visitGroupingExpr(ExprGrouping &expr) {
  this->printPointerUniqueName(&expr);
  std::cout << " [label= < GroupingExpr >];\n";
  this->printPointerUniqueName(&expr);
  std::cout << "->";
  this->printPointerUniqueName(expr.expression.get());
  std::cout << " [label=\"innerExpr\"];\n";
  this->printExpr(*expr.expression);
}
void AstPrinter::visitLiteralExpr(ExprLiteral &expr) {
  this->printPointerUniqueName(&expr);
  std::cout << " [label= < LiteralExpr <B>" << expr.value.lexeme
            << "</B> > shape=\"egg\"];\n";
}
void AstPrinter::visitSetExpr(ExprSet &expr) {}
void AstPrinter::visitSuperExpr(ExprSuper &expr) {}
void AstPrinter::visitThisExpr(ExprThis &expr) {}
void AstPrinter::visitUnaryExpr(ExprUnary &expr) {
  this->printPointerUniqueName(&expr);
  std::cout << " [label= < UnaryExpr <B>" << expr.operation.lexeme
            << "</B> >];\n";

  this->printPointerUniqueName(&expr);
  std::cout << "->";
  this->printPointerUniqueName(expr.right.get());
  std::cout << " [label=right];\n";
  this->printExpr(*expr.right);
}
void AstPrinter::visitVariableExpr(ExprVariable &expr) {
    this->printPointerUniqueName(&expr);
  std::cout << " [label= < VariableExpr <B>" << expr.name.lexeme
            << "</B> > shape=\"egg\"];\n";
}
void AstPrinter::visitPostfixExpr(ExprPostfix &expr) {
    this->printPointerUniqueName(&expr);
  std::cout << " [label= < UnaryExpr <B>" << expr.operation.lexeme
            << "</B> >];\n";

  this->printPointerUniqueName(&expr);
  std::cout << "->";
  this->printPointerUniqueName(expr.left.get());
  std::cout << " [label=left];\n";
  this->printExpr(*expr.left);
}
