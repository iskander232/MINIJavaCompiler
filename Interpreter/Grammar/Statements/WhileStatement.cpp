#include "WhileStatement.h"
#include <Location/Location.h>

WhileStatement::WhileStatement(Expression *expression, StatementsList *statements_list) :
    expression_(expression), statements_list_(statements_list) {};

Expression * WhileStatement::GetExpression() {
  return expression_;
}

StatementsList * WhileStatement::GetStatementsList() {
  return statements_list_;
}

void WhileStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}