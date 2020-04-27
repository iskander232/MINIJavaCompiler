#pragma once

#include "Statement.h"
#include "Expression/ExprList.h"

class ReturnStatement : public Statement {
 public:
  explicit ReturnStatement(Expression* expression);

  Expression* GetExpr();

  void Accept(Visitor *visitor) override;
 private:
  Expression* expression_;
};