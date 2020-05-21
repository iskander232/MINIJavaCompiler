#include "Trace.h"

#include <ostream>
namespace IRT {

void Trace::AddBlock(BaseBlock block) {
  blocks_.push_back(block);
}

std::vector<BaseBlock> Trace::GetBlocks() {
  return blocks_;
}

std::string Trace::ToString() {
  std::string res = "";
  for (auto block : blocks_) {
    res.append(block.GetLabel().ToString()).append("->");
  }
  return res.substr(0, res.size() - 2);
}
}