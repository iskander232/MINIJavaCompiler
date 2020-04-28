#include "IdentExpression.h"
#include <Location/Location.h>

IdentExpression::IdentExpression(std::string name) : name_(name) {}

std::string IdentExpression::GetName() {
  return name_;
}

void IdentExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}