#include "OutStatement.h"
#include <Location/Location.h>

OutStatement::OutStatement(Expression *expression): expression_(expression) {}

Expression* OutStatement::GetExpression() {
  return expression_;
}

void OutStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}