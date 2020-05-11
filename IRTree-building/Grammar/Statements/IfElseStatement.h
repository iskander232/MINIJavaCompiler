#pragma once

#include "Statement.h"
#include "Expression/Expression.h"
#include "StatementsList.h"

class IfElseStatement : public Statement {
 public:
  IfElseStatement(Expression *expression, StatementsList *if_statements_list, StatementsList* else_statements_list);

  Expression *GetExpression();
  StatementsList *GetIfStatements();
  StatementsList* GetElseStatements();

  void Accept(Visitor* visitor) override;
 private:
  Expression *expression_;
  StatementsList *if_statements_list_;
  StatementsList *else_statements_list_;
};