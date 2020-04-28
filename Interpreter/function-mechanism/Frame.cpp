#include "Frame.h"

Frame::Frame(std::shared_ptr<FunctionObject> function){
  params_.resize(function->arguments_.size());

  for (int i = 0; i < function->arguments_.size(); ++i) {
    params_[i] = function->arguments_[i];
  }
  return_value_ = function->ret_type_;

  AllocScope();
}

void Frame::SetParams(const std::vector<std::shared_ptr<Object>> &values) {
  if (params_.size() != values.size()) {
    throw std::runtime_error("Mismatched number of arguments");
  }
  for (int i = 0; i < params_.size(); ++i) {
    if (!params_[i]->IsEqual(values[i])) {
      throw std::runtime_error("Try to set argument with other type");
    }
    params_[i] = values[i];
  }
}

size_t Frame::AllocVariable(std::shared_ptr<Object> object) {
  size_t index = variables_.size();
  variables_.push_back(object);

  return index;
}

void Frame::DeallocScope() {
  size_t new_size = offsets_.top();
  offsets_.pop();

  variables_.resize(new_size);
}

void Frame::AllocScope() {
  offsets_.push(variables_.size());
}

std::shared_ptr<Object> Frame::Get(int index) const {
  if (index >= 0) {
    return variables_.at(index);
  } else {
    return params_.at(-index - 1);
  }
}

void Frame::Set(int index, std::shared_ptr<Object> value) {
  if (index >= 0) {
    if (variables_.at(index)->IsEqual(value)) {
      variables_.at(index) = value;
      return;
    }
  } else {
    if (params_.at(-index - 1)->IsEqual(value)) {
      params_.at(-index - 1) = value;
      return;
    }
  }
  throw std::runtime_error("Try to set other type value");
}

void Frame::SetReturnValue(std::shared_ptr<Object> value) {
  if (!return_value_->IsEqual(value)) {
    throw std::runtime_error("Try set bad return value");
  }
  is_returned = true;
  return_value_ = value;
}

void Frame::SetReturnType(std::shared_ptr<Object> value) {
  return_value_ = value;
}

void Frame::SetParentFrame(Frame *frame) {
  parent_frame = frame;

}

void Frame::SetParentReturnValue(std::shared_ptr<Object> value) {
  if (HasParent()) {
    parent_frame->SetReturnValue(value);
  } else {
    throw std::runtime_error("can't set parent return value: parent isn't exist");
  }
}

bool Frame::HasParent() {
  return parent_frame != nullptr;
}

bool Frame::Returned() {
  return is_returned;
}

std::shared_ptr<Object> Frame::GetReturnValue() const {
  return return_value_;
}
