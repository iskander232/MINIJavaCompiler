#pragma once

#include <memory>
#include <string>

class Object {
 public:
  virtual bool IsEqual(std::shared_ptr<Object> other) = 0;
  virtual std::shared_ptr<Object> GetCopy() = 0;
  virtual std::string GetName() = 0;
  virtual ~Object() = default;
};