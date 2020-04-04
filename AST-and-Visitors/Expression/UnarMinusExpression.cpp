#include "UnarMinusExpression.h"

UnarMinusExpression::UnarMinusExpression(Expression *expression) : expression_(expression) {}

Expression *UnarMinusExpression::GetExpression() {
  return expression_;
}

void UnarMinusExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
//
//int UnarMinusExpression::Eval() {
//  return -expression_->Eval();
//}