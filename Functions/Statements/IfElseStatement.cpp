#include "IfElseStatement.h"

IfElseStatement::IfElseStatement(Expression *expression,
                                 StatementsList *if_statements_list,
                                 StatementsList *else_statements_list) :
    expression_(expression),
    if_statements_list_(if_statements_list),
    else_statements_list_(else_statements_list) {}

Expression *IfElseStatement::GetExpression() {
  return expression_;
}

StatementsList *IfElseStatement::GetIfStatements() {
  return if_statements_list_;
}

StatementsList *IfElseStatement::GetElseStatements() {
  return else_statements_list_;
}

void IfElseStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}