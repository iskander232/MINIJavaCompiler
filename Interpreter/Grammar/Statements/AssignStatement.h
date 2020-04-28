#pragma once

#include "Statement.h"

#include "Lvalue/Lvalue.h"
#include "Expression/Expression.h"


class AssignStatement: public Statement{
 public:
  AssignStatement(Lvalue* lvalue, Expression* expression);
  void Accept(Visitor* visitor) override ;
  Expression* GetExpression();
  Lvalue* GetLvalue();
 private:
  Expression* expression_;
  Lvalue* lvalue_;
};