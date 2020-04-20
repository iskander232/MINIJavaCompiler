#pragma once

#include "Statement.h"
#include "Expression/Expression.h"
#include "Statements/StatementsList.h"

class IfStatement : public Statement {
 public:
  IfStatement(Expression *expression, StatementsList *statements_list);

  Expression *GetExpression();
  StatementsList *GetStatements();

  void Accept(Visitor* visitor) override ;
 private:
  Expression *expression_;
  StatementsList *statements_list_;
};