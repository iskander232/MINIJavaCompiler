#pragma once

#include "Expression.h"
#include "../../../Grammar/Types/Object.h"
namespace IRT {

class ConstExpression : public Expression {
 public:
  explicit ConstExpression(int value);
  ~ConstExpression() final = default;
  int Value() const;

  void Accept(Visitor *visitor) override;
 private:
  int value_;
};

}

