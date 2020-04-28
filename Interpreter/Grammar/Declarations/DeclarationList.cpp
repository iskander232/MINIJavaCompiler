#include "DeclarationList.h"
#include <Location/Location.h>

#include <stdexcept>

DeclarationList::DeclarationList() {}

DeclarationList::DeclarationList(Declaration *declaration) : declarations_{declaration} {}

void DeclarationList::AddDeclaration(Declaration *declaration) {
  declarations_.push_back(declaration);
}

size_t DeclarationList::GetSize() {
  return declarations_.size();
}

Declaration *DeclarationList::GetIth(int i) {
  if (i < 0 || i >= GetSize()) {
    throw std::runtime_error("Try to get declaration with bad index");
  }
  return declarations_[i];
}

void DeclarationList::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}