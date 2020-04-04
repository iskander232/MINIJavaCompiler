#include "Main.h"

Main::Main(std::string name, StatementsList *statements_list) : name_(name), statements_list_(statements_list) {
}

void Main::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

std::string Main::GetName() {
  return name_;
}

StatementsList *Main::GetStatementsList() {
  return statements_list_;
}