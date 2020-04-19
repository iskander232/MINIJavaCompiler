#include "SimpleLvalue.h"

SimpleLvalue::SimpleLvalue(std::string name): name_(name) {}

std::string SimpleLvalue::GetName() {
  return name_;
}

void SimpleLvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}