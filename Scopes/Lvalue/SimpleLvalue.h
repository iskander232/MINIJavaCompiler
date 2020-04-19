#pragma once

#include "Lvalue.h"

#include <string>

class SimpleLvalue: public Lvalue{
 public:
  SimpleLvalue(std::string name);
  std::string GetName() override ;
  void Accept(Visitor* visitor) override;
 private:
  std::string name_;
};