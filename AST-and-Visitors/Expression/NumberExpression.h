#pragma once

#include "Expression.h"

class NumberExpression: public Expression{
 public:
  NumberExpression(int num);
  int GetNumber();
//  int Eval() override ;
  void Accept(Visitor* visitor) override ;
 private:
  int number_;
};