#include "AssignStatement.h"
#include <Location/Location.h>

AssignStatement::AssignStatement(Lvalue *lvalue, Expression *expression): lvalue_(lvalue), expression_(expression){
}

Lvalue* AssignStatement::GetLvalue() {
  return lvalue_;
}

Expression* AssignStatement::GetExpression() {
  return expression_;
}

void AssignStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}