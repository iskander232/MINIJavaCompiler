#include "TemplateVisitor.h"
#include "Types/BasicObject.h"
#include "SymbolTable/ScopeLayer.h"

#include <string>
#include <map>
#include <stack>

class Interpreter : public Visitor {
 public:
  explicit Interpreter(ScopeLayer *root);
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
  void Visit(ClassesList *classes_list) override;
  void Visit(VarDecl *var_decl) override;
  void Visit(BinaryCallExpression *binary_call_expression) override;
  void Visit(BoolExpression *bool_expression) override;
  void Visit(IdentExpression *ident_expression) override;
  void Visit(NotExpression *not_expression) override;
  void Visit(NumberExpression *number_expression) override;
  void Visit(UnarMinusExpression *unar_minus_expression) override;
  void Visit(Lvalue *lvalue) override;
  void Visit(Main *main) override;
  void Visit(Program *program) override;
  void Visit(AssertStatement *assert_statement) override;
  void Visit(AssignStatement *assign_statement) override;
  void Visit(IfElseStatement *if_else_statement) override;
  void Visit(IfStatement *if_statement) override;
  void Visit(OutStatement *out_statement) override;
  void Visit(ScopeDeclStatement *scope_decl_statement) override;
  void Visit(StatementsList *statements_list) override;
  void Visit(WhileStatement *while_statement) override;

  void GetResult(Program *program);
 private:
  BasicObject GetTosValue();
  void SetTosValue(BasicObject object);
  BasicObject tos_value_;
  ScopeLayer *current_layer_;
  std::stack<size_t> offset_;
};