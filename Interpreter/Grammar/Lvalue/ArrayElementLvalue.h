#pragma once

#include "Lvalue.h"

class ArrayElementLvalue : public Lvalue {
 public:
  ArrayElementLvalue(std::string name, Expression *position);
  void Accept(Visitor *visitor) override;
  Expression* GetPos();
  std::shared_ptr<Object> GetType() override ;
 private:
  Expression *position_;
};