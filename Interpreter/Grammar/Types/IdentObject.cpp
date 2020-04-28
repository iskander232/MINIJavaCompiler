#include "IdentObject.h"

#include <stdexcept>

IdentObject::IdentObject(std::string name) : name_(name) {}

std::shared_ptr<Object> IdentObject::GetCopy() {
  auto copy = IdentObject(name_);
  for (auto value : values_) {
    copy.values_[value.first] = value.second->GetCopy();
  }
  for (auto func : functions_) {
    copy.functions_.push_back(std::dynamic_pointer_cast<FunctionObject>(func->GetCopy()));
  }
  return std::dynamic_pointer_cast<Object>(std::make_shared<IdentObject>(copy));
}

bool IdentObject::IsEqual(std::shared_ptr<Object> other) {
  auto other_ident = std::dynamic_pointer_cast<IdentObject>(other);
  return other_ident != nullptr && name_ == other_ident->name_;
}

std::shared_ptr<Object> IdentObject::GetValue(std::string value_name) {
  if (values_.find(value_name) == values_.end()) {
    throw std::runtime_error("Can't find value " + value_name + " in class " + name_);
  }
  return values_[value_name];
}

void IdentObject::SetValue(std::string value_name, std::shared_ptr<Object> new_object) {
  if (values_.find(value_name) == values_.end()) {
    values_[value_name] = new_object;
  } else {
    auto last_value = values_[value_name];
    if (last_value->IsEqual(new_object)) {
      values_[value_name] = new_object;
    } else {
      throw std::runtime_error("Try to set value with other type in class " + name_);
    }
  }
}

bool IdentObject::Has(std::string name) {
  return values_.find(name) != values_.end();
}