#include "VarDecl.h"

void VarDecl::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

std::string VarDecl::GetName() {
  return name_;
}

Object* VarDecl::GetType() {
  return type_;
}

VarDecl::VarDecl(Object *object, std::string name) : type_(object), name_(name) {}