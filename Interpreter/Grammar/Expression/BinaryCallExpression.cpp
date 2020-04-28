#include "BinaryCallExpression.h"
#include <Location/Location.h>

BinaryCallExpression::BinaryCallExpression(Expression *first, BinaryOperator *binary_operator, Expression *second)
    : first_(first), binary_operator_(
    binary_operator), second_(second) {};

void BinaryCallExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}

Expression *BinaryCallExpression::GetFirst() {
  return first_;
}

Expression *BinaryCallExpression::GetSecond() {
  return second_;
}

BinaryOperator *BinaryCallExpression::GetOperator() {
  return binary_operator_;
}