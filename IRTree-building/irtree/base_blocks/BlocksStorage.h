#pragma once

#include <map>
#include <string>

#include "BaseBlock.h"
#include "Trace.h"

namespace IRT {
class BlockStorage {
 public:
  explicit BlockStorage(Label label);
  explicit BlockStorage(Statement *statement);
  void AddStatement(Statement *statement);
  BaseBlock GetBlock(std::string name);
  void Finish();
  std::vector<Trace> BuildTraces(std::string start);
  BaseBlock last_block_;
  std::map<std::string, BaseBlock> blocks_;
};
}