#include "FunctionCallVisitor.h"

#include "Grammar/elements.h"

#include <iostream>
#include <stdexcept>
#include <function-mechanism/FunctionStorage.h>

FunctionCallVisitor::FunctionCallVisitor(
    ScopeLayer *function_scope, std::shared_ptr<FunctionObject> function,
    std::map<Symbol, std::shared_ptr<IdentObject>> classes_list, std::shared_ptr<IdentObject> current_class
) : root_layer(function_scope), frame(function), classes_list_(classes_list), current_class_(current_class) {
  current_layer_ = root_layer;
  offsets_.push(0);
  tos_value_ = std::shared_ptr<Object>(new UninitObject());
}

void FunctionCallVisitor::SetTree(ScopeLayerTree *tree) {
  tree_ = tree;
}

Frame &FunctionCallVisitor::GetFrame() {
  return frame;
}

void FunctionCallVisitor::SetParams(const std::vector<std::shared_ptr<Object>> &params) {
  frame.SetParams(params);
}
////////////////////////////////////////////////////////////////////////

void FunctionCallVisitor::Visit(AndOperator *and_operator) {}
void FunctionCallVisitor::Visit(DivOperator *div_operator) {}
void FunctionCallVisitor::Visit(EqualOperator *equal_operator) {}
void FunctionCallVisitor::Visit(LessOperator *less_operator) {}
void FunctionCallVisitor::Visit(MinusOperator *minus_operator) {}
void FunctionCallVisitor::Visit(MoreOperator *more_operator) {}
void FunctionCallVisitor::Visit(MulOperator *mul_opearator) {}
void FunctionCallVisitor::Visit(OrOperator *or_operator) {}
void FunctionCallVisitor::Visit(PlusOperator *plus_operator) {}
void FunctionCallVisitor::Visit(ProcOperator *proc_operator) {}
void FunctionCallVisitor::Visit(Class *a_class) {}
void FunctionCallVisitor::Visit(ClassesList *classes_list) {}
void FunctionCallVisitor::Visit(DeclarationList *declaration_list) {}
void FunctionCallVisitor::Visit(MethodDecl *method_decl) {}

////////////////////////////////////////////////////////////////////////


void FunctionCallVisitor::Visit(VarDecl *var_decl) {
  size_t index = frame.AllocVariable(var_decl->GetType());
  table_.CreateVariable(Symbol(var_decl->GetName()));
  table_.Put(Symbol(var_decl->GetName()), index);
}

void FunctionCallVisitor::Visit(ArrayGetExpression *array_get_expression) {
  auto array = std::dynamic_pointer_cast<ArrayObject>(Accept(array_get_expression->GetArray()));
  auto index_int = std::dynamic_pointer_cast<IntegerObject>(Accept(array_get_expression->GetIndex()));
  if (nullptr == array || index_int == nullptr) {
    throw std::runtime_error("exception in array get expression");
  }
  int index = index_int->GetValue();
  tos_value_ = array->GetIth(index);
}

void FunctionCallVisitor::Visit(ArrayRvalueExpression *array_rvalue_expression) {
  auto length_object = Accept(array_rvalue_expression->GetLength());
  auto length = std::dynamic_pointer_cast<IntegerObject>(length_object);
  if (length == nullptr) {
    throw std::runtime_error("length of array is not int");
  }
  auto new_array = std::make_shared<ArrayObject>(ArrayObject(array_rvalue_expression->GetType(), length->GetValue()));
  tos_value_ = std::dynamic_pointer_cast<Object>(new_array);
}

void FunctionCallVisitor::Visit(BinaryCallExpression *binary_call_expression) {
  auto first = Accept(binary_call_expression->GetFirst());

  auto second = Accept(binary_call_expression->GetSecond());

  tos_value_ = binary_call_expression->GetOperator()->eval(first, second);

}

void FunctionCallVisitor::Visit(BoolExpression *bool_expression) {
  tos_value_ = bool_expression->GetValue();
}

void FunctionCallVisitor::Visit(ExprList *expr_list) {}

void FunctionCallVisitor::Visit(GetLengthExpression *get_length_expression) {
  auto array_object = Accept(get_length_expression->GetArray());
  auto array = std::dynamic_pointer_cast<ArrayObject>(array_object);

  if (array == nullptr) {
    throw std::runtime_error("get length from not arraty");
  }
  tos_value_ = std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(array->GetLength())));
}

void FunctionCallVisitor::Visit(IdentCreateExpression *ident_create_expression) {
  Symbol name = Symbol(ident_create_expression->GetName());
  if (classes_list_.find(name) == classes_list_.end()) {
    throw std::runtime_error("try to create not declarated class");
  }
  tos_value_ = std::dynamic_pointer_cast<Object>(classes_list_[name]->GetCopy());
}
void FunctionCallVisitor::Visit(IdentExpression *ident_expression) {
  if (table_.Has(Symbol(ident_expression->GetName()))) {
    auto index = table_.Get(Symbol(ident_expression->GetName()));
    tos_value_ = frame.Get(index);
  } else {
    if (current_class_ != nullptr) {
      tos_value_ = current_class_->GetValue(ident_expression->GetName());
    } else {
      throw std::runtime_error("value with this name doesn't exist");
    }
  }
}

void FunctionCallVisitor::Visit(InvokeExpression *invoke_expression) {
  auto ident = std::dynamic_pointer_cast<IdentObject>(Accept(invoke_expression->GetExpression()));
  if (ident == nullptr) {
    throw std::runtime_error("try to invoke function from non class");
  }
  auto func_name = std::make_pair(Symbol(ident->name_), Symbol(invoke_expression->GetName()));
  auto func = current_layer_->GetFunc(func_name);

  std::vector<std::shared_ptr<Object>> params;
  for (int i = 0; i < invoke_expression->GetExprList()->GetSize(); ++i) {
    params.push_back(Accept(invoke_expression->GetExprList()->GetIth(i)));
    if (params.back()->IsEqual(std::make_shared<UninitObject>(UninitObject()))) {
      throw std::runtime_error("param isn't init");
    }
  }

  FunctionCallVisitor new_visitor(
      tree_->GetFunctionScopeByName(func_name),
      func,
      classes_list_,
      ident);

  func->formals_->Accept(&new_visitor);
  new_visitor.SetParams(params);
  new_visitor.SetTree(tree_);
  frame.SetReturnType(func->ret_type_);
  new_visitor.GetFrame().SetParentFrame(&frame);
  new_visitor.Visit(FunctionStorage::GetInstance().Get(func_name)->statements_list_);

  if (func->ret_type_->IsEqual(std::make_shared<UninitObject>(UninitObject()))) {
    if (new_visitor.GetFrame().Returned()) {
      throw std::runtime_error("returned void function");
    }
  } else {
    if (!frame.Returned()) {
      throw std::runtime_error("didn't returned not void function");
    }
  }
  if (!func->ret_type_->IsEqual(frame.GetReturnValue())) {
    throw std::runtime_error(
        "returned value " + frame.GetReturnValue()->GetName() +
            " and expected ret value " + func->ret_type_->GetName()
            + " are different");
  }
  tos_value_ = frame.GetReturnValue();
}

void FunctionCallVisitor::Visit(NotExpression *not_expression) {
  auto not_object = Accept(not_expression->GetExpression());

  auto object = std::dynamic_pointer_cast<BoolObject>(not_object);
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }

  tos_value_ = std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(!object->GetValue())));
}

void FunctionCallVisitor::Visit(NumberExpression *number_expression) {
  tos_value_ = number_expression->GetNumber();
}

void FunctionCallVisitor::Visit(ThisExpression *this_expression) {
  if (current_class_ == nullptr) {
    throw std::runtime_error("This class is NULL");
  }
  tos_value_ = std::dynamic_pointer_cast<Object>(current_class_);
}

void FunctionCallVisitor::Visit(UnarMinusExpression *unar_minus_expression) {
  auto minus_object = Accept(unar_minus_expression->GetExpression());

  auto object = std::dynamic_pointer_cast<IntegerObject>(minus_object);
  if (object == nullptr) {
    throw std::runtime_error("minus from non int");
  }
  tos_value_ = std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(-object->GetValue())));
}

void FunctionCallVisitor::Visit(Lvalue *lvalue) {
  int index;
  if (table_.Has(Symbol(lvalue->GetName()))) {
    index = table_.Get(Symbol(lvalue->GetName()));
    frame.Set(index, tos_value_->GetCopy());
  } else {
    if (current_class_ == nullptr) {
      throw std::runtime_error("Try to set to value with bad name");
    }
    current_class_->SetValue(lvalue->GetName(), tos_value_->GetCopy());
  }
}

void FunctionCallVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {
  auto new_value = tos_value_->GetCopy();
  auto pos = std::dynamic_pointer_cast<IntegerObject>(Accept(array_element_lvalue->GetPos()));
  if (pos == nullptr) {
    throw std::runtime_error("Pos isn't integer");
  }

  std::shared_ptr<ArrayObject> array = nullptr;
  if (table_.Has(Symbol(array_element_lvalue->GetName()))) {
    int array_index = table_.Get(Symbol(array_element_lvalue->GetName()));
    array = std::dynamic_pointer_cast<ArrayObject>(frame.Get(array_index));
  } else {
    array = std::dynamic_pointer_cast<ArrayObject>(current_class_->GetValue(array_element_lvalue->GetName()));
  }
  if (array == nullptr) {
    throw std::runtime_error("try to get element from not array");
  }

  array->SetIth(pos->GetValue(), new_value);
}

void FunctionCallVisitor::Visit(ArrayLvalue *array_lvalue) {
  size_t index2 = frame.AllocVariable(array_lvalue->GetType());
  table_.CreateVariable(Symbol(array_lvalue->GetName()));
  table_.Put(Symbol(array_lvalue->GetName()), index2);

  auto new_value = tos_value_->GetCopy();
  int index;
  if (table_.Has(Symbol(array_lvalue->GetName()))) {
    index = table_.Get(Symbol(array_lvalue->GetName()));
    frame.Set(index, new_value);
  } else {
    current_class_->SetValue(array_lvalue->GetName(), new_value);
  }
}

void FunctionCallVisitor::Visit(SimpleLvalue *simple_lvalue) {
  size_t index2 = frame.AllocVariable(simple_lvalue->GetType());
  table_.CreateVariable(Symbol(simple_lvalue->GetName()));
  table_.Put(Symbol(simple_lvalue->GetName()), index2);

  auto new_value = tos_value_;
  int index;
  if (table_.Has(Symbol(simple_lvalue->GetName()))) {
    index = table_.Get(Symbol(simple_lvalue->GetName()));
    frame.Set(index, new_value);
  } else {
    current_class_->SetValue(simple_lvalue->GetName(), new_value);
  }
}

void FunctionCallVisitor::Visit(Main *main) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();

  main->GetStatementsList()->Accept(this);

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();

  offsets_.pop();
  int index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}

void FunctionCallVisitor::Visit(Program *program) {
  program->GetClassesList()->Accept(this);
  program->GetMain()->Accept(this);
}

void FunctionCallVisitor::Visit(AssertStatement *assert_statement) {
  auto object = std::dynamic_pointer_cast<BoolObject>(Accept(assert_statement->GetExpression()));
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }
  if (!object->GetValue()) {
    throw std::runtime_error("assert is false");
  }
}

void FunctionCallVisitor::Visit(AssignStatement *assign_statement) {
  assign_statement->GetExpression()->Accept(this);
  assign_statement->GetLvalue()->Accept(this);
}

void FunctionCallVisitor::Visit(IfElseStatement *if_else_statement) {
  StatementsList *statements_list;

  current_layer_ = current_layer_->GetChild(offsets_.top());
  frame.AllocScope();
  table_.BeginScope();

  auto object = std::dynamic_pointer_cast<BoolObject>(Accept(if_else_statement->GetExpression()));
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }

  if (object->GetValue()) {
    statements_list = if_else_statement->GetIfStatements();
    offsets_.push(0);
  } else {
    statements_list = if_else_statement->GetElseStatements();
    offsets_.push(1);
  }

  current_layer_ = current_layer_->GetChild(offsets_.top());
  frame.AllocScope();
  table_.BeginScope();
  offsets_.push(0);

  statements_list->Accept(this);

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
  offsets_.pop();

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
  offsets_.pop();

  int index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}

void FunctionCallVisitor::Visit(IfStatement *if_statement) {
  auto object = std::dynamic_pointer_cast<BoolObject>(Accept(if_statement->GetExpression()));
  if (object == nullptr) {
    throw std::runtime_error("Condition is not boolean type");
  }
  if (object->GetValue()) {
    current_layer_ = current_layer_->GetChild(offsets_.top());
    frame.AllocScope();
    table_.BeginScope();
    offsets_.push(0);

    if_statement->GetStatements()->Accept(this);

    offsets_.pop();
    current_layer_ = current_layer_->GetParent();
    frame.DeallocScope();
    table_.EndScope();
  }
  int index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}

void FunctionCallVisitor::Visit(MethodInvokeStatement *method_invoke_statement) {
  auto ident = std::dynamic_pointer_cast<IdentObject>(Accept(method_invoke_statement->GetExpr()));
  if (ident == nullptr) {
    throw std::runtime_error("try to invoke function from non class");
  }
  auto func_name = std::make_pair(Symbol(ident->name_), Symbol(method_invoke_statement->GetName()));
  auto func = current_layer_->GetFunc(func_name);

  std::vector<std::shared_ptr<Object>> params;
  for (int i = 0; i < method_invoke_statement->GetExprList()->GetSize(); ++i) {
    params.push_back(Accept(method_invoke_statement->GetExprList()->GetIth(i)));
    if (params.back()->IsEqual(std::make_shared<UninitObject>(UninitObject()))) {
      throw std::runtime_error("param isn't init");
    }
  }

  FunctionCallVisitor new_visitor(tree_->GetFunctionScopeByName(func_name), func, classes_list_, ident);
  func->formals_->Accept(&new_visitor);
  new_visitor.SetParams(params);

  new_visitor.GetFrame().SetParentFrame(&frame);
  new_visitor.Visit(FunctionStorage::GetInstance().Get(func_name)->statements_list_);

  if (func->ret_type_->IsEqual(std::make_shared<UninitObject>(UninitObject()))) {
    if (new_visitor.GetFrame().Returned()) {
      throw std::runtime_error("returned void function");
    }
  } else {
    if (!new_visitor.GetFrame().Returned()) {
      throw std::runtime_error("didn't returned not void function");
    }
  }
  if (!func->ret_type_->IsEqual(frame.GetReturnValue())) {
    throw std::runtime_error(
        "returned value " + frame.GetReturnValue()->GetName() +
            " and expected ret value " + func->ret_type_->GetName()
            + " are different");
  }
}

void FunctionCallVisitor::Visit(OutStatement *out_statement) {
  auto object = std::dynamic_pointer_cast<IntegerObject>(Accept(out_statement->GetExpression()));
  if (object == nullptr) {
    throw std::runtime_error("Can't System.out.println non int object");
  }
  std::cout << object->GetValue() << std::endl;
}

void FunctionCallVisitor::Visit(ReturnStatement *return_statement) {
  if (frame.HasParent()) {
    frame.SetParentReturnValue(Accept(return_statement->GetExpr()));
  }

  returned_ = true;
}

void FunctionCallVisitor::Visit(ScopeDeclStatement *scope_decl_statement) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();

  scope_decl_statement->GetStatementsList()->Accept(this);

  offsets_.pop();
  int index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->GetParent();
  frame.DeallocScope();
  table_.EndScope();
}

void FunctionCallVisitor::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    if (!returned_) {
      statements_list->GetIth(i)->Accept(this);
    }
  }
}

void FunctionCallVisitor::Visit(WhileStatement *while_statement) {
  current_layer_ = current_layer_->GetChild(offsets_.top());
  offsets_.push(0);
  frame.AllocScope();
  table_.BeginScope();

  while (!returned_) {
    auto object = std::dynamic_pointer_cast<BoolObject>(Accept(while_statement->GetExpression()));

    if (object == nullptr) {
      throw std::runtime_error("Condition is not boolean type");
    }

    if (!object->GetValue()) break;

    while_statement->GetStatementsList()->Accept(this);

  }
  offsets_.pop();
  int index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->GetParent();

  frame.DeallocScope();
  table_.EndScope();

}

void FunctionCallVisitor::Visit(Formals *formals) {
  int index = -1;
  for (int i = 0; i < formals->GetSize(); ++i) {
    Symbol symbol = Symbol(formals->GetIth(i).second);
    table_.CreateVariable(symbol);
    table_.Put(symbol, index);
    --index;
  }
}