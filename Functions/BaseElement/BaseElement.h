#pragma once

#include "Visitors/Visitor.h"

class BaseElement {
 public:
  virtual void Accept(Visitor* visitor) = 0;
  virtual ~BaseElement() = default;
};
