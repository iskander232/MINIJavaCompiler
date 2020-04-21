#include "IdentObject.h"

IdentObject::IdentObject(std::string name, Class *value) : name_(name), value_(value) {}

IdentObject::IdentObject(std::string name) : name_(name), value_(nullptr) {}


void IdentObject::SetValue(Class *value) {
  value_ = value;
}