#pragma once

#include "Object.h"
#include <Grammar/Formals.h>
#include <Statements/StatementsList.h>

#include <vector>
#include <string>

using argument = std::pair<std::string, std::shared_ptr<Object>>;

class FunctionObject : public Object {
 public:
  FunctionObject(std::shared_ptr<Object> ret_type, Formals *formals, StatementsList* statements_list);

  std::shared_ptr<Object> GetCopy() override;
  bool IsEqual(std::shared_ptr<Object> other) override;

  std::vector<std::shared_ptr<Object>> arguments_;
  StatementsList* statements_list_;
  Formals* formals_;
  std::vector<std::string> argument_names_;
  std::shared_ptr<Object> ret_type_;
};