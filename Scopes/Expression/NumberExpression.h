#pragma once

#include "Expression.h"
#include "Types/BasicObject.h"

class NumberExpression: public Expression{
 public:
  explicit NumberExpression(int num);
  BasicObject* GetNumber();
  void Accept(Visitor* visitor) override ;
 private:
  BasicObject* number_;
};