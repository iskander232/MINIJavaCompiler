#pragma once

#include "BaseElement/BaseElement.h"
#include "Types/BasicObject.h"

class BinaryOperator : public BaseElement {
 public:
  virtual BasicObject eval(BasicObject a, BasicObject b) const = 0;
};