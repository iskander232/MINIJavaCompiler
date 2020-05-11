#include "ArrayGetExpression.h"
#include <Location/Location.h>

ArrayGetExpression::ArrayGetExpression(Expression *array, Expression *index): array_(array), index_(index) {}

Expression * ArrayGetExpression::GetArray() {
  return array_;
}

Expression * ArrayGetExpression::GetIndex() {
  return index_;
}

void ArrayGetExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}