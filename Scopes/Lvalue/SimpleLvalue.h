#pragma once

#include "Lvalue.h"

#include <string>

class SimpleLvalue: public Lvalue{
 public:

  explicit SimpleLvalue(std::string name);
  SimpleLvalue(SimpleObject* object, std::string name);

  Object* GetType() override ;
  std::string GetName() override ;
  void Accept(Visitor* visitor) override ;
 private:
  std::string name_;
  Object* type_;
};