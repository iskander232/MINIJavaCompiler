#include "Types/SimpleObject.h"
#include "Types/UninitObject.h"

#include "SimpleLvalue.h"

#include <stdexcept>

SimpleLvalue::SimpleLvalue(std::string name)
    : name_(name), type_(dynamic_cast<Object *>(new UninitObject())) {}

SimpleLvalue::SimpleLvalue(SimpleObject *object, std::string name)
    : type_(object), name_(name) {}

std::string SimpleLvalue::GetName() {
  return name_;
}

Object *SimpleLvalue::GetType() {
  return dynamic_cast<Object *>(type_);
}

void SimpleLvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}