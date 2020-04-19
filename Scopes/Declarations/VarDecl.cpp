#include "VarDecl.h"

void VarDecl::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

std::string VarDecl::GetName() {
  return name_;
}

VarDecl::VarDecl(std::string name) : name_(name) {}