#include "MoreOperator.h"

int MoreOperator::eval(int a, int b) const {
  return a > b;
}

void MoreOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}