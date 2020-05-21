#include "BaseBlock.h"

#include "../nodes/statements/JumpConditionalStatement.h"
#include "../nodes/statements/JumpStatement.h"
#include "../nodes/statements/LabelStatement.h"

namespace IRT {
BaseBlock::BaseBlock(Label label) : start_label_(label), is_ended_(false), statements_{new LabelStatement(label)} {}

BaseBlock::BaseBlock()
    : start_label_(Label("untitled")), is_ended_(false), statements_{new LabelStatement(start_label_)} {}

void BaseBlock::AddStatement(Statement *statement) {
  if (is_ended_) {
    throw std::runtime_error("Try to add statement to ended block");
  }

  if (dynamic_cast<JumpConditionalStatement *>(statement) || dynamic_cast<JumpStatement *>(statement)) {
    is_ended_ = true;
  }

  statements_.push_back(statement);
}

std::vector<Statement *> BaseBlock::GetStatements() {
  return statements_;
}

Statement *BaseBlock::GetJumpStatement() {
  if (!is_ended_) {
    throw std::runtime_error("Try to get jump statement from block without jump statement");
  }

  return statements_.back();
}

bool BaseBlock::IsEnded() {
  return is_ended_;
}

Label BaseBlock::GetLabel() {
  return start_label_;
}
}