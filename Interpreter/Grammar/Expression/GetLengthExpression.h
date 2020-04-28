#pragma once

#include "Expression.h"

class GetLengthExpression: public Expression{
 public:
  GetLengthExpression(Expression* array);
  Expression* GetArray();

  void Accept(Visitor* visitor) override ;
 private:
  Expression* array_;
};