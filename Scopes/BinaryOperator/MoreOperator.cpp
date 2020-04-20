#include "MoreOperator.h"
#include "Types/BasicObject.h"

BasicObject MoreOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Bool,
                     a.Get(BasicType::Integer) > b.Get(BasicType::Integer));
}

void MoreOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}