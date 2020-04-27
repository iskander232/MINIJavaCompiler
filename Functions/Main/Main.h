#pragma once

#include "BaseElement/BaseElement.h"
#include "Statements/StatementsList.h"

#include <string>

class Main : public BaseElement {
 public:
  Main(std::string name, StatementsList *statements_list);
  std::string GetName();
  StatementsList* GetStatementsList();
  void Accept(Visitor *visitor) override;
 private:
  std::string name_;
  StatementsList *statements_list_;
};