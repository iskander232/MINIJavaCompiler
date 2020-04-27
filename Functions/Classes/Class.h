#pragma once

#include "BaseElement/BaseElement.h"
#include "Declarations/DeclarationList.h"

#include <string>
class Class : public BaseElement {
 public:
  Class(std::string name, DeclarationList *declaration_list);
  std::string GetName();
  DeclarationList *GetDeclarations();

  void Accept(Visitor *visitor) override;
 private:
  std::string name_;
  DeclarationList *declaration_list_;
};