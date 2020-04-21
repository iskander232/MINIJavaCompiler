#include "Interpreter.h"

#include "elements.h"

#include <iostream>
#include <stdexcept>

Interpreter::Interpreter(ScopeLayerTree *tree)
    : tree_(tree), tos_value_(std::shared_ptr<Object>(new UninitObject())) {
  offset_.push(0);
}

std::shared_ptr<Object> Interpreter::GetTosValue() {
  return tos_value_;
}

void Interpreter::SetTosValue(std::shared_ptr<Object> object) {
  tos_value_ = object;
}

////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////

void Interpreter::Visit(BinaryCallExpression *binary_call_expression) {
  binary_call_expression->GetFirst()->Accept(this);
  auto first = GetTosValue();

  binary_call_expression->GetSecond()->Accept(this);
  auto second = GetTosValue();

  SetTosValue(binary_call_expression->GetOperator()->eval(first, second));

}

void Interpreter::Visit(BoolExpression *bool_expression) {
  SetTosValue(bool_expression->GetValue());
}

void Interpreter::Visit(IdentExpression *ident_expression) {
  SetTosValue(tree_->GetCurrentLayer()->Get(Symbol(ident_expression->GetName())));
}

void Interpreter::Visit(NotExpression *not_expression) {
  not_expression->GetExpression()->Accept(this);

  auto object = std::dynamic_pointer_cast<BoolObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }

  SetTosValue(std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(!object->GetValue()))));
}

void Interpreter::Visit(NumberExpression *number_expression) {
  SetTosValue(number_expression->GetNumber());
}

void Interpreter::Visit(UnarMinusExpression *unar_minus_expression) {
  unar_minus_expression->GetExpression()->Accept(this);

  auto object = std::dynamic_pointer_cast<IntegerObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("minus from non int");
  }
  SetTosValue(std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(-object->GetValue()))));
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

  auto object = std::dynamic_pointer_cast<BoolObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }

  if (!object->GetValue()) {
    throw std::runtime_error("assert is false");
  }
}

void Interpreter::Visit(AssignStatement *assign_statement) {
  assign_statement->GetExpression()->Accept(this);
  auto new_value = GetTosValue();
  auto last_value = tree_->GetCurrentLayer()->Get(Symbol(assign_statement->GetLvalue()->GetName()));
  if (!std::dynamic_pointer_cast<UninitObject>(last_value)) {
    if (typeid(*new_value) != typeid(*last_value)) {
      throw std::runtime_error("different types");
    }
  }
  tree_->GetCurrentLayer()->Put(Symbol(assign_statement->GetLvalue()->GetName()), new_value);
}

void Interpreter::Visit(IfElseStatement *if_else_statement) {
  StatementsList *statements_list;
  tree_->GoDown();

  if_else_statement->GetExpression()->Accept(this);

  auto object = std::dynamic_pointer_cast<BoolObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }

  if (object->GetValue()) {
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
  auto object = std::dynamic_pointer_cast<BoolObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }
  if (object->GetValue()) {
    tree_->GoDown();

    if_statement->GetStatements()->Accept(this);
    tree_->GoUp();
    tree_->GoNext();
  }
}

void Interpreter::Visit(OutStatement *out_statement) {
  out_statement->GetExpression()->Accept(this);
  auto object = std::dynamic_pointer_cast<IntegerObject>(GetTosValue());
  if (object == nullptr) {
    throw std::runtime_error("Can't System.out.println non int object");
  }
  std::cout << object->GetValue() << std::endl;
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

    auto object = std::dynamic_pointer_cast<BoolObject>(GetTosValue());
    if (object == nullptr) {
      throw std::runtime_error("Condition is not boolean type");
    }

    if (!object->GetValue()) break;
    tree_->GoDown();
    offset_.push(0);
    while_statement->GetStatementsList()->Accept(this);
    offset_.pop();
    tree_->GoUp();
  }
  tree_->GoNext();
}

void Interpreter::GetResult(Program *program) {
  Visit(program);
}