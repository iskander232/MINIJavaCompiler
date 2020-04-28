#include "ExprList.h"
#include <Location/Location.h>

#include <stdexcept>

ExprList::ExprList() {}

ExprList::ExprList(Expression *expression) : exprs_{expression} {}

void ExprList::AddExpr(Expression *expression) {
  exprs_.push_back(expression);
}

size_t ExprList::GetSize() {
  return exprs_.size();
}

Expression*  ExprList::GetIth(int i) {
  if (i < 0 || i >= GetSize()) {
    throw std::runtime_error("Try to get expression with bad index");
  }
  return exprs_[i];

}

void ExprList::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}