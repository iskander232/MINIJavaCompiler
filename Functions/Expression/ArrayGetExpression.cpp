#include "ArrayGetExpression.h"

ArrayGetExpression::ArrayGetExpression(Expression *array, Expression *index): array_(array), index_(index) {}

Expression * ArrayGetExpression::GetArray() {
  return array_;
}

Expression * ArrayGetExpression::GetIndex() {
  return index_;
}

void ArrayGetExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}