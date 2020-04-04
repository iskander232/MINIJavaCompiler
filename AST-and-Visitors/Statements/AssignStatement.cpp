#include "AssignStatement.h"

AssignStatement::AssignStatement(Lvalue *lvalue, Expression *expression): lvalue_(lvalue), expression_(expression){
}

Lvalue* AssignStatement::GetLvalue() {
  return lvalue_;
}

Expression* AssignStatement::GetExpression() {
  return expression_;
}

void AssignStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}