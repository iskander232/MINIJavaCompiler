#include "NumberExpression.h"

NumberExpression::NumberExpression(int num): number_(num) {};

int NumberExpression::GetNumber() {
  return number_;
}

//int NumberExpression::Eval() {
//  return number_;
//}

void NumberExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

