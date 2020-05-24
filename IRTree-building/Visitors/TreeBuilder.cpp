#include "TreeBuilder.h"
#include "Grammar/elements.h"

TreeBuilder::TreeBuilder() : tree_(new ScopeLayer()), current_layer_(tree_.root_), current_class_(nullptr) {}

std::map<Symbol, std::shared_ptr<IdentObject> > TreeBuilder::GetClasses() {
  return classes_list_;
}

std::map<Symbol, std::shared_ptr<FunctionObject> > TreeBuilder::GetFunctions() {
  return functions_;
}

///////////////////////////////////////////////////////////////////////////////

void TreeBuilder::Visit(AndOperator *and_operator) {}
void TreeBuilder::Visit(DivOperator *div_operator) {}
void TreeBuilder::Visit(EqualOperator *equal_operator) {}
void TreeBuilder::Visit(LessOperator *less_operator) {}
void TreeBuilder::Visit(MinusOperator *minus_operator) {}
void TreeBuilder::Visit(MoreOperator *more_operator) {}
void TreeBuilder::Visit(MulOperator *mul_opearator) {}
void TreeBuilder::Visit(OrOperator *or_operator) {}
void TreeBuilder::Visit(PlusOperator *plus_operator) {}
void TreeBuilder::Visit(ProcOperator *proc_operator) {}
void TreeBuilder::Visit(ArrayElementLvalue *array_element_lvalue) {}
void TreeBuilder::Visit(ArrayGetExpression *array_get_expression) {}
void TreeBuilder::Visit(ArrayRvalueExpression *array_rvalue_expression) {}
void TreeBuilder::Visit(BinaryCallExpression *binary_call_expression) {}
void TreeBuilder::Visit(BoolExpression *bool_expression) {}
void TreeBuilder::Visit(ExprList *expr_list) {}
void TreeBuilder::Visit(GetLengthExpression *get_length_expression) {}
void TreeBuilder::Visit(IdentCreateExpression *ident_create_expression) {}
void TreeBuilder::Visit(IdentExpression *ident_expression) {}
void TreeBuilder::Visit(InvokeExpression *invoke_expression) {}
void TreeBuilder::Visit(NotExpression *not_expression) {}
void TreeBuilder::Visit(NumberExpression *number_expression) {}
void TreeBuilder::Visit(ThisExpression *this_expression) {}
void TreeBuilder::Visit(UnarMinusExpression *unar_minus_expression) {}
void TreeBuilder::Visit(AssertStatement *assert_statement) {}
void TreeBuilder::Visit(MethodInvokeStatement *method_invoke_statement) {}
void TreeBuilder::Visit(OutStatement *out_statement) {}
void TreeBuilder::Visit(ReturnStatement *return_statement) {}
void TreeBuilder::Visit(Formals *formals) {}

///////////////////////////////////////////////////////////////////////////////

void TreeBuilder::Visit(ClassesList *classes_list) {
  for (int i = 0; i < classes_list->GetSize(); ++i) {
    classes_list->GetIth(i)->Accept(this);
  }
}

void TreeBuilder::Visit(DeclarationList *declaration_list) {
  for (int i = 0; i < declaration_list->GetSize(); ++i) {
    declaration_list->GetIth(i)->Accept(this);
  }
}

void TreeBuilder::Visit(MethodDecl *method_decl) {
  auto my_class = current_class_;
  current_class_ = nullptr;

  if (my_class == nullptr) {
    throw std::runtime_error("try to declare func not in class");
  }

  auto func = std::make_shared<FunctionObject>(FunctionObject(method_decl->GetType(),
                                                              method_decl->GetFormals(),
                                                              method_decl->GetStatements()));
  func->SetName(my_class->name_, method_decl->GetName());
  current_layer_->DeclareFunction(Symbol(func->name_), func);

  ScopeLayer* new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;

  method_decl->GetStatements()->Accept(this);

  tree_.AddMapping(Symbol(func->name_), new_layer);
  functions_[Symbol(func->name_)] = func;

  current_layer_ = current_layer_->GetParent();
  current_class_ = my_class;
}

void TreeBuilder::Visit(Class *a_class) {
  current_class_ = std::make_shared<IdentObject>(IdentObject(a_class->GetName()));
  classes_list_[Symbol(current_class_->name_)] = current_class_;

  if (classes_names_.find(Symbol(current_class_->name_)) != classes_names_.end()) {
    throw std::runtime_error("double classes with same nemes");
  }
  classes_names_.insert(Symbol(current_class_->name_));

  a_class->GetDeclarations()->Accept(this);
}

void TreeBuilder::Visit(ArrayLvalue *array_lvalue) {
  current_layer_->DeclareVariable(Symbol(array_lvalue->GetName()));
}

void TreeBuilder::Visit(SimpleLvalue *simple_lvalue) {
  current_layer_->DeclareVariable(Symbol(simple_lvalue->GetName()));
}

void TreeBuilder::Visit(AssignStatement *assign_statement) {
  Lvalue *lvalue = assign_statement->GetLvalue();
  lvalue->Accept(this);
}


void TreeBuilder::Visit(Lvalue *lvalue) {
  if (!std::dynamic_pointer_cast<UninitObject>(lvalue->GetType())) {
    current_layer_->DeclareVariable(Symbol(lvalue->GetName()));
    current_layer_->Put(Symbol(lvalue->GetName()), lvalue->GetType());
  }
}

void TreeBuilder::Visit(VarDecl *var_decl) {
  if (current_class_ == nullptr) {
    current_layer_->DeclareVariable(Symbol(var_decl->GetName()));
    current_layer_->Put(Symbol(var_decl->GetName()), var_decl->GetType());
  } else {
    current_class_->SetValue(var_decl->GetName(), var_decl->GetType());
  }
}

void TreeBuilder::Visit(Main *main) {
  current_class_ = nullptr;

  auto symbol = Symbol(main->GetName() + "_____" + "main");
  auto ret_type = std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()));
  auto func = std::make_shared<FunctionObject>(
      FunctionObject(ret_type, new Formals(), main->GetStatementsList()));
  func->SetName(main->GetName() + "_____" + "main");
  current_layer_->DeclareFunction(Symbol(func->name_), func);

  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;

  main->GetStatementsList()->Accept(this);

  tree_.AddMapping(Symbol(func->name_), new_layer);
  functions_[symbol] = func;

  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(Program *program) {
  program->GetClassesList()->Accept(this);
  program->GetMain()->Accept(this);
}

void TreeBuilder::Visit(IfElseStatement *if_else_statement) {
  if_else_statement->GetExpression()->Accept(this);

  auto new_layer1 = new ScopeLayer(current_layer_);
  auto new_layer2 = new ScopeLayer(new_layer1);
  current_layer_ = new_layer2;

  if_else_statement->GetIfStatements()->Accept(this);

  current_layer_ = current_layer_->GetParent();
  new_layer2 = new ScopeLayer(current_layer_);

  current_layer_ = new_layer2;
  if_else_statement->GetElseStatements()->Accept(this);

  current_layer_ = current_layer_->GetParent()->GetParent();
}

void TreeBuilder::Visit(IfStatement *if_statement) {
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;

  if_statement->GetStatements()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(ScopeDeclStatement *scope_decl_statement) {
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;

  scope_decl_statement->GetStatementsList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
}

void TreeBuilder::Visit(WhileStatement *while_statement) {
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;

  while_statement->GetStatementsList()->Accept(this);

  current_layer_ = current_layer_->GetParent();
}

ScopeLayerTree *TreeBuilder::GetTree() {
  return &tree_;
}