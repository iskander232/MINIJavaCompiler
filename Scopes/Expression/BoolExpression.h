#pragma once

#include "Expression.h"
#include "Types/BasicObject.h"

class BoolExpression: public Expression{
 public:
  BoolExpression(bool value);
  BasicObject* GetValue();
  void Accept(Visitor* visitor) override ;
//  int Eval() override ;
 private:
  BasicObject* value_;
};