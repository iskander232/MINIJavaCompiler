#include "Location.h"

Location::Location() : last_element(nullptr) {};

Location &Location::GetInstance() {
  static Location storage;
  return storage;
}

void Location::SetLoc(BaseElement *base_element, yy::location loc) {
  locations_[base_element] = loc;
}

void Location::SetElement(BaseElement *element) {
  last_element = element;
}

yy::location Location::LastLoc() {
  if (!last_element) {
    throw std::runtime_error("not in visitor");
  }
  return locations_[last_element];
}