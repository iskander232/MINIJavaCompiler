#include "Interpreter.h"

#include "elements.h"

#include <iostream>

void Interpreter::Visit(AndOperator *and_operator) {}

void Interpreter::Visit(DivOperator *div_operator) {}

void Interpreter::Visit(EqualOperator *equal_operator) {}

void Interpreter::Visit(LessOperator *less_operator) {}

void Interpreter::Visit(MinusOperator *minus_operator) {}

void Interpreter::Visit(MoreOperator *more_operator) {}

void Interpreter::Visit(MulOperator *mul_opearator) {}

void Interpreter::Visit(OrOperator *or_operator) {}

void Interpreter::Visit(PlusOperator *plus_operator) {}

void Interpreter::Visit(ProcOperator *proc_operator) {}

void Interpreter::Visit(ClassesList *classes_list) {}

void Interpreter::Visit(VarDecl *var_decl) {
  variables_[var_decl->GetName()] = 0;
}

void Interpreter::Visit(BinaryCallExpression *binary_call_expression) {
  binary_call_expression->GetFirst()->Accept(this);
  int first = GetTosValue();

  binary_call_expression->GetSecond()->Accept(this);
  int second = GetTosValue();

  SetTosValue(binary_call_expression->GetOperator()->eval(first, second));
}

void Interpreter::Visit(BoolExpression *bool_expression) {
  SetTosValue(bool_expression->GetValue());
}

void Interpreter::Visit(IdentExpression *ident_expression) {
  SetTosValue(variables_[ident_expression->GetName()]);
}

void Interpreter::Visit(NotExpression *not_expression) {
  not_expression->GetExpression()->Accept(this);
  SetTosValue(!GetTosValue());
}

void Interpreter::Visit(NumberExpression *number_expression) {
  SetTosValue(number_expression->GetNumber());
}

void Interpreter::Visit(UnarMinusExpression *unar_minus_expression) {
  unar_minus_expression->GetExpression()->Accept(this);
  SetTosValue(-GetTosValue());
}

void Interpreter::Visit(Lvalue *lvalue) {}

void Interpreter::Visit(Main *main) {
  main->GetStatementsList()->Accept(this);
}

void Interpreter::Visit(Program *program) {
  program->GetMain()->Accept(this);
  program->GetClassesList()->Accept(this);
}

void Interpreter::Visit(AssertStatement *assert_statement) {
  assert_statement->GetExpression()->Accept(this);
  if (!GetTosValue()){
    throw std::runtime_error("assert is false");
  }
}

void Interpreter::Visit(AssignStatement *assign_statement) {
  assign_statement->GetExpression()->Accept(this);

  variables_[assign_statement->GetLvalue()->GetName()] = GetTosValue();
}

void Interpreter::Visit(OutStatement *out_statement) {
  out_statement->GetExpression()->Accept(this);
  std::cout << GetTosValue() << std::endl;
}

void Interpreter::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i){
    statements_list->GetIth(i)->Accept(this);
  }
}

int Interpreter::GetTosValue() {
  return tos_value_;
}

void Interpreter::SetTosValue(int value) {
  tos_value_ = value;
}

void Interpreter::GetResult(Program *program) {
  Visit(program);
}
