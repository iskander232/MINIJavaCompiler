#pragma once

#include <string>
#include <unordered_map>
#include <function-mechanism/address/Address.h>
#include <stack>
#include <vector>

#include "../Grammar/Types/IdentObject.h"
#include "../Grammar/Types/Object.h"

namespace IRT {
class FrameTranslator {
 public:
  FrameTranslator(std::string function_name, std::shared_ptr<Object> ret_type, std::shared_ptr<IdentObject> a_class);
  void SetupScope();
  void TearDownScope();

  void AddVariable( std::string name, int offset, std::shared_ptr<Object> var_type);
  void AddLocalVariable(std::string name, int offset, std::shared_ptr<Object> var_type);
  void AddReturnAddress(int offset, std::shared_ptr<Object> var_type);

  void AddArgumentAddress(std::string name, int offset, std::shared_ptr<Object> var_type);

  Address *FramePointer();
  Address *GetAddress(std::string name);
  Address *GetReturnValueAddress();

  std::shared_ptr<Object> GetType(std::string name);



 private:


  std::string return_address_ = "::return";
  std::string frame_pointer_address_ = "::fp";
  std::string return_value_address_ = "::return_value";

  std::unordered_map<std::string, std::stack<Address *> > addresses_;
  std::unordered_map<std::string, std::stack<std::shared_ptr<Object>>> types_;
  std::stack<std::string> symbols_;
  std::string function_name_;

  std::shared_ptr<IdentObject> this_;
  int GetOffset(size_t var_size);
  int max_offset_ = 0;
};

}

