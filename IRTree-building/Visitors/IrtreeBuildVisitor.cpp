#include <irtree/tree_wrapper/ExpressionWrapper.h>
#include <irtree/nodes/expressions/ConstExpression.h>
#include <irtree/tree_wrapper/conditional_wrappers/NegateConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/AndConditionalWrapper.h>
#include <irtree/tree_wrapper/conditional_wrappers/OrConditionalWrapper.h>
#include <irtree/types/BinaryOperatorType.h>
#include <irtree/generators/Temporary.h>
#include <irtree/nodes/expressions/BinopExpression.h>
#include <irtree/nodes/expressions/TempExpression.h>
#include <irtree/nodes/expressions/MemExpression.h>
#include <irtree/nodes/statements/MoveStatement.h>
#include <irtree/tree_wrapper/StatementWrapper.h>
#include <irtree/nodes/statements/LabelStatement.h>
#include <irtree/nodes/statements/SeqStatement.h>
#include <irtree/nodes/statements/JumpStatement.h>
#include <irtree/nodes/ExpressionList.h>
#include <irtree/nodes/expressions/CallExpression.h>
#include <irtree/nodes/expressions/NameExpression.h>
#include <irtree/types/LogicOperatorType.h>
#include <irtree/tree_wrapper/conditional_wrappers/RelativeConditionalWrapper.h>
#include "elements.h"

#include "IrtreeBuildVisitor.h"
void IrtreeBuildVisitor::Visit(AndOperator *and_operator) {
  auto first = Accept(and_operator->first);
  auto second = Accept(and_operator->second);

  tos_value_ = new IRT::AndConditionalWrapper(
      first,
      second
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(true)));
}

void IrtreeBuildVisitor::Visit(DivOperator *div_operator) {
  auto first = Accept(div_operator->first);
  auto second = Accept(div_operator->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::DIV,
          first->ToExpression(),
          second->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(EqualOperator *equal_operator) {
  auto first = Accept(equal_operator->first);
  auto second = Accept(equal_operator->second);

  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::EQ,
      first->ToExpression(),
      second->ToExpression()
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(true)));

}

void IrtreeBuildVisitor::Visit(LessOperator *less_operator) {
  auto first = Accept(less_operator->first);
  auto second = Accept(less_operator->second);

  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::LT,
      first->ToExpression(),
      second->ToExpression()
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(true)));
}

void IrtreeBuildVisitor::Visit(MinusOperator *minus_operator) {
  auto first = Accept(minus_operator->first);
  auto second = Accept(minus_operator->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MINUS,
          first->ToExpression(),
          second->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));

}

void IrtreeBuildVisitor::Visit(MoreOperator *more_operator) {
  auto first = Accept(more_operator->first);
  auto second = Accept(more_operator->second);

  tos_value_ = new IRT::RelativeConditionalWrapper(
      IRT::LogicOperatorType::GT,
      first->ToExpression(),
      second->ToExpression()
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(0)));
}

void IrtreeBuildVisitor::Visit(MulOperator *mul_opearator) {
  auto first = Accept(mul_opearator->first);
  auto second = Accept(mul_opearator->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MUL,
          first->ToExpression(),
          second->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(OrOperator *or_operator) {
  auto first = Accept(or_operator->first);
  auto second = Accept(or_operator->second);

  tos_value_ = new IRT::OrConditionalWrapper(
      first,
      second
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(0)));
}

void IrtreeBuildVisitor::Visit(PlusOperator *plus_operator) {
  auto first = Accept(plus_operator->first);
  auto second = Accept(plus_operator->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::PLUS,
          first->ToExpression(),
          second->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(ProcOperator *proc_operator) {
  auto first = Accept(proc_operator->first);
  auto second = Accept(proc_operator->second);

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MOD,
          first->ToExpression(),
          second->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(Class *a_class) {
  std::string last_name_ = current_class_name_;
  current_class_name_ = a_class->GetName();
  Accept(a_class->GetDeclarations());
  current_class_name_ = last_name_;
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(ClassesList *classes_list) {
  for (int i = 0; i < classes_list->GetSize(); ++i) {
    Accept(classes_list->GetIth(i));
  }
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(DeclarationList *declaration_list) {
  for (int i = 0; i < declaration_list->GetSize(); ++i) {
    Accept(declaration_list->GetIth(i));
  }
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(MethodDecl *method_decl) {
  auto function = std::make_shared<FunctionObject>(FunctionObject(method_decl->GetType(),
                                                                  method_decl->GetFormals(),
                                                                  method_decl->GetStatements()));

  function->SetName(current_class_name_, method_decl->GetName());
  current_frame_ = new IRT::FrameTranslator(
      function->name_, function->ret_type_, classes_[Symbol(current_class_name_)]);
  frame_translator_[function->name_] = current_frame_;

  function->formals_->Accept(this);

  bool is_void = (nullptr == std::dynamic_pointer_cast<UninitObject>(function->ret_type_));
  if (!is_void) {
    current_frame_->AddReturnAddress(function->ret_type_->GetSize(), function->ret_type_);
  }

  auto statements_ir = Accept(function->statements_list_);

  if (statements_ir) {
    if (!is_void) {
      tos_value_ = new IRT::StatementWrapper(
          new IRT::SeqStatement(
              new IRT::LabelStatement(IRT::Label(function->name_)),
              statements_ir->ToStatement()
          )
      );
      tos_value_->SetObject(function->ret_type_);
      method_trees_.emplace(function->name_, tos_value_->ToStatement());
    }
  } else {
    tos_value_ = nullptr;
  }
}

void IrtreeBuildVisitor::Visit(VarDecl *var_decl) {
  if (!is_main) {
    tos_value_ = nullptr;
    return;
  }
  current_frame_->AddLocalVariable(
      var_decl->GetName(), var_decl->GetType()->GetSize(), var_decl->GetType());
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(BinaryCallExpression *binary_call_expression) {
  BinaryOperator *Operator = binary_call_expression->GetOperator();
  Operator->SetExprs(binary_call_expression->GetFirst(), binary_call_expression->GetSecond());
  Accept(Operator);
}

void IrtreeBuildVisitor::Visit(ArrayGetExpression *array_get_expression) {
  auto array_type = std::dynamic_pointer_cast<ArrayObject>(
      Accept(array_get_expression->GetArray())->GetObject());

  auto offset = new IRT::MemExpression(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MUL,
          new IRT::ConstExpression(array_type->GetObject()->GetSize()),
          new IRT::BinopExpression(
              IRT::BinaryOperatorType::PLUS,
              Accept(array_get_expression->GetIndex())->ToExpression(),
              new IRT::ConstExpression(1))));

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::MemExpression(
          new IRT::BinopExpression(
              IRT::BinaryOperatorType::PLUS,
              Accept(array_get_expression->GetArray())->ToExpression(),
              offset
          ))
  );
  tos_value_->SetObject(array_type->GetObject());
}

void IrtreeBuildVisitor::Visit(ArrayRvalueExpression *array_rvalue_expression) {
  auto size = dynamic_cast<IRT::ConstExpression *>(Accept(array_rvalue_expression->GetLength()));
  if (size == nullptr) {
    throw std::runtime_error("Try to create array with not const size");
  }
  auto array = std::make_shared<ArrayObject>(
      ArrayObject(
          array_rvalue_expression->GetType(),
          size->Value() + 1));
  auto temp = IRT::Temporary();
  current_frame_->AddLocalVariable(temp.ToString(), array->GetSize(), array);
  tos_value_ = new IRT::ExpressionWrapper(
      current_frame_->GetAddress(temp.ToString())->ToExpression()
  );
  tos_value_->SetObject(array);
}

void IrtreeBuildVisitor::Visit(BoolExpression *bool_expression) {
  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::ConstExpression(
          std::dynamic_pointer_cast<BoolObject>(bool_expression->GetValue())->GetValue())
  );
  tos_value_->SetObject(std::make_shared<BoolObject>(BoolObject(0)));
}

void IrtreeBuildVisitor::Visit(ExprList *expr_list) {}

void IrtreeBuildVisitor::Visit(GetLengthExpression *get_length_expression) {
  auto array = Accept(get_length_expression->GetArray());
  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::MemExpression(array->ToExpression()));
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(IdentCreateExpression *ident_create_expression) {
  auto temp = IRT::Temporary();
  auto ident = classes_[Symbol(ident_create_expression->GetName())];
  current_frame_->AddLocalVariable(temp.ToString(), ident->GetSize(), ident);

  tos_value_ = new IRT::ExpressionWrapper(
      current_frame_->GetAddress(temp.ToString())->ToExpression()
  );
  tos_value_->SetObject(ident);
}

void IrtreeBuildVisitor::Visit(IdentExpression *ident_expression) {
  auto addres = current_frame_->GetAddress(ident_expression->GetName());

  tos_value_ = new IRT::ExpressionWrapper(addres->ToExpression());
  tos_value_->SetObject(current_frame_->GetType(ident_expression->GetName()));
}

void IrtreeBuildVisitor::Visit(InvokeExpression *invoke_expression) {
  IRT::ExpressionList *irt_expressions = new IRT::ExpressionList();

  irt_expressions->Add(
      Accept(invoke_expression->GetExpression())->ToExpression());

  for (int i = 0; i < invoke_expression->GetExprList()->GetSize(); ++i) {
    irt_expressions->Add(
        Accept(invoke_expression->GetExprList()->GetIth(i))->ToExpression());
  }

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::CallExpression(
          new IRT::NameExpression(IRT::Label(invoke_expression->GetName())),
          irt_expressions
      )
  );
}

void IrtreeBuildVisitor::Visit(NotExpression *not_expression) {
  tos_value_ = new IRT::NegateConditionalWrapper(tos_value_);
  tos_value_->SetObject(nullptr);
}

void IrtreeBuildVisitor::Visit(NumberExpression *number_expression) {
  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::ConstExpression(
          std::dynamic_pointer_cast<IntegerObject>(number_expression->GetNumber())->GetValue())
  );
  tos_value_->SetObject(number_expression->GetNumber());
}

void IrtreeBuildVisitor::Visit(ThisExpression *this_expression) {
  tos_value_ = new IRT::ExpressionWrapper(
      current_frame_->GetAddress("::this")->ToExpression()
  );
  tos_value_->SetObject(current_frame_->GetType("::this"));
}

void IrtreeBuildVisitor::Visit(UnarMinusExpression *unar_minus_expression) {
  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::BinopExpression(
          IRT::BinaryOperatorType::MINUS,
          new IRT::ConstExpression(0),
          tos_value_->ToExpression()
      )
  );
  tos_value_->SetObject(std::make_shared<IntegerObject>(IntegerObject(0)));
}

void IrtreeBuildVisitor::Visit(Lvalue *lvalue) {}

void IrtreeBuildVisitor::Visit(ArrayElementLvalue *array_element_lvalue) {}

void IrtreeBuildVisitor::Visit(ArrayLvalue *array_lvalue) {}

void IrtreeBuildVisitor::Visit(SimpleLvalue *simple_lvalue) {}

void IrtreeBuildVisitor::Visit(Main *main) {
  auto function = std::make_shared<FunctionObject>(
      FunctionObject(std::make_shared<UninitObject>(UninitObject()),
                     new Formals(),
                     main->GetStatementsList()));

  function->SetName(main->GetName(), "main");
  current_frame_ = new IRT::FrameTranslator(
      function->name_, function->ret_type_, std::make_shared<IdentObject>(IdentObject("main")));
  frame_translator_[function->name_] = current_frame_;

  function->formals_->Accept(this);

  bool is_void = (nullptr == std::dynamic_pointer_cast<UninitObject>(function->ret_type_));
  if (!is_void) {
    current_frame_->AddReturnAddress(function->ret_type_->GetSize(), function->ret_type_);
  }

  auto statements_ir = Accept(main->GetStatementsList());

  if (statements_ir) {
    if (!is_void) {
      tos_value_ = new IRT::StatementWrapper(
          new IRT::SeqStatement(
              new IRT::LabelStatement(IRT::Label(function->name_)),
              statements_ir->ToStatement()
          )
      );
      tos_value_->SetObject(function->ret_type_);
      method_trees_.emplace(function->name_, tos_value_->ToStatement());
    }
  } else {
    tos_value_ = nullptr;
  }

}

void IrtreeBuildVisitor::Visit(Program *program) {
  Accept(program->GetClassesList());
  is_main = true;
  Accept(program->GetMain());
}

void IrtreeBuildVisitor::Visit(AssertStatement *assert_statement) {
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(AssignStatement *assign_statement) {
  auto var_expression = current_frame_->GetAddress(
      assign_statement->GetLvalue()->GetName())->ToExpression();
  auto rvalue = Accept(assign_statement->GetExpression());

  tos_value_ = new IRT::StatementWrapper(new IRT::MoveStatement(
      var_expression,
      rvalue->ToExpression())
  );
}

void IrtreeBuildVisitor::Visit(IfElseStatement *if_else_statement) {
  auto if_cond_expression = Accept(if_else_statement->GetExpression());
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_else_statement->GetIfStatements());
  current_frame_->TearDownScope();
  current_frame_->SetupScope();
  auto false_stmt = Accept(if_else_statement->GetElseStatements());
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_false;
  IRT::Label label_join;

  IRT::Statement *suffix = new IRT::LabelStatement(label_join);

  IRT::Label *result_true = &label_join;
  IRT::Label *result_false = &label_join;

  if (false_stmt) {
    result_false = &label_false;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_false),
        new IRT::SeqStatement(false_stmt->ToStatement(), suffix)
    );

    if (true_stmt) {
      suffix = new IRT::SeqStatement(
          new IRT::JumpStatement(label_join),
          suffix
      );
    }
  }

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_true),
        new IRT::SeqStatement(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
          if_cond_expression->ToConditional(*result_true, *result_false),
          suffix
      )
  );

}

void IrtreeBuildVisitor::Visit(IfStatement *if_statement) {
  auto if_cond_expression = Accept(if_statement->GetExpression());
  current_frame_->SetupScope();
  auto true_stmt = Accept(if_statement->GetStatements());
  current_frame_->TearDownScope();
  current_frame_->SetupScope();
  current_frame_->TearDownScope();

  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Statement *suffix = new IRT::LabelStatement(label_join);

  IRT::Label *result_true = &label_join;

  if (true_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_true),
        new IRT::SeqStatement(true_stmt->ToStatement(), suffix)
    );
  }

  tos_value_ = new IRT::StatementWrapper(
      new IRT::SeqStatement(
          if_cond_expression->ToConditional(*result_true, label_join),
          suffix
      )
  );
}

void IrtreeBuildVisitor::Visit(MethodInvokeStatement *method_invoke_statement) {
  IRT::ExpressionList *irt_expressions = new IRT::ExpressionList();

  irt_expressions->Add(
      Accept(method_invoke_statement->GetExpr())->ToExpression());

  for (int i = 0; i < method_invoke_statement->GetExprList()->GetSize(); ++i) {
    irt_expressions->Add(
        Accept(method_invoke_statement->GetExprList()->GetIth(i))->ToExpression());
  }

  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(OutStatement *out_statement) {
  tos_value_ = nullptr;
}

void IrtreeBuildVisitor::Visit(ReturnStatement *return_statement) {
  auto return_expr = Accept(return_statement->GetExpr());
  tos_value_ = new IRT::StatementWrapper(
      new IRT::MoveStatement(
          current_frame_->GetReturnValueAddress()->ToExpression(),
          return_expr->ToExpression()
      )
  );
  tos_value_->SetObject(current_frame_->GetType("::return"));
}

void IrtreeBuildVisitor::Visit(ScopeDeclStatement *scope_decl_statement) {
  current_frame_->SetupScope();
  tos_value_ = Accept(scope_decl_statement->GetStatementsList());
  current_frame_->TearDownScope();
}

void IrtreeBuildVisitor::Visit(StatementsList *statements_list) {
  std::vector<IRT::Statement *> statements;
  for (int i = 0; i < statements_list->GetSize(); ++i) {
    auto statement = statements_list->GetIth(i);
    auto stmt = Accept(statement);
    if (stmt) {
      statements.push_back(stmt->ToStatement());
    }
  }

  if (statements.size() == 0) {
    tos_value_ = nullptr;
    return;
  }

  if (statements.size() == 1) {
    tos_value_ = new IRT::StatementWrapper(statements[0]);
    return;
  }

  IRT::Statement *suffix = statements.back();

  for (int index = (int) statements.size() - 2; index >= 0; --index) {
    suffix = new IRT::SeqStatement(
        statements.at(index),
        suffix
    );
  }
  tos_value_ = new IRT::StatementWrapper(suffix);
}

void IrtreeBuildVisitor::Visit(WhileStatement *while_statement) {
  auto BoolConditional = Accept(while_statement->GetExpression());
  IRT::Label begin_label;
  IRT::Label end_label;
  IRT::Label end_while_label;

  IRT::Statement *rule = new IRT::LabelStatement(end_while_label);

  rule = new IRT::SeqStatement(
      BoolConditional->ToConditional(begin_label, end_while_label),
      rule
  );
  rule = new IRT::SeqStatement(
      new IRT::LabelStatement(end_label),
      rule
  );
  rule = new IRT::SeqStatement(
      new IRT::JumpStatement(end_label),
      rule
  );
  rule = new IRT::SeqStatement(
      Accept(while_statement->GetStatementsList())->ToStatement(),
      rule
  );

  rule = new IRT::SeqStatement(
      new IRT::LabelStatement(begin_label),
      rule
  );

  rule = new IRT::SeqStatement(
      new IRT::JumpStatement(end_label),
      rule
  );
  tos_value_ = new IRT::StatementWrapper(rule);
}

void IrtreeBuildVisitor::Visit(Formals *formals) {
  for (int i = 0; i < formals->GetSize(); ++i) {
    auto formal = formals->GetIth(i);
    current_frame_->AddArgumentAddress(formal.second, formal.first->GetSize(), formal.first);
  }
}

IrtreeBuildVisitor::IrtreeBuildVisitor(ScopeLayerTree *layer_tree,
                                       std::map<Symbol, std::shared_ptr<IdentObject>> classes)
    : tree_(layer_tree), classes_(classes) {}

IrtMapping IrtreeBuildVisitor::GetTrees() {
  return method_trees_;
}
