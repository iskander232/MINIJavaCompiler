#include "OrOperator.h"
#include "Types/BasicObject.h"

BasicObject OrOperator::eval(BasicObject a, BasicObject b) const {
  return BasicObject(BasicType::Bool,
                     a.Get(BasicType::Bool) || b.Get(BasicType::Bool));
}

void OrOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}