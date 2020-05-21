#pragma once

#include <vector>
#include "BaseBlock.h"
namespace IRT {
class Trace {
 public:
  void AddBlock(BaseBlock block);
  std::vector<BaseBlock> GetBlocks();
  std::vector<BaseBlock> blocks_;
  std::string ToString();
};
}