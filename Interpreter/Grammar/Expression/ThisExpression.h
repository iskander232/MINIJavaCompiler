#include "Expression.h"

class ThisExpression: public Expression{
 public:
  void Accept(Visitor* visitor);
};
