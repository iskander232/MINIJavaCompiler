#include "Linerisation.h"

#include "BaseElements.h"

namespace IRT {

void Linerisation::Visit(ExpStatement *stmt) {
  IrtStorage elements = Accept(stmt->GetExpression());
  tos_value_.statement_ = new ExpStatement(elements.expression_);
}

void Linerisation::Visit(ConstExpression *const_expression) {
  tos_value_.expression_ = new ConstExpression(const_expression->Value());
}

void Linerisation::Visit(JumpConditionalStatement *jump_conditional_statement) {
  auto lhs = Accept(jump_conditional_statement->left_operand_).expression_;
  auto rhs = Accept(jump_conditional_statement->right_operand_).expression_;

  tos_value_.statement_ = new JumpConditionalStatement(
      jump_conditional_statement->operator_type_,
      lhs,
      rhs,
      jump_conditional_statement->label_true_,
      jump_conditional_statement->label_false_
  );
}
void Linerisation::Visit(MoveStatement *move_statement) {
  auto source = Accept(move_statement->source_).expression_;
  auto target = Accept(move_statement->target_).expression_;

  tos_value_.statement_ = new MoveStatement(source, target);
}

void Linerisation::Visit(SeqStatement *seq_statement) {
  auto first = Accept(seq_statement->first_statement_).statement_;
  auto second = Accept(seq_statement->second_statement_).statement_;

  if (dynamic_cast<SeqStatement *>(first)) {
    auto seqf = dynamic_cast<SeqStatement *>(first);
    tos_value_.statement_ = new SeqStatement(
        Accept(seqf->first_statement_).statement_,
        Accept(new SeqStatement(
            Accept(seqf->second_statement_).statement_,
            Accept(second).statement_
        )).statement_
    );
  } else {
    tos_value_.statement_ = new SeqStatement(
        first,
        second
    );
  }
}

void Linerisation::Visit(LabelStatement *label_statement) {
  tos_value_.statement_ = new LabelStatement(label_statement->label_);
}

void Linerisation::Visit(BinopExpression *binop_statement) {
  tos_value_.expression_ = new BinopExpression(
      binop_statement->operator_type_,
      Accept(binop_statement->first_).expression_,
      Accept(binop_statement->second_).expression_
  );
}
void Linerisation::Visit(TempExpression *temp_exression) {
  tos_value_.expression_ = new TempExpression(temp_exression->temporary_);
}

void Linerisation::Visit(MemExpression *mem_expression) {
  tos_value_.expression_ = new MemExpression(
      Accept(mem_expression->expression_).expression_
  );
}

void Linerisation::Visit(JumpStatement *jump_statement) {
  tos_value_.statement_ = new JumpStatement(
      jump_statement->label_
  );
}
void Linerisation::Visit(CallExpression *call_expression) {
  auto func = Accept(call_expression->function_name_).expression_;
  auto args = Accept(call_expression->args_).expression_list_;

  tos_value_.expression_ = new CallExpression(func, args);
}
void Linerisation::Visit(ExpressionList *expression_list) {
  auto expression_list_ = new ExpressionList();

  for (auto expression: expression_list->expressions_) {
    expression_list_->Add(Accept(expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;

}

void Linerisation::Visit(NameExpression *name_expression) {
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}

void Linerisation::Visit(EseqExpression *eseq_expression) {
  auto stmt = Accept(eseq_expression->statement_).statement_;
  auto expr = Accept(eseq_expression->expression_).expression_;

  tos_value_.expression_ = new EseqExpression(stmt, expr);
}

Statement *Linerisation::GetTree() {
  return tos_value_.statement_;
}

} // IRT namespace