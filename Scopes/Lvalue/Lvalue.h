#pragma once

#include "BaseElement/BaseElement.h"
#include "Types/Object.h"

#include <string>

class Lvalue : public BaseElement {
 public:
  explicit Lvalue(std::string name);
  std::string GetName();
  void Accept(Visitor *visitor) override;
  virtual std::shared_ptr<Object> GetType();
 private:
  std::string name_;
};