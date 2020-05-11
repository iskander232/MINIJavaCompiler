#include "AssertStatement.h"
#include <Location/Location.h>

AssertStatement::AssertStatement(Expression* expression): expression_(expression){}

Expression* AssertStatement::GetExpression() {
  return expression_;
}

void AssertStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}