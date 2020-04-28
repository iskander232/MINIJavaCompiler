#include "VarDecl.h"
#include <Location/Location.h>

void VarDecl::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}

std::string VarDecl::GetName() {
  return name_;
}

std::shared_ptr<Object> VarDecl::GetType() {
  return type_;
}

VarDecl::VarDecl(std::shared_ptr<Object> object, std::string name) : type_(object), name_(name) {}