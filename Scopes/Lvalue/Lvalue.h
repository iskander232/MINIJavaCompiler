#pragma once

#include "BaseElement/BaseElement.h"
#include "Types/Object.h"

#include <string>

class Lvalue : public BaseElement {
 public:
  Lvalue(std::string name);
  Lvalue(std::shared_ptr<Object> type, std::string name);
  std::string GetName();
  void Accept(Visitor *visitor) override;
  std::shared_ptr<Object> GetType();
 private:
  std::string name_;
  std::shared_ptr<Object> type_;
};