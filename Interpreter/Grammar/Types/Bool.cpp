#include "Bool.h"

BoolObject::BoolObject(int value) : value_(value) {}

bool BoolObject::GetValue() {
  return value_;
}

bool BoolObject::IsEqual(std::shared_ptr<Object> other) {
  return nullptr != std::dynamic_pointer_cast<BoolObject>(other);
}

std::shared_ptr<Object> BoolObject::GetCopy() {
  return std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(value_)));
}