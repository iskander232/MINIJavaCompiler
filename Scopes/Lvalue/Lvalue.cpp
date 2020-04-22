#include "Lvalue.h"

#include "Types/UninitObject.h"

Lvalue::Lvalue(std::string name)
    : name_(name),
      type_(std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()))) {}

Lvalue::Lvalue(std::shared_ptr<Object> type, std::string name) : type_(type), name_(name) {}
std::string Lvalue::GetName() {
  return name_;
}

std::shared_ptr<Object> Lvalue::GetType() {
  return type_;
}

void Lvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
