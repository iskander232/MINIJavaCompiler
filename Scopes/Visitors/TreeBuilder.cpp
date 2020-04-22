#include "TreeBuilder.h"
#include "elements.h"

TreeBuilder::TreeBuilder() : tree_(new ScopeLayer()) {}

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
void TreeBuilder::Visit(ArrayGetExpression *array_get_expression) {}
void TreeBuilder::Visit(ArrayRvalueExpression *array_rvalue_expression) {}
void TreeBuilder::Visit(BinaryCallExpression *binary_call_expression) {}
void TreeBuilder::Visit(BoolExpression *bool_expression) {}
void TreeBuilder::Visit(GetLengthExpression *get_length_expression) {}
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
  Lvalue *lvalue = assign_statement->GetLvalue();
  if (nullptr == std::dynamic_pointer_cast<UninitObject>(lvalue->GetType())) {
    tree_.GetCurrentLayer()->DeclareVariable(Symbol(assign_statement->GetLvalue()->GetName()));
  }
}

void TreeBuilder::Visit(VarDecl *var_decl) {
  tree_.GetCurrentLayer()->DeclareVariable(Symbol(var_decl->GetName()));
}

void TreeBuilder::Visit(Main *main) {
  tree_.AddChildAndGoThere();
  main->GetStatementsList()->Accept(this);
  tree_.GoUp();
  tree_.GoNext();
}

void TreeBuilder::Visit(Program *program) {
  program->GetClassesList()->Accept(this);
  program->GetMain()->Accept(this);
}

void TreeBuilder::Visit(IfElseStatement *if_else_statement) {
  tree_.AddChildAndGoThere();

  tree_.AddChildAndGoThere();
  if_else_statement->GetIfStatements()->Accept(this);
  tree_.GoUp();
  tree_.GoNext();

  tree_.AddChildAndGoThere();
  if_else_statement->GetElseStatements()->Accept(this);

  tree_.GoUp();
  tree_.GoUp();
  tree_.GoNext();
}

void TreeBuilder::Visit(IfStatement *if_statement) {
  tree_.AddChildAndGoThere();
  if_statement->GetStatements()->Accept(this);
  tree_.GoUp();
  tree_.GoNext();
}

void TreeBuilder::Visit(ScopeDeclStatement *scope_decl_statement) {
  tree_.AddChildAndGoThere();
  scope_decl_statement->GetStatementsList()->Accept(this);
  tree_.GoUp();
  tree_.GoNext();
}

void TreeBuilder::Visit(StatementsList *statements_list) {
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
}

void TreeBuilder::Visit(WhileStatement *while_statement) {
  tree_.AddChildAndGoThere();
  while_statement->GetStatementsList()->Accept(this);
  tree_.GoUp();
  tree_.GoNext();
}

ScopeLayerTree *TreeBuilder::GetTree() {
  return &tree_;
}