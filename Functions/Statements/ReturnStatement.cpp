#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(Expression *expression) : expression_(expression) {}

Expression *ReturnStatement::GetExpr() {
  return expression_;
}

void ReturnStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}