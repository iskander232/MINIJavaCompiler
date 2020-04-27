#include "IdentExpression.h"

IdentExpression::IdentExpression(std::string name) : name_(name) {}

std::string IdentExpression::GetName() {
  return name_;
}

void IdentExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}