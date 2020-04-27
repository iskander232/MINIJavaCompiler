#include "OrOperator.h"

#include "Types/Bool.h"

#include <stdexcept>

std::shared_ptr<Object> OrOperator::eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const {
  auto a_bool = std::dynamic_pointer_cast<BoolObject>(a);
  auto b_bool = std::dynamic_pointer_cast<BoolObject>(b);
  if (a_bool.get() && b_bool.get()) {
    return std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(
        a_bool->GetValue() || b_bool->GetValue())));
  } else {
    throw std::runtime_error("Can't cast to bool");
  }
}

void OrOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}