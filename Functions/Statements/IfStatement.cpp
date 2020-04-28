#include "IfStatement.h"
#include <Location/Location.h>

IfStatement::IfStatement(Expression *expression, StatementsList *statements_list)
    : expression_(expression), statements_list_(statements_list) {};

Expression *IfStatement::GetExpression() {
  return expression_;
}

StatementsList *IfStatement::GetStatements() {
  return statements_list_;
}

void IfStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}