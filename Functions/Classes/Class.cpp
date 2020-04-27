#include "Class.h"

Class::Class(std::string name, DeclarationList *declaration_list) : name_(name), declaration_list_(declaration_list) {}

std::string Class::GetName() {
  return name_;
}

DeclarationList *Class::GetDeclarations() {
  return declaration_list_;
}

void Class::Accept(Visitor *visitor) {
  visitor->Visit(this);
}