#pragma once

#include "SimpleObject.h"

class BoolObject : public SimpleObject {
 public:
  explicit BoolObject(int value);
  bool GetValue();
 private:
  int value_;
};