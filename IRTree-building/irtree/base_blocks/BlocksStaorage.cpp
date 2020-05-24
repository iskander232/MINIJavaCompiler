#include "BlocksStorage.h"

#include "../nodes/statements/JumpStatement.h"
#include "../nodes/statements/JumpConditionalStatement.h"
#include "../nodes/statements/LabelStatement.h"
#include "../nodes/statements/SeqStatement.h"

namespace IRT {

BlockStorage::BlockStorage(Label label) : last_block_(label) {}

BlockStorage::BlockStorage(Statement *statement) {
  if (dynamic_cast<LabelStatement *>(statement)) {
    last_block_ = BaseBlock(dynamic_cast<LabelStatement *>(statement)->label_);
    return;
  }

  auto cur_seq = dynamic_cast<SeqStatement *>(statement);
  last_block_ = BaseBlock(dynamic_cast<LabelStatement *>(cur_seq->first_statement_)->label_);

  auto cur = cur_seq->second_statement_;
  cur_seq = dynamic_cast<SeqStatement *>(cur_seq->second_statement_);
  while (cur_seq) {
    AddStatement(cur_seq->first_statement_);

    cur = cur_seq->second_statement_;
    cur_seq = dynamic_cast<SeqStatement *>(cur_seq->second_statement_);
  }

  if (cur) {
    AddStatement(cur);
  }
}

void BlockStorage::AddStatement(Statement *statement) {
  if (dynamic_cast<JumpStatement *>(statement) || dynamic_cast<JumpConditionalStatement *>(statement)) {
    last_block_.AddStatement(statement);
    blocks_[last_block_.GetLabel().ToString()] = last_block_;
    return;
  }

  if (dynamic_cast<LabelStatement *>(statement)) {
    auto label_statement = dynamic_cast<LabelStatement *>(statement);

    if (!last_block_.IsEnded()) {
      last_block_.AddStatement(new JumpStatement(label_statement->label_));
      blocks_[last_block_.GetLabel().ToString()] = last_block_;
    }

    last_block_ = BaseBlock(label_statement->label_);
    return;
  }

  last_block_.AddStatement(statement);
}

BaseBlock BlockStorage::GetBlock(std::string name) {
  return blocks_[name];
}

void BlockStorage::Finish() {
  AddStatement(new JumpStatement(Label("::done")));
  for (auto f: blocks_) {
    used_[f.first] = 5;
  }
}

std::vector<Trace> BlockStorage::BuildTraces(std::string start) {
  if (start == "::done") {
    return {};
  }

  auto last_trace = Trace();
  std::vector<Trace> result;
  while (blocks_.find(start) != blocks_.end() && start != "::done") {
    auto block = blocks_[start];

    last_trace.AddBlock(block);

    if (used_[start] == 0) {
      break;
    } else {
      used_[start]--;
    }
    auto jump_stmt = dynamic_cast<JumpStatement *>(block.GetJumpStatement());
    if (jump_stmt) {
      start = jump_stmt->label_.ToString();
    } else {
      auto cjump_stmt = dynamic_cast<JumpConditionalStatement *>(block.GetJumpStatement());
      auto traces = BuildTraces(cjump_stmt->label_true_.ToString());
      for (Trace t: traces) {
        result.push_back(t);
      }

      start = cjump_stmt->label_false_.ToString();
    }
  }

  result.push_back(last_trace);

  return result;
}
}