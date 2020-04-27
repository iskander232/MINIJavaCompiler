#include "ArrayLvalue.h"

#include "Types/ArrayObject.h"

#include <stdexcept>

ArrayLvalue::ArrayLvalue(std::shared_ptr<Object> type, std::string name) :
    Lvalue(name),
    type_(std::dynamic_pointer_cast<ArrayObject>(type)) {
  if (type_ == nullptr) {
    throw std::runtime_error("It's not array");
  }
}

std::shared_ptr<Object> ArrayLvalue::GetType() {
  return std::dynamic_pointer_cast<Object>(type_);
}

void ArrayLvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
