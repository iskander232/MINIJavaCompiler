#pragma once

#include "BaseElement/BaseElement.h"
#include "Declaration.h"

#include <vector>
class DeclarationList : public BaseElement {
 public:
  DeclarationList();
  explicit DeclarationList(Declaration *declaration);

  void AddDeclaration(Declaration *declaration);

  size_t GetSize();
  Declaration *GetIth(int i);

  void Accept(Visitor *visitor) override ;
 private:
  std::vector<Declaration *> declarations_;
};