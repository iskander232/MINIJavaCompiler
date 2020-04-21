#include "Bool.h"

BoolObject::BoolObject(int value) : value_(value) {}

bool BoolObject::GetValue() {
  return value_;
}