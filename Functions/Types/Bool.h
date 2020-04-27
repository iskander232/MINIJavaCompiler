#pragma once

#include "SimpleObject.h"

class BoolObject : public SimpleObject {
 public:
  explicit BoolObject(int value);
  bool GetValue();

  bool IsEqual(std::shared_ptr<Object> other) override;
  std::shared_ptr<Object> GetCopy() override;
  int value_;
};