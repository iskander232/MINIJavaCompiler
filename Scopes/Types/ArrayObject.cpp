#include "ArrayObject.h"
#include "Types/UninitObject.h"

#include <stdexcept>

ArrayObject::ArrayObject(std::shared_ptr<Object> object)
    : object_(std::dynamic_pointer_cast<SimpleObject>(object)), length_(-1) {
  if (nullptr != std::dynamic_pointer_cast<UninitObject>(object_) || nullptr == object_) {
    throw std::runtime_error("Can't make array of non simple type");
  }
}
ArrayObject::ArrayObject(std::shared_ptr<Object> object, int length)
    : object_(std::dynamic_pointer_cast<SimpleObject>(object)),
      length_(length),
      elements_(length_, std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()))) {
  if (nullptr != std::dynamic_pointer_cast<UninitObject>(object_) || nullptr == object_) {
    throw std::runtime_error("Can't make array of non simple type");
  }
}
size_t ArrayObject::GetLength() {
  return length_;
}

std::shared_ptr<Object> ArrayObject::GetObject() {
  return object_;
}

std::shared_ptr<Object> ArrayObject::GetIth(int i) {
  if (i >= length_ || i < 0) {
    throw std::runtime_error("Try to get element with bad index");
  }
  return elements_[i];
}

void ArrayObject::SetIth(int i, std::shared_ptr<Object> object) {
  if (typeid(*object_) != typeid(*object)) {
    throw std::runtime_error("Bad type");
  }
  if (i < 0 || i >= length_) {
    throw std::runtime_error("Bad index");
  }
  elements_[i] = object;
}

bool ArrayObject::IsEqual(std::shared_ptr<Object> other) {
  auto other_array = std::dynamic_pointer_cast<ArrayObject>(other);
  if (!other_array)
    return false;
  return object_->IsEqual(other_array->GetObject());
}

