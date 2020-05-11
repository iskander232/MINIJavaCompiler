#include "SimpleObject.h"

class IntegerObject : public SimpleObject {
 public:
  explicit IntegerObject(int value);
  std::string GetName() override ;
  int GetValue();

  std::shared_ptr<Object> GetCopy() override;
  bool IsEqual(std::shared_ptr<Object> other) override;
  int GetSize() override ;
  int value_;
};