#pragma once

#include "Grammar/BaseElement/BaseElement.h"
#include "Grammar/Expression/Expression.h"

#include "Types/Object.h"
#include <memory>
class BinaryOperator : public BaseElement {
 public:
  virtual std::shared_ptr<Object> eval(std::shared_ptr<Object> a, std::shared_ptr<Object> b) const = 0;
  void SetExprs(Expression* f, Expression* s){
    first = f;
    second = s;
  }

  Expression* first;
  Expression* second;
};