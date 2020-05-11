#pragma once

#include "Statement.h"
#include "Expression/Expression.h"

class OutStatement: public Statement{
 public:
  OutStatement(Expression* expression);
  Expression* GetExpression();
  void Accept(Visitor* visitor) override ;
 private:
  Expression* expression_;
};