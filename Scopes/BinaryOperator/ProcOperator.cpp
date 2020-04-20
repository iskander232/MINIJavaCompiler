#include "ProcOperator.h"
#include "Types/BasicObject.h"

BasicObject ProcOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Integer,
                     a.Get(BasicType::Integer) % b.Get(BasicType::Integer));
}

void ProcOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}