#pragma once

#include "Expression.h"

class NotExpression : public Expression {
 public:
  NotExpression(Expression *expression);
  Expression* GetExpression();
  void Accept(Visitor *visitor) override;
//  int Eval() override;
 private:
  Expression *expression_;
};