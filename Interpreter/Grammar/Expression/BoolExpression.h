#pragma once

#include "Expression.h"

#include <memory>
class BoolExpression : public Expression {
 public:
  explicit BoolExpression(bool value);
  std::shared_ptr<Object> GetValue();
  void Accept(Visitor *visitor) override;
//  int Eval() override ;
 private:
  std::shared_ptr<BoolObject> value_;
};