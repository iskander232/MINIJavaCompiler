#include "ScopeDeclStatement.h"
#include <Location/Location.h>

ScopeDeclStatement::ScopeDeclStatement(StatementsList *statements_list) :
    statements_list_(statements_list) {};

StatementsList *ScopeDeclStatement::GetStatementsList() {
  return statements_list_;
}

void ScopeDeclStatement::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}