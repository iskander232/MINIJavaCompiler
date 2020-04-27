#include "IdentCreateExpression.h"


IdentCreateExpression::IdentCreateExpression(std::string name): name_(name) {}

std::string IdentCreateExpression::GetName() {
  return name_;
}

void IdentCreateExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}