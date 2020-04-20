#include <Types/BasicObject.h>
#include "SimpleLvalue.h"


SimpleLvalue::SimpleLvalue(std::string name) : name_(name), type_(new BasicObject(BasicType::Void)) {}

SimpleLvalue::SimpleLvalue(BasicObject* object, std::string name) : type_(object), name_(name) {}

std::string SimpleLvalue::GetName() {
  return name_;
}

BasicObject* SimpleLvalue::GetType() {
  return type_;
}
void SimpleLvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}