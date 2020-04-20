#include "PrintVisitor.h"

#include "elements.h"

PrintVisitor::PrintVisitor(const std::string &filename) : stream_(filename) {};

void PrintVisitor::PrintVisitor::Print() {
  for (int i = 0; i < num_tabs_; ++i) {
    stream_ << "  ";
  }
}

void PrintVisitor::Visit(AndOperator *and_operator) {
  Print();
  stream_ << "and" << std::endl;
}

void PrintVisitor::Visit(DivOperator *div_operator) {
  Print();
  stream_ << "divide" << std::endl;
}

void PrintVisitor::Visit(EqualOperator *equal_operator) {
  Print();
  stream_ << "equal" << std::endl;
}

void PrintVisitor::Visit(LessOperator *less_operator) {
  Print();
  stream_ << "less" << std::endl;
}

void PrintVisitor::Visit(MinusOperator *minus_operator) {
  Print();
  stream_ << "minus" << std::endl;
}

void PrintVisitor::Visit(MoreOperator *more_operator) {
  Print();
  stream_ << "more" << std::endl;
}

void PrintVisitor::Visit(MulOperator *mul_opearator) {
  Print();
  stream_ << "multiply" << std::endl;
}

void PrintVisitor::Visit(OrOperator *or_operator) {
  Print();
  stream_ << "or" << std::endl;
}

void PrintVisitor::Visit(PlusOperator *plus_operator) {
  Print();
  stream_ << "plus" << std::endl;
}

void PrintVisitor::Visit(ProcOperator *proc_operator) {
  Print();
  stream_ << "take the remainder of the division" << std::endl;
}

void PrintVisitor::Visit(ClassesList *classes_list) {
  Print();
  stream_ << "Classes List is:" << std::endl;

  ++num_tabs_;

  for (int i = 0; i < classes_list->GetSize(); ++i) {
//    classes_list->GetIth(i)->Accept(this);
  }

  --num_tabs_;
}

void PrintVisitor::Visit(VarDecl *var_decl) {
  Print();
  stream_ << "new variable with name:" << var_decl->GetName() << std::endl;
}

void PrintVisitor::Visit(BinaryCallExpression *binary_call_expression) {
  Print();
  stream_ << "Binary operator calling is:" << std::endl;

  ++num_tabs_;
  binary_call_expression->GetFirst()->Accept(this);
  binary_call_expression->GetOperator()->Accept(this);
  binary_call_expression->GetSecond()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(BoolExpression *bool_expression) {
  Print();
  stream_ << " bool expression value is:";
  if (bool_expression->GetValue()->Get(BasicType::Bool)) {
    stream_ << "true" << std::endl;
  } else {
    stream_ << "false" << std::endl;
  }
}

void PrintVisitor::Visit(IdentExpression *ident_expression) {
  Print();
  stream_ << "Variable name is: " << ident_expression->GetName() << std::endl;
}

void PrintVisitor::Visit(NotExpression *not_expression) {
  Print();
  stream_ << "not than" << std::endl;

  ++num_tabs_;
  not_expression->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(NumberExpression *number_expression) {
  Print();
  stream_ << "integer value is " << number_expression->GetNumber() << std::endl;
}

void PrintVisitor::Visit(UnarMinusExpression *unar_minus_expression) {
  Print();
  stream_ << "minus ..." << std::endl;

  ++num_tabs_;
  unar_minus_expression->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(Lvalue *lvalue) {
  Print();
  stream_ << "lvalue is:" << std::endl;
}

void PrintVisitor::Visit(Main *main) {
  Print();
  stream_ << "Main class " << main->GetName() << " starts here:" << std::endl;

  ++num_tabs_;
  main->GetStatementsList()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(Program *program) {
  Print();
  stream_ << "Program:" << std::endl;

  ++num_tabs_;
  program->GetMain()->Accept(this);
  program->GetClassesList()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(AssertStatement *assert_statement) {
  Print();
  stream_ << "assert:" << std::endl;

  ++num_tabs_;
  assert_statement->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(AssignStatement *assign_statement) {
  Print();
  stream_ << "Assigning" << std::endl;

  ++num_tabs_;
  assign_statement->GetLvalue()->Accept(this);
  assign_statement->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(IfElseStatement *if_else_statement) {}
void PrintVisitor::Visit(IfStatement *if_statement) {}

void PrintVisitor::Visit(OutStatement *out_statement) {
  Print();
  stream_ << "cout" << std::endl;

  ++num_tabs_;
  out_statement->GetExpression()->Accept(this);
  --num_tabs_;
}

void PrintVisitor::Visit(ScopeDeclStatement *scope_decl_statement) {}

void PrintVisitor::Visit(StatementsList *statements_list) {
  Print();
  stream_ << "statements list" << std::endl;

  ++num_tabs_;
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    statements_list->GetIth(i)->Accept(this);
  }
  --num_tabs_;
}

void PrintVisitor::Visit(WhileStatement *while_statement) {}

PrintVisitor::~PrintVisitor() {
  stream_.close();
}