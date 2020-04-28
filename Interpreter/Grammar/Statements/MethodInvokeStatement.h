#pragma once

#include "Statement.h"
#include "Expression/ExprList.h"

#include <string>

class MethodInvokeStatement : public Statement {
 public:
  MethodInvokeStatement(Expression *expr, std::string name, ExprList* exprList);

  Expression *GetExpr();
  std::string GetName();
  ExprList *GetExprList();

  void Accept(Visitor *visitor) override;
 private:
  Expression *expression_;
  std::string name_;
  ExprList *expr_list_;
};