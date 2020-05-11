#pragma once

#include "Declaration.h"

#include <string>
#include "Types/Object.h"

class VarDecl : public Declaration {
 public:
  VarDecl(std::shared_ptr<Object>object, std::string name);
  std::string GetName();
  std::shared_ptr<Object> GetType();
  void Accept(Visitor *visitor) override;
 private:
  std::shared_ptr<Object> type_;
  std::string name_;
};