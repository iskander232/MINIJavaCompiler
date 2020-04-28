#pragma once

#include "Grammar/BaseElement/BaseElement.h"

#include "Types/Object.h"
#include <memory>
class BinaryOperator : public BaseElement {
 public:
  virtual std::shared_ptr<Object> eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const = 0;
};