#include "TemplateVisitor.h"
#include "Types/Object.h"
#include "SymbolTable/ScopeLayerTree.h"

#include "../../IRTree-building/function-mechanism/Frame.h"
#include <function-mechanism/FunctionTable.h>

#include <string>
#include <map>
#include <stack>

class FunctionCallVisitor : public TemplateVisitor<std::shared_ptr<Object>> {
 public:
  FunctionCallVisitor(
      ScopeLayer* function_scope,
      std::shared_ptr<FunctionObject> function,
      std::map<Symbol, std::shared_ptr<IdentObject>> classes_list,
      std::shared_ptr<IdentObject> current_class);


  void SetParams(const std::vector<std::shared_ptr<Object>> &params);
  void SetTree(ScopeLayerTree *tree);

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

  Frame &GetFrame();
 private:
  ScopeLayer* root_layer;
  ScopeLayer* current_layer_;
  std::stack<int> offsets_;
  Frame frame;
  FunctionTable table_;
  std::map<Symbol, std::shared_ptr<IdentObject>> classes_list_;
  std::shared_ptr<IdentObject> current_class_;
  ScopeLayerTree *tree_;
  bool returned_ = false;
};