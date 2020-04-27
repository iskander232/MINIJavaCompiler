#include "MethodDecl.h"

MethodDecl::MethodDecl(std::shared_ptr<Object> type,
                       std::string name,
                       Formals *formals,
                       StatementsList *statements_list) :

    type_(type),
    name_(name),
    formals_(formals),
    statements_list_(statements_list){}

std::shared_ptr<Object> MethodDecl::GetType() {
  return type_;
}

std::string MethodDecl::GetName() {
  return name_;
}

Formals * MethodDecl::GetFormals() {
  return formals_;
}

StatementsList * MethodDecl::GetStatements() {
  return statements_list_;
}

void MethodDecl::Accept(Visitor *visitor) {
  visitor->Visit(this);
}