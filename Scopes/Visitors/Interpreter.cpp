#include "Interpreter.h"

#include "elements.h"

#include <iostream>
#include <stdexcept>

Interpreter::Interpreter(ScopeLayerTree *tree) : tree_(tree), tos_value_(BasicType::Void) {
  offset_.push(0);
}

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

void Interpreter::Visit(VarDecl *var_decl) {}

void Interpreter::Visit(BinaryCallExpression *binary_call_expression) {
  binary_call_expression->GetFirst()->Accept(this);
  BasicObject first = GetTosValue();

  binary_call_expression->GetSecond()->Accept(this);
  BasicObject second = GetTosValue();

  SetTosValue(binary_call_expression->GetOperator()->eval(first, second));

}

void Interpreter::Visit(BoolExpression *bool_expression) {
  SetTosValue(*bool_expression->GetValue());
}

void Interpreter::Visit(IdentExpression *ident_expression) {
  SetTosValue(*tree_->GetCurrentLayer()->Get(Symbol(ident_expression->GetName())));
}

void Interpreter::Visit(NotExpression *not_expression) {
  not_expression->GetExpression()->Accept(this);
  SetTosValue(
      BasicObject(BasicType::Bool,
                  !GetTosValue().Get(BasicType::Bool))
  );
}

void Interpreter::Visit(NumberExpression *number_expression) {
  SetTosValue(
      BasicObject(BasicType::Integer,
                  number_expression->GetNumber()->Get(BasicType::Integer))
  );
}

void Interpreter::Visit(UnarMinusExpression *unar_minus_expression) {
  unar_minus_expression->GetExpression()->Accept(this);
  SetTosValue(
      BasicObject(BasicType::Integer,
                  -GetTosValue().Get(BasicType::Integer))
  );
}

void Interpreter::Visit(Lvalue *lvalue) {}

void Interpreter::Visit(Main *main) {
  tree_->GoDown();
  main->GetStatementsList()->Accept(this);
  tree_->GoUp();
  tree_->GoNext();
}

void Interpreter::Visit(Program *program) {
  program->GetClassesList()->Accept(this);
  program->GetMain()->Accept(this);
}

void Interpreter::Visit(AssertStatement *assert_statement) {
  assert_statement->GetExpression()->Accept(this);
  if (!GetTosValue().Get(BasicType::Bool)) {
    throw std::runtime_error("assert is false");
  }
}

void Interpreter::Visit(AssignStatement *assign_statement) {
  assign_statement->GetExpression()->Accept(this);
  BasicObject new_value = GetTosValue();
  if (assign_statement->GetLvalue()->GetType()->GetType() == BasicType::Void) {
    auto last_value = tree_->GetCurrentLayer()->Get(assign_statement->GetLvalue()->GetName());
    if (new_value.GetType() != last_value->GetType()) {
      throw std::runtime_error("different types");
    }
  }
  tree_->GetCurrentLayer()->Put(assign_statement->GetLvalue()->GetName(), std::make_shared<BasicObject>(new_value));
}

void Interpreter::Visit(IfElseStatement *if_else_statement) {
  StatementsList *statements_list;
  tree_->GoDown();

  if_else_statement->GetExpression()->Accept(this);

  if (GetTosValue().Get(BasicType::Bool)) {
    statements_list = if_else_statement->GetIfStatements();
  } else {
    statements_list = if_else_statement->GetElseStatements();
    tree_->GoNext();
  }

  tree_->GoDown();

  statements_list->Accept(this);

  tree_->GoUp();
  tree_->GoUp();
  tree_->GoNext();
}

void Interpreter::Visit(IfStatement *if_statement) {
  if_statement->GetExpression()->Accept(this);
  if (GetTosValue().Get(BasicType::Bool)) {
    tree_->GoDown();

    if_statement->GetStatements()->Accept(this);
    tree_->GoUp();
    tree_->GoNext();
  }
}

void Interpreter::Visit(OutStatement *out_statement) {
  out_statement->GetExpression()->Accept(this);
  std::cout << GetTosValue().Get(BasicType::Integer) << std::endl;
}

void Interpreter::Visit(ScopeDeclStatement *scope_decl_statement) {
  tree_->GoDown();
  scope_decl_statement->GetStatementsList()->Accept(this);
  tree_->GoUp();
  tree_->GoNext();
}

void Interpreter::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
}

void Interpreter::Visit(WhileStatement *while_statement) {
  while (1) {
    while_statement->GetExpression()->Accept(this);
    if (!GetTosValue().Get(BasicType::Bool)) break;
    tree_->GoDown();
    offset_.push(0);
    while_statement->GetStatementsList()->Accept(this);
    offset_.pop();
    tree_->GoUp();
  }
  tree_->GoNext();
}

BasicObject Interpreter::GetTosValue() {
  return tos_value_;
}

void Interpreter::SetTosValue(BasicObject object) {
  tos_value_ = std::move(object);
}

void Interpreter::GetResult(Program *program) {
  Visit(program);
}
