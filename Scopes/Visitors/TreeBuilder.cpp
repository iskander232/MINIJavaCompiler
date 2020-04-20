#include "TreeBuilder.h"
#include "elements.h"

TreeBuilder::TreeBuilder() : tree_(new ScopeLayer()), current_layer_(tree_.root_) {}

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
void TreeBuilder::Visit(BinaryCallExpression *binary_call_expression) {}
void TreeBuilder::Visit(BoolExpression *bool_expression) {}
void TreeBuilder::Visit(IdentExpression *ident_expression) {}
void TreeBuilder::Visit(NotExpression *not_expression) {}
void TreeBuilder::Visit(NumberExpression *number_expression) {}
void TreeBuilder::Visit(UnarMinusExpression *unar_minus_expression) {}
void TreeBuilder::Visit(Lvalue *lvalue) {}
void TreeBuilder::Visit(AssertStatement *assert_statement) {}
void TreeBuilder::Visit(OutStatement *out_statement) {}
void TreeBuilder::Visit(ClassesList *classes_list) {}
//////////////////////////////////////////////////////////


void TreeBuilder::Visit(AssignStatement *assign_statement) {
  if (assign_statement->GetLvalue()->GetType()->GetType() != BasicType::Void) {
    current_layer_->DeclareVariable(Symbol(assign_statement->GetLvalue()->GetName()));
  }
}
void TreeBuilder::Visit(VarDecl *var_decl) {
  current_layer_->DeclareVariable(Symbol(var_decl->GetName()));
}

void TreeBuilder::Visit(Main *main) {
  auto new_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_layer;
  main->GetStatementsList()->Accept(this);
}

void TreeBuilder::Visit(Program *program) {
  program->GetClassesList()->Accept(this);
  program->GetMain()->Accept(this);
}

void TreeBuilder::Visit(IfElseStatement *if_else_statement) {
  auto if_else_layer = new ScopeLayer(current_layer_);
  current_layer_ = if_else_layer;

  auto if_layer = new ScopeLayer(current_layer_);
  current_layer_ = if_layer;
  if_else_statement->GetIfStatements()->Accept(this);
  current_layer_ = current_layer_->GetParent();

  auto else_layer = new ScopeLayer(current_layer_);
  current_layer_ = else_layer;
  if_else_statement->GetElseStatements()->Accept(this);
  current_layer_ = current_layer_->GetParent();

  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(IfStatement *if_statement) {
  auto if_layer = new ScopeLayer(current_layer_);
  current_layer_ = if_layer;
  if_statement->GetStatements()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(ScopeDeclStatement *scope_decl_statement) {
  auto new_scope_layer = new ScopeLayer(current_layer_);
  current_layer_ = new_scope_layer;
  scope_decl_statement->GetStatementsList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

void TreeBuilder::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
}

void TreeBuilder::Visit(WhileStatement *while_statement) {
  auto while_layer = new ScopeLayer(current_layer_);
  current_layer_ = while_layer;
  while_statement->GetStatementsList()->Accept(this);
  current_layer_ = current_layer_->GetParent();
}

ScopeLayer *TreeBuilder::GetRoot() {
  return tree_.root_;
}