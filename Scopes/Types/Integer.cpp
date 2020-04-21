#include "Integer.h"

IntegerObject::IntegerObject(int value) : value_(value) {}

int IntegerObject::GetValue() {
  return value_;
}