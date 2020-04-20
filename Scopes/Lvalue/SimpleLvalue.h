#pragma once

#include "Lvalue.h"

#include <string>

class SimpleLvalue: public Lvalue{
 public:

  explicit SimpleLvalue(std::string name);
  SimpleLvalue(BasicObject* object, std::string name);

  BasicObject* GetType() override ;
  std::string GetName() override ;
  void Accept(Visitor* visitor) override ;
 private:
  std::string name_;
  BasicObject* type_;
};