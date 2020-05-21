# pragma once

#include <vector>
#include "../generators/Label.h"
#include "../nodes/statements/Statement.h"
#include "../visitors/PrintVisitor.h"

namespace IRT {
class BaseBlock {
 public:
  explicit BaseBlock(Label label);
  BaseBlock();
  Label GetLabel();
  void AddStatement(Statement *statement);
  std::vector<Statement *> GetStatements();
  Statement *GetJumpStatement();
  bool IsEnded();
 private:
  bool is_ended_;
  Label start_label_;
  std::vector<Statement *> statements_;
};

}