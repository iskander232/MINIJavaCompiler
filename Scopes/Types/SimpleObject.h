#pragma once

#include "Object.h"

class SimpleObject : public Object {
 public:
  bool IsEqual(std::shared_ptr<Object> other) override final;
};