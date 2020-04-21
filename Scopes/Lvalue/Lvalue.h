#pragma once

#include "BaseElement/BaseElement.h"
#include "Types/Object.h"

#include <string>

class Lvalue: public BaseElement{
 public:
  virtual std::string GetName() = 0;
  virtual Object* GetType() = 0;
};