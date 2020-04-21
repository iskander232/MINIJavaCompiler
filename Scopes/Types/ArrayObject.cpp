#include "ArrayObject.h"

ArrayObject::ArrayObject(SimpleObject object, Expression *length)
    : simple_object_(object), length_(length) {}
ArrayObject::ArrayObject(SimpleObject object) : simple_object_(object), length_(nullptr) {}


Expression *ArrayObject::GetLength() {
  return length_;
}

SimpleObject ArrayObject::GetObject() {
  return simple_object_;
}