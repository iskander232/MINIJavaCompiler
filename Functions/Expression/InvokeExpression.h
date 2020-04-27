#include "ExprList.h"

#include <string>

class InvokeExpression : public Expression {
 public:
  InvokeExpression(Expression *expression, std::string name, ExprList *expr_list);

  Expression *GetExpression();
  std::string GetName();
  ExprList *GetExprList();
  void Accept(Visitor *visitor) override;
 private:
  Expression *expression_;
  std::string name_;
  ExprList *expr_list_;
};