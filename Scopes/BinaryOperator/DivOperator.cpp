#include "DivOperator.h"
#include "Types/BasicObject.h"

BasicObject DivOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Integer,
                     a.Get(BasicType::Integer) / b.Get(BasicType::Integer));
}

void DivOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}