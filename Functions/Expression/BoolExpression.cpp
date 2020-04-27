#include "BoolExpression.h"

#include "Types/Bool.h"
BoolExpression::BoolExpression(bool value) : value_(new BoolObject(value)) {};

std::shared_ptr<Object> BoolExpression::GetValue() {
  return std::dynamic_pointer_cast<Object>(value_);
}

void BoolExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}