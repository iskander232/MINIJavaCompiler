#include "ProcOperator.h"

int ProcOperator::eval(int a, int b) const {
  return a % b;
}

void ProcOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}