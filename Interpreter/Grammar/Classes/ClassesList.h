#pragma once

#include "BaseElement/BaseElement.h"
#include "Class.h"

#include <vector>

class ClassesList : public BaseElement {
 public:
  void AddClass(Class *clas);
  void Accept(Visitor *visitor) override;
  size_t GetSize();
  Class* GetIth(int i);
 private:
  std::vector<Class *> classes_list_;
};