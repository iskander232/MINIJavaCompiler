#pragma once
#include <irtree/generators/Temporary.h>
#include "Address.h"
namespace IRT {

class AddressInRegister : public Address {
 public:
  AddressInRegister(const Temporary& temp);
  Expression *ToExpression() override;
 private:
  Temporary temp_;
};

}

