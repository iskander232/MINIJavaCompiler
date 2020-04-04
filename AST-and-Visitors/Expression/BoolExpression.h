#pragma once

#include "Expression.h"

class BoolExpression: public Expression{
 public:
  BoolExpression(bool value);
  int GetValue();
  void Accept(Visitor* visitor) override ;
//  int Eval() override ;
 private:
  int value_;
};