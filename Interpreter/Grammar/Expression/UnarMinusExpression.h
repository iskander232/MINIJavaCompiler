#pragma once

#include "Expression.h"

class UnarMinusExpression : public Expression {
 public:
  UnarMinusExpression(Expression *expression);
  Expression *GetExpression();
  void Accept(Visitor *visitor) override;
//  int Eval() override ;
 private:
  Expression *expression_;
};