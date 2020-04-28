#pragma once

#include "Expression.h"
#include "Types/SimpleObject.h"

class ArrayRvalueExpression: public Expression{
 public:
  ArrayRvalueExpression(std::shared_ptr<Object> type, Expression* length);

  Expression* GetLength();
  std::shared_ptr<Object> GetType();

  void Accept(Visitor* visitor) override ;
 private:
  std::shared_ptr<Object> type_;
  Expression* length_;
};