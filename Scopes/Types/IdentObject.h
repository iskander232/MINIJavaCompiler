#pragma once

#include "SimpleObject.h"
#include "Classes/Class.h"

#include <string>

class IdentObject : public SimpleObject {
 public:
  IdentObject(std::string name, Class *value);
  IdentObject(std::string name);

  void SetValue(Class* value);

 private:
  Class *value_;
  std::string name_;
};