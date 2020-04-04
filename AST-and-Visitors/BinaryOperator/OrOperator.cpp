#include "OrOperator.h"

int OrOperator::eval(int a, int b) const {
  return a || b;
}

void OrOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}