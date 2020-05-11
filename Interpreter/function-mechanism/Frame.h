#pragma once

#include "../../Interpreter/Grammar/Types/FunctionObject.h"

#include <stack>
#include <memory>
class Frame {
 public:
  explicit Frame(std::shared_ptr<FunctionObject> function);
  void SetParams(const std::vector<std::shared_ptr<Object>> &values);

  size_t AllocVariable(std::shared_ptr<Object> object);

  void DeallocScope();
  void AllocScope();

  std::shared_ptr<Object> Get(int index) const;
  void Set(int index, std::shared_ptr<Object> value);

  void SetParentFrame(Frame *frame);

  std::shared_ptr<Object> GetReturnValue() const;

  void SetParentReturnValue(std::shared_ptr<Object> value);

  bool HasParent();

  bool Returned();

  void SetReturnValue(std::shared_ptr<Object> value);
  void SetReturnType(std::shared_ptr<Object> value);
 private:
  std::stack<int> offsets_;
  std::vector<std::shared_ptr<Object>> params_;
  std::vector<std::shared_ptr<Object>> variables_;

  std::shared_ptr<Object> return_value_;
  bool is_returned = false;


  Frame *parent_frame = nullptr;

};



