#include "LessOperator.h"
#include "Types/BasicObject.h"

BasicObject LessOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Bool,
                     a.Get(BasicType::Integer) < b.Get(BasicType::Integer));
}

void LessOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
