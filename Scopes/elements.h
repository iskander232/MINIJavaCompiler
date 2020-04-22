#pragma once

#include "BinaryOperator/AndOperator.h"
#include "BinaryOperator/DivOperator.h"
#include "BinaryOperator/EqualOperator.h"
#include "BinaryOperator/LessOperator.h"
#include "BinaryOperator/MinusOperator.h"
#include "BinaryOperator/MoreOperator.h"
#include "BinaryOperator/MulOperator.h"
#include "BinaryOperator/OrOperator.h"
#include "BinaryOperator/PlusOperator.h"
#include "BinaryOperator/ProcOperator.h"

#include "Classes/ClassesList.h"

#include "Declarations/VarDecl.h"

#include "Expression/ArrayGetExpression.h"
#include "Expression/ArrayRvalueExpression.h"
#include "Expression/BinaryCallExpression.h"
#include "Expression/BoolExpression.h"
#include "Expression/GetLengthExpression.h"
#include "Expression/IdentExpression.h"
#include "Expression/NotExpression.h"
#include "Expression/NumberExpression.h"
#include "Expression/UnarMinusExpression.h"

#include "Lvalue/Lvalue.h"

#include "Main/Main.h"

#include "Program/Program.h"

#include "Statements/AssertStatement.h"
#include "Statements/AssignStatement.h"
#include "Statements/IfElseStatement.h"
#include "Statements/IfStatement.h"
#include "Statements/OutStatement.h"
#include "Statements/ScopeDeclStatement.h"
#include "Statements/StatementsList.h"
#include "Statements/WhileStatement.h"

#include "Types/ArrayObject.h"
#include "Types/Bool.h"
#include "Types/IdentObject.h"
#include "Types/Integer.h"
#include "Types/UninitObject.h"