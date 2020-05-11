#pragma once

#include "Object.h"

class UninitObject : public Object {
 public:
  std::shared_ptr<Object> GetCopy() override;
  bool IsEqual(std::shared_ptr<Object> other) override;
  std::string GetName() override ;
  int GetSize() override ;
  ~UninitObject(){}
};