#include "DivOperator.h"

int DivOperator::eval(int a, int b) const {
  return a / b;
}

void DivOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}