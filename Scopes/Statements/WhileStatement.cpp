#include "WhileStatement.h"

WhileStatement::WhileStatement(Expression *expression, StatementsList *statements_list) :
    expression_(expression), statements_list_(statements_list) {};

Expression * WhileStatement::GetExpression() {
  return expression_;
}

StatementsList * WhileStatement::GetStatementsList() {
  return statements_list_;
}

void WhileStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}