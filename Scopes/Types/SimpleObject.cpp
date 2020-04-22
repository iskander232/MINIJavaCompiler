#include "SimpleObject.h"

bool SimpleObject::IsEqual(std::shared_ptr<Object> other) {
  auto simple_other = std::dynamic_pointer_cast<SimpleObject>(other);
  if (simple_other) {
    return typeid(*this) == typeid(*simple_other);
  }
  return false;
}