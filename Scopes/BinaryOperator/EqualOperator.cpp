#include "EqualOperator.h"
#include "Types/BasicObject.h"

#include "stdexcept"

BasicObject EqualOperator::eval(BasicObject a, BasicObject b) const {
  if (a.GetType() == b.GetType()) {
    return BasicObject(BasicType::Bool,
                       a.Get(a.GetType()) == b.Get(b.GetType()));
  }
  throw std::runtime_error("Different types");
}

void EqualOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}