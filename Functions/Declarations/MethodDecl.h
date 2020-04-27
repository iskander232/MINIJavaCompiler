#pragma once

#include "Declaration.h"
#include "Formals.h"
#include "Types/Object.h"
#include "Statements/StatementsList.h"

#include <memory>
#include <string>

class MethodDecl : public Declaration {
 public:
  MethodDecl(std::shared_ptr<Object> type, std::string name, Formals *formals, StatementsList *statements_list);
  std::shared_ptr<Object> GetType();
  std::string GetName();
  Formals *GetFormals();
  StatementsList *GetStatements();
  void Accept(Visitor *visitor) override;
 private:
  std::shared_ptr<Object> type_;
  std::string name_;
  Formals *formals_;
  StatementsList *statements_list_;
};