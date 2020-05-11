#include "Expression.h"

#include <string>

class IdentCreateExpression : public Expression {
 public:
  IdentCreateExpression(std::string name);

  std::string GetName();

  void Accept(Visitor *visitor) override;
 private:
  std::string name_;
};
