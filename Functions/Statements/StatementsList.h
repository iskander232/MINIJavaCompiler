#pragma once

#include "BaseElement/BaseElement.h"
#include "Statement.h"

#include <vector>

class StatementsList : public BaseElement {
 public:
  void AddStatement(Statement *statement);
  void Accept(Visitor *visitor) override ;
  size_t GetSize();
  Statement* GetIth(int i);
 private:
  std::vector<Statement *> statements_list_;
};