#pragma once

#include "Object.h"

class UninitObject : public Object {
 public:
  bool IsEqual(std::shared_ptr<Object> other) override ;
};