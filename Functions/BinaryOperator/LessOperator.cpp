#include "LessOperator.h"

#include "Types/Integer.h"
#include "Types/Bool.h"

#include <stdexcept>

std::shared_ptr<Object> LessOperator::eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const {
  auto a_int = std::dynamic_pointer_cast<IntegerObject>(a);
  auto b_int = std::dynamic_pointer_cast<IntegerObject>(b);
  if (a_int.get() && b_int.get()) {
    return std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(
        a_int->GetValue() < b_int->GetValue())));
  } else {
    throw std::runtime_error("Can't cast to int");
  }
}

void LessOperator::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
