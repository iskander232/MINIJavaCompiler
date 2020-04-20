#include "BoolExpression.h"

BoolExpression::BoolExpression(bool value) : value_(new BasicObject(BasicType::Bool, value)) {};

BasicObject *BoolExpression::GetValue() {
  return value_;
}

void BoolExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}