#pragma once

#include "Object.h"
#include "SimpleObject.h"
#include "Expression/Expression.h"

class ArrayObject : public Object {
 public:
  ArrayObject(SimpleObject object, Expression *length);
  explicit ArrayObject(SimpleObject object);


  Expression *GetLength();

  SimpleObject GetObject();

 private:
  Expression *length_;
  SimpleObject simple_object_;
};