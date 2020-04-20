#include "Interpreter.h"

#include "elements.h"

#include <iostream>
#include <stdexcept>

Interpreter::Interpreter(ScopeLayer *root) : current_layer_(root), tos_value_(BasicType::Void) {
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
  SetTosValue(*current_layer_->Get(Symbol(ident_expression->GetName())));
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
  current_layer_ = current_layer_->GetChild(offset_.top());
  offset_.push(0);
  main->GetStatementsList()->Accept(this);

  current_layer_ = current_layer_->GetParent();
  offset_.pop();

  size_t index = offset_.top();
  offset_.pop();
  offset_.push(index + 1);
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
    auto last_value = current_layer_->Get(assign_statement->GetLvalue()->GetName());
    if (new_value.GetType() != last_value->GetType()) {
      throw std::runtime_error("different types");
    }
  }
  current_layer_->Put(assign_statement->GetLvalue()->GetName(), std::make_shared<BasicObject>(new_value));
}

void Interpreter::Visit(IfElseStatement *if_else_statement) {
  StatementsList *statements_list;
  int ind;
  if_else_statement->GetExpression()->Accept(this);
  if (GetTosValue().Get(BasicType::Bool)) {
    statements_list = if_else_statement->GetIfStatements();
    ind = 0;
  } else {
    statements_list = if_else_statement->GetElseStatements();
    ind = 1;
  }
  current_layer_ = current_layer_->GetChild(offset_.top())->GetChild(ind);
  offset_.push(0);
  statements_list->Accept(this);
  offset_.pop();
  current_layer_ = current_layer_->GetParent()->GetParent();
  size_t index = offset_.top();
  offset_.pop();
  offset_.push(index + 1);
}

void Interpreter::Visit(IfStatement *if_statement) {
  if_statement->GetExpression()->Accept(this);
  if (GetTosValue().Get(BasicType::Bool)) {
    current_layer_ = current_layer_->GetChild(offset_.top());
    offset_.push(0);

    if_statement->GetStatements()->Accept(this);
    offset_.pop();
    size_t index = offset_.top();
    offset_.pop();
    offset_.push(index + 1);
  }
}

void Interpreter::Visit(OutStatement *out_statement) {
  out_statement->GetExpression()->Accept(this);
  std::cout << GetTosValue().Get(BasicType::Integer) << std::endl;
}

void Interpreter::Visit(ScopeDeclStatement *scope_decl_statement) {
  current_layer_ = current_layer_->GetChild(offset_.top());
  offset_.push(0);
  scope_decl_statement->GetStatementsList()->Accept(this);
  offset_.pop();
  size_t index = offset_.top();
  offset_.pop();
  offset_.push(index + 1);
}

void Interpreter::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
}

void Interpreter::Visit(WhileStatement *while_statement) {
  int index = offset_.top();
  while (1) {
    while_statement->GetExpression()->Accept(this);
    if (!GetTosValue().Get(BasicType::Bool)) break;
    current_layer_ = current_layer_->GetChild(offset_.top());
    offset_.push(0);
    while_statement->GetStatementsList()->Accept(this);
    offset_.pop();
    current_layer_ = current_layer_->GetParent();
  }
  offset_.pop();
  offset_.push(index + 1);
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
