#pragma once

#include "BaseElement/BaseElement.h"

#include <string>

class Lvalue: public BaseElement{
 public:
  virtual std::string GetName() = 0;
};