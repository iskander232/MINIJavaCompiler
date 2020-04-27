#include "InvokeExpression.h"

InvokeExpression::InvokeExpression(Expression *expression, std::string name, ExprList *expr_list) :
    expression_(expression), name_(name), expr_list_(expr_list) {}

Expression *InvokeExpression::GetExpression() {
  return expression_;
}

std::string InvokeExpression::GetName() {
  return name_;
}

ExprList *InvokeExpression::GetExprList() {
  return expr_list_;
}

void InvokeExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}