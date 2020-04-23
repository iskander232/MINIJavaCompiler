#include "ArrayElementLvalue.h"
#include "Types/UninitObject.h"
#include <stdexcept>

ArrayElementLvalue::ArrayElementLvalue(std::string name, Expression *position) :
    Lvalue(name), position_(position) {}

std::shared_ptr<Object> ArrayElementLvalue::GetType() {
  return std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()));
}

void ArrayElementLvalue::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

Expression *ArrayElementLvalue::GetPos() {
  return position_;
}
