#pragma once

#include "Statement.h"
#include "Expression/Expression.h"

class AssertStatement: public Statement{
 public:
  AssertStatement(Expression* expression);
  Expression* GetExpression();
  void Accept(Visitor* visitor) override ;
 private:
  Expression* expression_;
};