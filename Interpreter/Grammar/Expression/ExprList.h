#pragma once

#include "BaseElement/BaseElement.h"
#include "Expression.h"

#include <vector>
class ExprList : public BaseElement {
 public:
  ExprList();
  explicit ExprList(Expression *Expr);

  void AddExpr(Expression *Expr);

  size_t GetSize();
  Expression* GetIth(int i);

  void Accept(Visitor *visitor) override ;
 private:
  std::vector<Expression*> exprs_;
};