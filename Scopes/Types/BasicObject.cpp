#include "BasicObject.h"

#include <stdexcept>
#include <string>

BasicObject::BasicObject(BasicType type, int value) : type_(type), value_(value), is_init_(true) {}

BasicObject::BasicObject(BasicType type) : type_(type), is_init_(false) {}

int BasicObject::Get(BasicType get_type) {
  if (type_ == BasicType::Void) {
    throw std::runtime_error("Can't get value from void");
  }
  if (get_type != type_) {
    throw std::runtime_error("Can't cast " + std::to_string(type_) + " to " + std::to_string(get_type));
  }
  if (!IsInit()) {
    throw std::runtime_error("The variable is not initialized");
  }
  return value_;
}

bool BasicObject::IsInit() {
  return is_init_;
}

BasicType BasicObject::GetType() {
  return type_;
}