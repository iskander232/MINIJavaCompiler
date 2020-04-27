#include "GetLengthExpression.h"

GetLengthExpression::GetLengthExpression(Expression *array): array_(array) {}

Expression * GetLengthExpression::GetArray() {
  return array_;
}

void GetLengthExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}