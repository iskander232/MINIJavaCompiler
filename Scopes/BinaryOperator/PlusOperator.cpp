#include "PlusOperator.h"

int PlusOperator::eval(int a, int b) const {
  return a + b;
}

void PlusOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}