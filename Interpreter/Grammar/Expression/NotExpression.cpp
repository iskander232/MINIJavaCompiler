#include "NotExpression.h"
#include <Location/Location.h>

NotExpression::NotExpression(Expression *expression):expression_(expression) {};

Expression* NotExpression::GetExpression() {
  return expression_;
}
//int NotExpression::Eval() {
//  return !expression_->Eval();
//}

void NotExpression::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}