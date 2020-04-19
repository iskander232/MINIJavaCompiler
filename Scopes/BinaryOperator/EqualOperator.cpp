#include "EqualOperator.h"

int EqualOperator::eval(int a, int b) const {
  return a == b;
}

void EqualOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}