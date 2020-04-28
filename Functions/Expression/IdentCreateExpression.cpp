#include "IdentCreateExpression.h"
#include <Location/Location.h>


IdentCreateExpression::IdentCreateExpression(std::string name): name_(name) {}

std::string IdentCreateExpression::GetName() {
  return name_;
}

void IdentCreateExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}