#include "StatementsList.h"

void StatementsList::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

void StatementsList::AddStatement(Statement *statement) {
  statements_list_.push_back(statement);
}

size_t StatementsList::GetSize() {
  return statements_list_.size();
}

Statement * StatementsList::GetIth(int i) {
  return statements_list_[i];
}