#pragma once

#include "SimpleObject.h"
#include <Types/FunctionObject.h>

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

class IdentObject : public SimpleObject {
 public:
  explicit IdentObject(std::string name);
  std::string GetName() override ;

  std::shared_ptr<Object> GetCopy() override;
  bool IsEqual(std::shared_ptr<Object> other) override;

  int GetSize() override;
  int GetMaxSize();

  std::shared_ptr<Object> GetValue(std::string value_name);

  void SetValue(std::string value_name, std::shared_ptr<Object> new_object);
  bool Has(std::string name);

  std::unordered_map<std::string, std::shared_ptr<Object>> values_;
  std::vector<std::string> values_names_;
  std::vector<std::shared_ptr<Object>> values_values_;
  std::vector<std::shared_ptr<FunctionObject>> functions_;
  std::string name_;
};