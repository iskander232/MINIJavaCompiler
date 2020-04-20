#include "IdentObject.h"

IdentObject::IdentObject(std::string name, Class *value) : name_(name), value_(value), is_init_(true) {}

IdentObject::IdentObject(std::string name) : name_(name), value_(nullptr), is_init_(false) {}

bool IdentObject::IsInit() {
  return is_init_;
}

void IdentObject::SetValue(Class *value) {
  value_ = value;
  is_init_ = true;
}