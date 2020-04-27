#pragma once

#include "BaseElement/BaseElement.h"
#include "Types/Object.h"

#include <string>
#include <vector>

using formal = std::pair<std::shared_ptr<Object>, std::string>;
class Formals : public BaseElement {
 public:
  Formals();
  Formals(std::shared_ptr<Object> object, std::string name);

  void AddFormals(std::shared_ptr<Object>, std::string name);

  size_t GetSize();
  formal GetIth(int i);

  void Accept(Visitor *visitor) override ;
 private:
  std::vector<formal> formals_;
};