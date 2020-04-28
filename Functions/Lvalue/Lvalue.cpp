#include "Lvalue.h"
#include <Location/Location.h>

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
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}
