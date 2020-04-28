#pragma once

#include "Expression.h"
#include "BinaryOperator/BinaryOperator.h"

class BinaryCallExpression: public Expression{
 public:
  BinaryCallExpression(Expression* first, BinaryOperator* binary_operator, Expression* second);
  void Accept(Visitor* visitor) override ;
  Expression* GetFirst();
  Expression* GetSecond();
  BinaryOperator* GetOperator();
//  int eEval() override ;
 private:
  Expression* first_;
  Expression* second_;
  BinaryOperator* binary_operator_;
};