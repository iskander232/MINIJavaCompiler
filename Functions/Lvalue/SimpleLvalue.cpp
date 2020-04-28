#include "SimpleLvalue.h"
#include "Types/SimpleObject.h"
#include <Location/Location.h>
#include <stdexcept>

SimpleLvalue::SimpleLvalue(std::shared_ptr<Object> type, std::string name)
    : Lvalue(name), type_(std::dynamic_pointer_cast<SimpleObject>(type)) {
  if (type_ == nullptr){
    throw std::runtime_error("It's not simple type");
  }
}

std::shared_ptr<Object> SimpleLvalue::GetType() {
  return std::dynamic_pointer_cast<Object>(type_);
}

void SimpleLvalue::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}