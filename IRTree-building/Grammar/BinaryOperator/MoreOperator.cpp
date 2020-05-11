#include "MoreOperator.h"

#include "Types/Bool.h"
#include "Types/Integer.h"
#include <Location/Location.h>

#include <stdexcept>

std::shared_ptr<Object> MoreOperator::eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const {
  auto a_int = std::dynamic_pointer_cast<IntegerObject>(a);
  auto b_int = std::dynamic_pointer_cast<IntegerObject>(b);
  if (a_int.get() && b_int.get()) {
    return std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(
        a_int->GetValue() > b_int->GetValue())));
  } else {
    throw std::runtime_error("Can't cast to int");
  }
}

void MoreOperator::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}