#include "MulOperator.h"

int MulOperator::eval(int a, int b) const {
  return a * b;
}

void MulOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}