#include "FunctionObject.h"

#include <set>
#include <stdexcept>

FunctionObject::FunctionObject(std::shared_ptr<Object> ret_type, Formals *formals, StatementsList *statements_list)
    : ret_type_(ret_type), formals_(formals), statements_list_(statements_list) {
  std::set<std::string> names;
  for (int i = 0; i < formals->GetSize(); ++i) {
    formal f = formals->GetIth(i);
    arguments_.push_back(f.first);
    argument_names_.push_back(f.second);
    if (names.find(argument_names_.back()) != names.end()) {
      throw std::runtime_error("same name in arguments of function");
    }
  }
};

std::shared_ptr<Object> FunctionObject::GetCopy() {
  auto copy = FunctionObject(ret_type_, formals_, statements_list_);
  for (auto argument: arguments_) {
    copy.arguments_.push_back(argument->GetCopy());
  }
  copy.argument_names_ = argument_names_;
  return std::dynamic_pointer_cast<Object>(std::make_shared<FunctionObject>(copy));
}

bool FunctionObject::IsEqual(std::shared_ptr<Object> other) {
  return std::dynamic_pointer_cast<FunctionObject>(other) != nullptr;
}

std::string FunctionObject::GetName() {
  return "function";
}

void FunctionObject::SetName(std::string name) {
  name_ = name;
}

void FunctionObject::SetName(std::string class_name, std::string func_name) {
  name_ = class_name + "_____" + func_name;
}