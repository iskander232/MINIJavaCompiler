#include "MethodInvokeStatement.h"

MethodInvokeStatement::MethodInvokeStatement(Expression *expr, std::string name, ExprList *exprList) :
    expression_(expr), name_(name), expr_list_(exprList) {}

Expression *MethodInvokeStatement::GetExpr() {
  return expression_;
}

std::string MethodInvokeStatement::GetName() {
  return name_;
}

ExprList * MethodInvokeStatement::GetExprList() {
  return expr_list_;
}

void MethodInvokeStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}