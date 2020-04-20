#include "PlusOperator.h"
#include "Types/BasicObject.h"

#include <iostream>

BasicObject PlusOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Integer,
                     a.Get(BasicType::Integer) + b.Get(BasicType::Integer));
}

void PlusOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}