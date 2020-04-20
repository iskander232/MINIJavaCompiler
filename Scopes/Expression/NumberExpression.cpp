#include "NumberExpression.h"

NumberExpression::NumberExpression(int num) : number_(new BasicObject(BasicType::Integer, num)) {};

BasicObject* NumberExpression::GetNumber() {
  return number_;
}

void NumberExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

