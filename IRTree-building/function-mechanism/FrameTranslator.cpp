#include <function-mechanism/address/AddressInRegister.h>
#include <function-mechanism/address/AddressInFrame.h>
#include "FrameTranslator.h"

#include <../Grammar/Types/UninitObject.h>

namespace IRT {
FrameTranslator::FrameTranslator(
    std::string function_name, std::shared_ptr<Object> ret_type, std::shared_ptr<IdentObject> a_class)
    : function_name_(function_name), this_(a_class) {

  addresses_[frame_pointer_address_].push(new AddressInRegister(
      Temporary(frame_pointer_address_)
  ));

  types_[frame_pointer_address_].push(std::make_shared<UninitObject>(UninitObject()));

  types_[return_address_].push(ret_type);

  addresses_[return_value_address_].push(new AddressInRegister(
      Temporary(return_value_address_)
  ));

  AddVariable("::this", 0, this_);
  for (int i = 0; i < this_->values_values_.size(); ++i) {
    AddVariable(
        this_->values_names_[i], this_->GetMaxSize(), this_->values_values_[i]);
  }
}
void FrameTranslator::SetupScope() {
  symbols_.push("{");
}

void FrameTranslator::TearDownScope() {
  while (symbols_.top() != "{") {
    std::string symbol = symbols_.top();
    addresses_[symbol].pop();
    types_[symbol].pop();
    if (addresses_[symbol].empty()) {
      addresses_.erase(symbol);
      types_.erase(symbol);
    }
    symbols_.pop();
  }
  symbols_.pop();
}

void FrameTranslator::AddLocalVariable(std::string name, int offset, std::shared_ptr<Object> var_type) {
  AddVariable(name, offset, var_type);
}

Address *FrameTranslator::FramePointer() {
  return addresses_[frame_pointer_address_].top();
}

int FrameTranslator::GetOffset(size_t var_size) {
  int tmp = max_offset_;
  max_offset_ += var_size;
  return tmp;
}
void FrameTranslator::AddArgumentAddress(std::string name, int offset, std::shared_ptr<Object> var_type) {
  AddVariable(name, offset, var_type);
}

void FrameTranslator::AddVariable(std::string name, int offset, std::shared_ptr<Object> var_type) {
  symbols_.push(name);

  if (addresses_.find(name) == addresses_.end()) {
    addresses_[name];
  }
  addresses_[name].push(
      new AddressInFrame(FramePointer(), GetOffset(offset))
  );
  types_[name].push(var_type);
}
Address *FrameTranslator::GetAddress(std::string name) {
  return addresses_[name].top();
}

std::shared_ptr<Object> FrameTranslator::GetType(std::string name) {
  return types_[name].top();
}

void FrameTranslator::AddReturnAddress(int offset, std::shared_ptr<Object> var_type) {
  AddVariable(return_address_, offset, var_type);
}

Address *FrameTranslator::GetReturnValueAddress() {
  return GetAddress(return_value_address_);
}

}
