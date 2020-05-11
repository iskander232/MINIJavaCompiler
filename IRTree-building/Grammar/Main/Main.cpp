#include "Main.h"
#include <Location/Location.h>

Main::Main(std::string name, StatementsList *statements_list) : name_(name), statements_list_(statements_list) {
}

void Main::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
  Location::GetInstance().SetPrevLoc();
}

std::string Main::GetName() {
  return name_;
}

StatementsList *Main::GetStatementsList() {
  return statements_list_;
}