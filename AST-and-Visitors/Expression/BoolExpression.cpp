#include "BoolExpression.h"

BoolExpression::BoolExpression(bool value): value_(value) {};

int BoolExpression::GetValue() {
  return value_;
}
//int BoolExpression::Eval() {
//  return value_;
//}

void BoolExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}