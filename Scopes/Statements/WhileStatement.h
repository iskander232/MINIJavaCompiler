#pragma once

#include "Statement.h"

#include "Expression/Expression.h"
#include "StatementsList.h"

class WhileStatement : public Statement {
 public:
  WhileStatement(Expression *expression, StatementsList *statements_list);

  Expression *GetExpression();
  StatementsList *GetStatementsList();

  void Accept(Visitor *visitor) override;
 private:
  Expression *expression_;
  StatementsList *statements_list_;
};