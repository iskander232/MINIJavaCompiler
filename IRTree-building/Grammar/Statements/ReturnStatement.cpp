#include "ReturnStatement.h"
#include <Location/Location.h>

ReturnStatement::ReturnStatement(Expression *expression) : expression_(expression) {}

Expression *ReturnStatement::GetExpr() {
  return expression_;
}

void ReturnStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}