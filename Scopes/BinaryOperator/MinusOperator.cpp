#include "MinusOperator.h"

int MinusOperator::eval(int a, int b) const {
  return a - b;
}

void MinusOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}