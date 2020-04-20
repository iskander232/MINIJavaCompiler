#pragma once

#include "Statements/Statement.h"

#include <string>
#include "Types/Object.h"

class VarDecl : public Statement {
 public:
  VarDecl(Object *object, std::string name);
  std::string GetName();
  Object *GetType();
  void Accept(Visitor *visitor) override;
 private:
  Object *type_;
  std::string name_;
};