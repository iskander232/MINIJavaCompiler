#include "MulOperator.h"
#include "Types/BasicObject.h"

BasicObject MulOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Integer,
                     a.Get(BasicType::Integer) * b.Get(BasicType::Integer));
}

void MulOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}