#include "Integer.h"

IntegerObject::IntegerObject(int value) : value_(value) {}

int IntegerObject::GetValue() {
  return value_;
}

std::shared_ptr<Object> IntegerObject::GetCopy() {
  return std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(value_)));
}

bool IntegerObject::IsEqual(std::shared_ptr<Object> other) {
  return nullptr != std::dynamic_pointer_cast<IntegerObject>(other);
}