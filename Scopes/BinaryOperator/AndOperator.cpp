#include "AndOperator.h"

BasicObject AndOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Bool,
                     a.Get(BasicType::Bool) && b.Get(BasicType::Bool));
}

void AndOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}