#pragma once

#include "BinaryOperator.h"

class MinusOperator: public BinaryOperator{
 public:
  int eval(int a, int b) const override ;
  void Accept(Visitor* visitor) override ;
};