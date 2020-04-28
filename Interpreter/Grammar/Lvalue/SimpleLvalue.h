#pragma once

#include "Lvalue.h"

class SimpleLvalue : public Lvalue {
 public:
  SimpleLvalue(std::shared_ptr<Object> type, std::string name);
  void Accept(Visitor *visitor) override;
  std::shared_ptr<Object> GetType() override;
 private:
  std::shared_ptr<SimpleObject> type_;
};