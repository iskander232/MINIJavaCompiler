#include "ArrayLvalue.h"

#include "Types/ArrayObject.h"
#include "Types/UninitObject.h"

#include <stdexcept>
ArrayLvalue::ArrayLvalue(ArrayObject *object, std::string name)
    : type_(dynamic_cast<Object *>(object)), name_(name) {
  if (type_ == nullptr) {
    throw std::runtime_error("Can't cast Object to ArrayObject");
  }
}

ArrayLvalue::ArrayLvalue(std::string name) :
    type_(dynamic_cast<Object *>(new UninitObject())),
    name_(name) {};

std::string ArrayLvalue::GetName() {
  return name_;
}

Object *ArrayLvalue::GetType() {
  return dynamic_cast<Object *>(type_);
}