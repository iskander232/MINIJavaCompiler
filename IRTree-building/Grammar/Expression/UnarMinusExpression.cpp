#include "UnarMinusExpression.h"
#include <Location/Location.h>

UnarMinusExpression::UnarMinusExpression(Expression *expression) : expression_(expression) {}

Expression *UnarMinusExpression::GetExpression() {
  return expression_;
}

void UnarMinusExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}