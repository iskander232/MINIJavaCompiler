#include "AndOperator.h"

#include "Types/Bool.h"
#include <Location/Location.h>
#include <stdexcept>

std::shared_ptr<Object> AndOperator::eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const {
  auto a_bool = std::dynamic_pointer_cast<BoolObject>(a);
  auto b_bool = std::dynamic_pointer_cast<BoolObject>(b);
  if (a_bool.get() && b_bool.get()) {
    return std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(
        a_bool->GetValue() && b_bool->GetValue())));
  } else {
    throw std::runtime_error("Can't cast to bool");
  }
}

void AndOperator::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}