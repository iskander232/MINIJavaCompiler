#include "Lvalue.h"

#include "Types/UninitObject.h"

Lvalue::Lvalue(std::string name)
    : name_(name) {}

std::string Lvalue::GetName() {
  return name_;
}

std::shared_ptr<Object> Lvalue::GetType() {
  return std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()));
}

void Lvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
