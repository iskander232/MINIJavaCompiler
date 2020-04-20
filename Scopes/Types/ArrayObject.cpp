#include "ArrayObject.h"

ArrayObject::ArrayObject(SimpleObject object, Expression *length)
    : simple_object_(object), length_(length), is_init_(true) {}
ArrayObject::ArrayObject(SimpleObject object) : simple_object_(object), length_(nullptr), is_init_(false) {}

bool ArrayObject::IsInit() {
  return is_init_;
}

Expression *ArrayObject::GetLength() {
  return length_;
}

SimpleObject ArrayObject::GetObject() {
  return simple_object_;
}