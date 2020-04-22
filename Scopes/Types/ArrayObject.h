#pragma once

#include "Object.h"
#include "SimpleObject.h"
#include "Expression/Expression.h"

#include <memory>
#include <vector>

class ArrayObject : public Object {
 public:

  explicit ArrayObject(std::shared_ptr<Object> object);
  ArrayObject(std::shared_ptr<Object> object, int length);

  size_t GetLength();
  std::shared_ptr<Object> GetIth(int i);
  void SetIth(int i, std::shared_ptr<Object> object);
  std::shared_ptr<Object> GetObject();

  bool IsEqual(std::shared_ptr<Object> other) override;

 private:
  size_t length_;
  std::shared_ptr<SimpleObject> object_;
  std::vector<std::shared_ptr<Object>> elements_;
};