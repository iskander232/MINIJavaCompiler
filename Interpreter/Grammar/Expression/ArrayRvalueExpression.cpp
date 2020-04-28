#include "ArrayRvalueExpression.h"
#include <Location/Location.h>

#include <stdexcept>

ArrayRvalueExpression::ArrayRvalueExpression(std::shared_ptr<Object> type, Expression *length) :
    type_(std::dynamic_pointer_cast<SimpleObject>(type)), length_(length) {
  if (!type_){
    throw std::runtime_error("Array of non simple type");
  }
}

std::shared_ptr<Object> ArrayRvalueExpression::GetType() {
  return std::dynamic_pointer_cast<Object>(type_);
}

Expression * ArrayRvalueExpression::GetLength() {
  return length_;
}

void ArrayRvalueExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}