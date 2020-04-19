#pragma once

#include "forward_declaration.h"

class Visitor {
 public:
  virtual void Visit(AndOperator *and_operator) = 0;
  virtual void Visit(DivOperator *div_operator) = 0;
  virtual void Visit(EqualOperator *equal_operator) = 0;
  virtual void Visit(LessOperator *less_operator) = 0;
  virtual void Visit(MinusOperator *minus_operator) = 0;
  virtual void Visit(MoreOperator *more_operator) = 0;
  virtual void Visit(MulOperator *mul_opearator) = 0;
  virtual void Visit(OrOperator *or_operator) = 0;
  virtual void Visit(PlusOperator *plus_operator) = 0;
  virtual void Visit(ProcOperator *proc_operator) = 0;
  virtual void Visit(ClassesList *classes_list) = 0;
  virtual void Visit(VarDecl *var_decl) = 0;
  virtual void Visit(BinaryCallExpression *binary_call_expression) = 0;
  virtual void Visit(BoolExpression *bool_expression) = 0;
  virtual void Visit(IdentExpression *ident_expression) = 0;
  virtual void Visit(NotExpression *not_expression) = 0;
  virtual void Visit(NumberExpression *number_expression) = 0;
  virtual void Visit(UnarMinusExpression *unar_minus_expression) = 0;
  virtual void Visit(Lvalue *lvalue) = 0;
  virtual void Visit(Main *main) = 0;
  virtual void Visit(Program *program) = 0;
  virtual void Visit(AssertStatement *assert_statement) = 0;
  virtual void Visit(AssignStatement *assign_statement) = 0;
  virtual void Visit(OutStatement *out_statement) = 0;
  virtual void Visit(StatementsList *statements_list) = 0;
};