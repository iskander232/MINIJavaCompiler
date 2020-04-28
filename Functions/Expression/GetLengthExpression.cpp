#include "GetLengthExpression.h"
#include <Location/Location.h>

GetLengthExpression::GetLengthExpression(Expression *array): array_(array) {}

Expression * GetLengthExpression::GetArray() {
  return array_;
}

void GetLengthExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}