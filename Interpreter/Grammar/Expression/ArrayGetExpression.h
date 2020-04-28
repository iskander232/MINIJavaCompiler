#pragma once

#include "Expression.h"

class ArrayGetExpression: public Expression{
 public:
  ArrayGetExpression(Expression* array, Expression* index);
  Expression* GetArray();
  Expression* GetIndex();
  void Accept(Visitor* visitor) override;
 private:
  Expression* array_;
  Expression* index_;
};