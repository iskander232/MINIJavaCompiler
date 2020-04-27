#include "Formals.h"

#include <stdexcept>

Formals::Formals() {}

Formals::Formals(std::shared_ptr<Object> object, std::string name) : formals_{std::make_pair(object, name)} {}

void Formals::AddFormals(std::shared_ptr<Object> object, std::string name) {
  formals_.push_back(std::make_pair(object, name));
}

size_t Formals::GetSize() {
  return formals_.size();
}

formal Formals::GetIth(int i) {
  if (i < 0 || i >= GetSize()) {
    throw std::runtime_error("Bad index of formal");
  }
  return formals_[i];
}

void Formals::Accept(Visitor *visitor) {
  visitor->Visit(this);
}