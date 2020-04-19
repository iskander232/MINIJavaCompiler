#include "AndOperator.h"

int AndOperator::eval(int a, int b) const {
  return a && b;
}

void AndOperator::Accept(Visitor* visitor) {
  visitor->Visit(this);
}