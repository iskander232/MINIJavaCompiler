#pragma once

#include "../generators/Label.h"
#include "../nodes/expressions/Expression.h"
#include "../nodes/statements/Statement.h"
#include "../../Grammar/Types/UninitObject.h"

namespace IRT {
class SubtreeWrapper {
 public:
  SubtreeWrapper() : type_(std::make_shared<UninitObject>(UninitObject())) {}
  virtual ~SubtreeWrapper() = default;
  virtual Expression *ToExpression() = 0;
  virtual Statement *ToStatement() = 0;
  virtual Statement *ToConditional(Label true_label, Label false_label) = 0;

  void SetObject(std::shared_ptr<Object> object) {
    type_ = object;
  }

  std::shared_ptr<Object> GetObject() {
    return type_;
  }

 private:
  std::shared_ptr<Object> type_;
};

}