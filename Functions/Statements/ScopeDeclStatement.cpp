#include "ScopeDeclStatement.h"

ScopeDeclStatement::ScopeDeclStatement(StatementsList *statements_list) :
    statements_list_(statements_list) {};

StatementsList *ScopeDeclStatement::GetStatementsList() {
  return statements_list_;
}

void ScopeDeclStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}