#include "OutStatement.h"

OutStatement::OutStatement(Expression *expression): expression_(expression) {}

Expression* OutStatement::GetExpression() {
  return expression_;
}

void OutStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}