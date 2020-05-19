

#include "MinusESEQ.h"

#include "BaseElements.h"

namespace IRT {

void MinusESEQ::Visit(ExpStatement *stmt) {
  IrtStorage elements = Accept(stmt->GetExpression());
  tos_value_.statement_ = new ExpStatement(elements.expression_);
}

void MinusESEQ::Visit(ConstExpression *const_expression) {
  tos_value_.expression_ = new ConstExpression(const_expression->Value());
}

void MinusESEQ::Visit(JumpConditionalStatement *jump_conditional_statement) {
  auto lhs = Accept(jump_conditional_statement->left_operand_).expression_;
  auto rhs = Accept(jump_conditional_statement->right_operand_).expression_;

  if (!dynamic_cast<EseqExpression *>(lhs)) {
    tos_value_.statement_ = new JumpConditionalStatement(
        jump_conditional_statement->operator_type_,
        lhs,
        rhs,
        jump_conditional_statement->label_true_,
        jump_conditional_statement->label_false_
    );
  } else {
    auto eseqlhs = dynamic_cast<EseqExpression *>(lhs);
    tos_value_.statement_ = new SeqStatement(
        eseqlhs->statement_,
        new JumpConditionalStatement(
            jump_conditional_statement->operator_type_,
            eseqlhs->expression_,
            rhs,
            jump_conditional_statement->label_true_,
            jump_conditional_statement->label_false_
        )
    );
  }

  jump_conditional_statement = dynamic_cast<JumpConditionalStatement *>(tos_value_.statement_);

  lhs = Accept(jump_conditional_statement->left_operand_).expression_;
  rhs = Accept(jump_conditional_statement->right_operand_).expression_;

  if (!dynamic_cast<EseqExpression *>(rhs)) {
    tos_value_.statement_ = new JumpConditionalStatement(
        jump_conditional_statement->operator_type_,
        lhs,
        rhs,
        jump_conditional_statement->label_true_,
        jump_conditional_statement->label_false_
    );
  } else {
    auto eseqrhs = dynamic_cast<EseqExpression *>(rhs);
    Temporary temp = Temporary();
    tos_value_.statement_ = new SeqStatement(
        new MoveStatement(new TempExpression(temp), eseqrhs->expression_),
        new SeqStatement(
            eseqrhs->statement_,
            new JumpConditionalStatement(jump_conditional_statement->operator_type_,
                                         new TempExpression(temp),
                                         eseqrhs->expression_,
                                         jump_conditional_statement->label_true_,
                                         jump_conditional_statement->label_false_
            )
        )
    );
  }
}

void MinusESEQ::Visit(MoveStatement *move_statement) {
  auto source = Accept(move_statement->source_).expression_;
  auto target = Accept(move_statement->target_).expression_;

  tos_value_.statement_ = new MoveStatement(source, target);
}

void MinusESEQ::Visit(SeqStatement *seq_statement) {
  auto first = Accept(seq_statement->first_statement_).statement_;
  auto second = Accept(seq_statement->second_statement_).statement_;

  tos_value_.statement_ = new SeqStatement(
      first,
      second
  );
}

void MinusESEQ::Visit(LabelStatement *label_statement) {
  tos_value_.statement_ = new LabelStatement(label_statement->label_);
}

void MinusESEQ::Visit(BinopExpression *binop_statement) {
  auto first = Accept(binop_statement->first_).expression_;
  auto second = Accept(binop_statement->second_).expression_;

  auto eseqfirst = dynamic_cast<EseqExpression *>(first);

  if (eseqfirst) {
    tos_value_.expression_ = new EseqExpression(
        eseqfirst->statement_,
        new BinopExpression(
            binop_statement->operator_type_,
            eseqfirst->expression_,
            second
        )
    );
  } else {
    if (dynamic_cast<EseqExpression *>(second)) {
      auto eseqsecond = dynamic_cast<EseqExpression *>(second);
      Temporary temp = Temporary();

      tos_value_.expression_ = new EseqExpression(
          new MoveStatement(
              new TempExpression(temp),
              Accept(binop_statement->first_).expression_),
          new EseqExpression(
              eseqsecond->statement_,
              new BinopExpression(
                  binop_statement->operator_type_,
                  new TempExpression(temp),
                  eseqsecond->expression_
              )
          )
      );
    } else {
      tos_value_.expression_ = new BinopExpression(
          binop_statement->operator_type_,
          first,
          second
      );
    }
  }
}

void MinusESEQ::Visit(TempExpression *temp_exression) {
  tos_value_.expression_ = new TempExpression(temp_exression->temporary_);
}

void MinusESEQ::Visit(MemExpression *mem_expression) {
  auto exp = Accept(mem_expression->expression_).expression_;
  auto eseqexp = dynamic_cast<EseqExpression *>(exp);
  if (eseqexp) {
    tos_value_.expression_ = new EseqExpression(
        eseqexp->statement_,
        new MemExpression(eseqexp->expression_)
    );
  } else {
    tos_value_.expression_ = new MemExpression(exp);
  }
}

void MinusESEQ::Visit(JumpStatement *jump_statement) {
  tos_value_.statement_ = new JumpStatement(
      jump_statement->label_
  );
}
void MinusESEQ::Visit(CallExpression *call_expression) {
  auto func = Accept(call_expression->function_name_).expression_;
  auto args = Accept(call_expression->args_).expression_list_;

  tos_value_.expression_ = new EseqExpression(
      tos_value_.statement_,
      new CallExpression(func, args)
  );
}

void MinusESEQ::Visit(ExpressionList *expression_list) {
  auto expression_list_ = new ExpressionList();
  std::vector<Statement *> prefix_statements;
  for (int i = 0; i < expression_list->expressions_.size(); ++i) {
    Temporary temp = Temporary();
    if (dynamic_cast<EseqExpression *>(expression_list->expressions_[i])) {
      auto eseq = dynamic_cast<EseqExpression *>(expression_list->expressions_[i]);
      prefix_statements.push_back(
          new SeqStatement(
              Accept(eseq->statement_).statement_,
              new MoveStatement(
                  new TempExpression(temp),
                  Accept(eseq->expression_).expression_)));
    } else {
      prefix_statements.push_back(
          new MoveStatement(
              new TempExpression(temp),
              Accept(expression_list->expressions_[i]).expression_
          ));
    }
    expression_list_->Add(new TempExpression(temp));
  }

  Statement *prefix = prefix_statements[0];
  for (int i = 1; i < prefix_statements.size(); ++i) {
    prefix = new SeqStatement(
        prefix,
        prefix_statements[i]
    );
  }

  tos_value_.statement_ = prefix;
  tos_value_.expression_list_ = expression_list_;
}

void MinusESEQ::Visit(NameExpression *name_expression) {
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}

void MinusESEQ::Visit(EseqExpression *eseq_expression) {
  auto stmt = Accept(eseq_expression->statement_).statement_;
  auto expr = Accept(eseq_expression->expression_).expression_;

  auto eseq = dynamic_cast<EseqExpression *>(expr);
  if (eseq) {
    tos_value_.expression_ = new EseqExpression(
        new SeqStatement(stmt, eseq->statement_),
        eseq->expression_
    );
  } else {
    tos_value_.expression_ = new EseqExpression(stmt, expr);
  }
}

Statement *MinusESEQ::GetTree() {
  return tos_value_.statement_;
}

} //IRT namespace
