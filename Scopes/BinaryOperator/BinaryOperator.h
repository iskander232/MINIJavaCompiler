#pragma once

#include "BaseElement/BaseElement.h"

class BinaryOperator: public BaseElement{
 public:
  virtual int eval(int a, int b) const = 0;
};