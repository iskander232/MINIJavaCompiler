#pragma once

#include <memory>
class Object {
 public:
  virtual bool IsEqual(std::shared_ptr<Object> other) = 0;
};