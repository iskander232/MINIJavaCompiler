#pragma once

#include "Lvalue.h"

class ArrayLvalue : public Lvalue {
 public:
  ArrayLvalue(std::shared_ptr<Object> type, std::string name);
  void Accept(Visitor *visitor) override;
  std::shared_ptr<Object> GetType() override ;
 private:
  std::shared_ptr<ArrayObject> type_;
};