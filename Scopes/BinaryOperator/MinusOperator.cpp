#include "MinusOperator.h"
#include "Types/BasicObject.h"

BasicObject MinusOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Integer,
                     a.Get(BasicType::Integer) - b.Get(BasicType::Integer));
}

void MinusOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}