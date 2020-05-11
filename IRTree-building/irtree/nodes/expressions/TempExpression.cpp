#include "TempExpression.h"
void IRT::TempExpression::Accept(IRT::Visitor *visitor) {
  visitor->Visit(this);

}
IRT::TempExpression::TempExpression(const IRT::Temporary &temporary): temporary_(temporary) {

}
