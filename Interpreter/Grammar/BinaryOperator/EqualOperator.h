#pragma once

#include "BinaryOperator.h"

class EqualOperator: public BinaryOperator {
 public:
  std::shared_ptr<Object> eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const override;
  void Accept(Visitor* visitor) override;
};