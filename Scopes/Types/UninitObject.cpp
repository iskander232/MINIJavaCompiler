#include "UninitObject.h"

bool UninitObject::IsEqual(std::shared_ptr<Object> other) {
  return std::dynamic_pointer_cast<UninitObject>(other) != nullptr;
}