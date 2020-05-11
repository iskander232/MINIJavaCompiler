#include "Location.h"

Location &Location::GetInstance() {
  static Location storage;
  return storage;
}

void Location::SetLoc(BaseElement *base_element, yy::location loc) {
  locations_[base_element] = loc;
}

void Location::SetElement(BaseElement *element) {
  element_.push(element);
}

void Location::SetPrevLoc() {
  element_.pop();
}

yy::location Location::LastLoc() {
  if (element_.empty()) {
    throw std::runtime_error("not in visitor");
  }
  return locations_[element_.top()];
}