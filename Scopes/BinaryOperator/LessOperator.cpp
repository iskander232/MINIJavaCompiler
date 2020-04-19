#include "LessOperator.h"

int LessOperator::eval(int a, int b) const {
  return a < b;
}

void LessOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
