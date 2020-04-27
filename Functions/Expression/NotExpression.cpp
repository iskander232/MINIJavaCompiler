#include "NotExpression.h"

NotExpression::NotExpression(Expression *expression):expression_(expression) {};

Expression* NotExpression::GetExpression() {
  return expression_;
}
//int NotExpression::Eval() {
//  return !expression_->Eval();
//}

void NotExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}