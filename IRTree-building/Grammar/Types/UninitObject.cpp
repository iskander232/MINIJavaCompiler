#include "UninitObject.h"

std::shared_ptr<Object> UninitObject::GetCopy() {
  return std::dynamic_pointer_cast<Object>(std::shared_ptr<UninitObject>(this));
}
bool UninitObject::IsEqual(std::shared_ptr<Object> other) {
  return std::dynamic_pointer_cast<UninitObject>(other) != nullptr;
}

std::string UninitObject::GetName() {
  return "Uninit object";
}

int UninitObject::GetSize() {
  return 0;
}