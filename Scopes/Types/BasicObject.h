#pragma once

#include "SimpleObject.h"

enum BasicType {
  Integer,
  Bool,
  Void
};

class BasicObject : public SimpleObject {
 public:
  BasicObject(BasicType type, int value);
  explicit BasicObject(BasicType type);

  bool IsInit() override;
  int Get(BasicType get_type);
  BasicType GetType();
 private:
  BasicType type_;
  int value_;
  bool is_init_;
};