#include "AssertStatement.h"

AssertStatement::AssertStatement(Expression* expression): expression_(expression){}

Expression* AssertStatement::GetExpression() {
  return expression_;
}

void AssertStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}