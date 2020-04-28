#pragma once

#include "Statement.h"

#include "Expression/Expression.h"

class ScopeDeclStatement : public Statement {
 public:
  ScopeDeclStatement(StatementsList *statements_list);

  StatementsList* GetStatementsList();

  void Accept(Visitor *visitor) override ;
 private:
  StatementsList *statements_list_;
};