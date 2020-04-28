#include "MethodInvokeStatement.h"
#include <Location/Location.h>

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
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}