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
  virtual void Visit(Class *a_class) = 0;
  virtual void Visit(ClassesList *classes_list) = 0;
  virtual void Visit(DeclarationList *declaration_list) = 0;
  virtual void Visit(MethodDecl *method_decl) = 0;
  virtual void Visit(VarDecl *var_decl) = 0;
  virtual void Visit(BinaryCallExpression *binary_call_expression) = 0;
  virtual void Visit(ArrayGetExpression *array_get_expression) = 0;
  virtual void Visit(ArrayRvalueExpression *array_rvalue_expression) = 0;
  virtual void Visit(BoolExpression *bool_expression) = 0;
  virtual void Visit(ExprList *expr_list) = 0;
  virtual void Visit(GetLengthExpression *get_length_expression) = 0;
  virtual void Visit(IdentCreateExpression *ident_create_expression) = 0;
  virtual void Visit(IdentExpression *ident_expression) = 0;
  virtual void Visit(InvokeExpression *invoke_expression) = 0;
  virtual void Visit(NotExpression *not_expression) = 0;
  virtual void Visit(NumberExpression *number_expression) = 0;
  virtual void Visit(ThisExpression *this_expression) = 0;
  virtual void Visit(UnarMinusExpression *unar_minus_expression) = 0;
  virtual void Visit(Lvalue *lvalue) = 0;
  virtual void Visit(ArrayElementLvalue *array_element_lvalue) = 0;
  virtual void Visit(ArrayLvalue *array_lvalue) = 0;
  virtual void Visit(SimpleLvalue *simple_lvalue) = 0;
  virtual void Visit(Main *main) = 0;
  virtual void Visit(Program *program) = 0;
  virtual void Visit(AssertStatement *assert_statement) = 0;
  virtual void Visit(AssignStatement *assign_statement) = 0;
  virtual void Visit(IfElseStatement *if_else_statement) = 0;
  virtual void Visit(IfStatement *if_statement) = 0;
  virtual void Visit(MethodInvokeStatement* method_invoke_statement) = 0;
  virtual void Visit(OutStatement *out_statement) = 0;
  virtual void Visit(ReturnStatement* return_statement) = 0;
  virtual void Visit(ScopeDeclStatement *scope_decl_statement) = 0;
  virtual void Visit(StatementsList *statements_list) = 0;
  virtual void Visit(WhileStatement *while_statement) = 0;
  virtual void Visit(Formals* formals) = 0;
};