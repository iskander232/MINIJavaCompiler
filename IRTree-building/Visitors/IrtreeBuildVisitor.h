#pragma once

#include <include/visitors/Visitor.h>
#include <irtree/tree_wrapper/SubtreeWrapper.h>
#include <unordered_map>
#include <function-mechanism/FrameTranslator.h>
#include <SymbolTable/ScopeLayerTree.h>
#include "TemplateVisitor.h"

using IrtMapping = std::unordered_map<std::string, IRT::Statement*>;

class IrtreeBuildVisitor : public TemplateVisitor<IRT::SubtreeWrapper*> {
  public:
  explicit IrtreeBuildVisitor(ScopeLayerTree* layer_tree, std::map<Symbol, std::shared_ptr<IdentObject>> classes);
  void Visit(AndOperator *and_operator) override;
  void Visit(DivOperator *div_operator) override;
  void Visit(EqualOperator *equal_operator) override;
  void Visit(LessOperator *less_operator) override;
  void Visit(MinusOperator *minus_operator) override;
  void Visit(MoreOperator *more_operator) override;
  void Visit(MulOperator *mul_opearator) override;
  void Visit(OrOperator *or_operator) override;
  void Visit(PlusOperator *plus_operator) override;
  void Visit(ProcOperator *proc_operator) override;
  void Visit(Class *a_class) override;
  void Visit(ClassesList *classes_list) override;
  void Visit(DeclarationList *declaration_list) override;
  void Visit(MethodDecl *method_decl) override;
  void Visit(VarDecl *var_decl) override;
  void Visit(ArrayGetExpression *array_get_expression) override;
  void Visit(ArrayRvalueExpression *array_rvalue_expression) override;
  void Visit(BinaryCallExpression *binary_call_expression) override;
  void Visit(BoolExpression *bool_expression) override;
  void Visit(ExprList *expr_list) override;
  void Visit(GetLengthExpression *get_length_expression) override;
  void Visit(IdentCreateExpression *ident_create_expression) override;
  void Visit(IdentExpression *ident_expression) override;
  void Visit(InvokeExpression *invoke_expression) override;
  void Visit(NotExpression *not_expression) override;
  void Visit(NumberExpression *number_expression) override;
  void Visit(ThisExpression *this_expression) override;
  void Visit(UnarMinusExpression *unar_minus_expression) override;
  void Visit(Lvalue *lvalue) override;
  void Visit(ArrayElementLvalue *array_element_lvalue) override;
  void Visit(ArrayLvalue *array_lvalue) override;
  void Visit(SimpleLvalue *simple_lvalue) override;
  void Visit(Main *main) override;
  void Visit(Program *program) override;
  void Visit(AssertStatement *assert_statement) override;
  void Visit(AssignStatement *assign_statement) override;
  void Visit(IfElseStatement *if_else_statement) override;
  void Visit(IfStatement *if_statement) override;
  void Visit(MethodInvokeStatement *method_invoke_statement) override;
  void Visit(OutStatement *out_statement) override;
  void Visit(ReturnStatement *return_statement) override;
  void Visit(ScopeDeclStatement *scope_decl_statement) override;
  void Visit(StatementsList *statements_list) override;
  void Visit(WhileStatement *while_statement) override;
  void Visit(Formals *formals) override;

   IrtMapping GetTrees();

 private:
  std::unordered_map<std::string, IRT::FrameTranslator*> frame_translator_;
  std::map<Symbol, std::shared_ptr<IdentObject>> classes_;
  std::string current_class_name_ = "";
  bool is_main = false;

  IRT::FrameTranslator *current_frame_;
  ScopeLayerTree* tree_;

  IrtMapping method_trees_;
};


