#pragma once

#include "Lvalue.h"

class ArrayLvalue : public Lvalue {
 public:
  ArrayLvalue(ArrayObject *object, std::string name);
  explicit ArrayLvalue(std::string name);
  std::string GetName() override;
  Object *GetType() override;
 private:
  Object *type_;
  std::string name_;
};