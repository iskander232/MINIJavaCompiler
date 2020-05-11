#include "NumberExpression.h"
#include <Location/Location.h>

#include "Types/Integer.h"

NumberExpression::NumberExpression(int num) : number_(new IntegerObject(num)) {};

std::shared_ptr<Object> NumberExpression::GetNumber() {
  return std::dynamic_pointer_cast<Object>(number_);
}

void NumberExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}

