#include "SimpleObject.h"

class IntegerObject : public SimpleObject {
 public:
  explicit IntegerObject(int value);
  int GetValue();
 private:
  int value_;
};