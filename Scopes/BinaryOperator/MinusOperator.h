#pragma once

#include "BinaryOperator.h"

class MinusOperator: public BinaryOperator{
 public:
  BasicObject eval(BasicObject a, BasicObject b) const override ;
  void Accept(Visitor* visitor) override ;
};