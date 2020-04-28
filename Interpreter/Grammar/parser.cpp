// A Bison parser, made by GNU Bison 3.5.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "parser.hh"


// Unqualified %code blocks.
#line 21 "parser.y"

    #include "include/driver.hh"
    #include "Grammar/location.hh"
    #include "Grammar/elements.h"
    #include "Location/Location.h"
    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }

#line 55 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 146 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  parser::parser (Scanner &scanner_yyarg, Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 48: // binary_operator
        value.YY_MOVE_OR_COPY< BinaryOperator* > (YY_MOVE (that.value));
        break;

      case 49: // class
        value.YY_MOVE_OR_COPY< Class* > (YY_MOVE (that.value));
        break;

      case 50: // classes
        value.YY_MOVE_OR_COPY< ClassesList* > (YY_MOVE (that.value));
        break;

      case 65: // declaration
        value.YY_MOVE_OR_COPY< Declaration* > (YY_MOVE (that.value));
        break;

      case 51: // declarations
        value.YY_MOVE_OR_COPY< DeclarationList* > (YY_MOVE (that.value));
        break;

      case 53: // expr_list
      case 54: // empty_expr_list
      case 55: // some_expr_list
        value.YY_MOVE_OR_COPY< ExprList* > (YY_MOVE (that.value));
        break;

      case 52: // expr
        value.YY_MOVE_OR_COPY< Expression* > (YY_MOVE (that.value));
        break;

      case 56: // formals
      case 57: // empty_formals
      case 58: // some_formals
        value.YY_MOVE_OR_COPY< Formals* > (YY_MOVE (that.value));
        break;

      case 59: // lvalue
        value.YY_MOVE_OR_COPY< Lvalue* > (YY_MOVE (that.value));
        break;

      case 60: // main_class
        value.YY_MOVE_OR_COPY< Main* > (YY_MOVE (that.value));
        break;

      case 61: // method_declaration
        value.YY_MOVE_OR_COPY< MethodDecl* > (YY_MOVE (that.value));
        break;

      case 62: // program
        value.YY_MOVE_OR_COPY< Program* > (YY_MOVE (that.value));
        break;

      case 63: // statement
        value.YY_MOVE_OR_COPY< Statement* > (YY_MOVE (that.value));
        break;

      case 64: // statements
        value.YY_MOVE_OR_COPY< StatementsList* > (YY_MOVE (that.value));
        break;

      case 66: // variable_declaration
        value.YY_MOVE_OR_COPY< VarDecl* > (YY_MOVE (that.value));
        break;

      case 43: // "number"
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 46: // simple_type
      case 47: // array_type
        value.YY_MOVE_OR_COPY< std::shared_ptr<Object> > (YY_MOVE (that.value));
        break;

      case 42: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 48: // binary_operator
        value.move< BinaryOperator* > (YY_MOVE (that.value));
        break;

      case 49: // class
        value.move< Class* > (YY_MOVE (that.value));
        break;

      case 50: // classes
        value.move< ClassesList* > (YY_MOVE (that.value));
        break;

      case 65: // declaration
        value.move< Declaration* > (YY_MOVE (that.value));
        break;

      case 51: // declarations
        value.move< DeclarationList* > (YY_MOVE (that.value));
        break;

      case 53: // expr_list
      case 54: // empty_expr_list
      case 55: // some_expr_list
        value.move< ExprList* > (YY_MOVE (that.value));
        break;

      case 52: // expr
        value.move< Expression* > (YY_MOVE (that.value));
        break;

      case 56: // formals
      case 57: // empty_formals
      case 58: // some_formals
        value.move< Formals* > (YY_MOVE (that.value));
        break;

      case 59: // lvalue
        value.move< Lvalue* > (YY_MOVE (that.value));
        break;

      case 60: // main_class
        value.move< Main* > (YY_MOVE (that.value));
        break;

      case 61: // method_declaration
        value.move< MethodDecl* > (YY_MOVE (that.value));
        break;

      case 62: // program
        value.move< Program* > (YY_MOVE (that.value));
        break;

      case 63: // statement
        value.move< Statement* > (YY_MOVE (that.value));
        break;

      case 64: // statements
        value.move< StatementsList* > (YY_MOVE (that.value));
        break;

      case 66: // variable_declaration
        value.move< VarDecl* > (YY_MOVE (that.value));
        break;

      case 43: // "number"
        value.move< int > (YY_MOVE (that.value));
        break;

      case 46: // simple_type
      case 47: // array_type
        value.move< std::shared_ptr<Object> > (YY_MOVE (that.value));
        break;

      case 42: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 48: // binary_operator
        value.copy< BinaryOperator* > (that.value);
        break;

      case 49: // class
        value.copy< Class* > (that.value);
        break;

      case 50: // classes
        value.copy< ClassesList* > (that.value);
        break;

      case 65: // declaration
        value.copy< Declaration* > (that.value);
        break;

      case 51: // declarations
        value.copy< DeclarationList* > (that.value);
        break;

      case 53: // expr_list
      case 54: // empty_expr_list
      case 55: // some_expr_list
        value.copy< ExprList* > (that.value);
        break;

      case 52: // expr
        value.copy< Expression* > (that.value);
        break;

      case 56: // formals
      case 57: // empty_formals
      case 58: // some_formals
        value.copy< Formals* > (that.value);
        break;

      case 59: // lvalue
        value.copy< Lvalue* > (that.value);
        break;

      case 60: // main_class
        value.copy< Main* > (that.value);
        break;

      case 61: // method_declaration
        value.copy< MethodDecl* > (that.value);
        break;

      case 62: // program
        value.copy< Program* > (that.value);
        break;

      case 63: // statement
        value.copy< Statement* > (that.value);
        break;

      case 64: // statements
        value.copy< StatementsList* > (that.value);
        break;

      case 66: // variable_declaration
        value.copy< VarDecl* > (that.value);
        break;

      case 43: // "number"
        value.copy< int > (that.value);
        break;

      case 46: // simple_type
      case 47: // array_type
        value.copy< std::shared_ptr<Object> > (that.value);
        break;

      case 42: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 48: // binary_operator
        value.move< BinaryOperator* > (that.value);
        break;

      case 49: // class
        value.move< Class* > (that.value);
        break;

      case 50: // classes
        value.move< ClassesList* > (that.value);
        break;

      case 65: // declaration
        value.move< Declaration* > (that.value);
        break;

      case 51: // declarations
        value.move< DeclarationList* > (that.value);
        break;

      case 53: // expr_list
      case 54: // empty_expr_list
      case 55: // some_expr_list
        value.move< ExprList* > (that.value);
        break;

      case 52: // expr
        value.move< Expression* > (that.value);
        break;

      case 56: // formals
      case 57: // empty_formals
      case 58: // some_formals
        value.move< Formals* > (that.value);
        break;

      case 59: // lvalue
        value.move< Lvalue* > (that.value);
        break;

      case 60: // main_class
        value.move< Main* > (that.value);
        break;

      case 61: // method_declaration
        value.move< MethodDecl* > (that.value);
        break;

      case 62: // program
        value.move< Program* > (that.value);
        break;

      case 63: // statement
        value.move< Statement* > (that.value);
        break;

      case 64: // statements
        value.move< StatementsList* > (that.value);
        break;

      case 66: // variable_declaration
        value.move< VarDecl* > (that.value);
        break;

      case 43: // "number"
        value.move< int > (that.value);
        break;

      case 46: // simple_type
      case 47: // array_type
        value.move< std::shared_ptr<Object> > (that.value);
        break;

      case 42: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 42: // "identifier"
#line 118 "parser.y"
                 { yyo << yysym.value.template as < std::string > (); }
#line 651 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 43: // "number"
#line 118 "parser.y"
                 { yyo << yysym.value.template as < int > (); }
#line 657 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 46: // simple_type
#line 118 "parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Object> > (); }
#line 663 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 47: // array_type
#line 118 "parser.y"
                 { yyo << yysym.value.template as < std::shared_ptr<Object> > (); }
#line 669 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 48: // binary_operator
#line 118 "parser.y"
                 { yyo << yysym.value.template as < BinaryOperator* > (); }
#line 675 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 49: // class
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Class* > (); }
#line 681 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 50: // classes
#line 118 "parser.y"
                 { yyo << yysym.value.template as < ClassesList* > (); }
#line 687 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 51: // declarations
#line 118 "parser.y"
                 { yyo << yysym.value.template as < DeclarationList* > (); }
#line 693 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 52: // expr
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Expression* > (); }
#line 699 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 53: // expr_list
#line 118 "parser.y"
                 { yyo << yysym.value.template as < ExprList* > (); }
#line 705 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 54: // empty_expr_list
#line 118 "parser.y"
                 { yyo << yysym.value.template as < ExprList* > (); }
#line 711 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 55: // some_expr_list
#line 118 "parser.y"
                 { yyo << yysym.value.template as < ExprList* > (); }
#line 717 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 56: // formals
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Formals* > (); }
#line 723 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 57: // empty_formals
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Formals* > (); }
#line 729 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 58: // some_formals
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Formals* > (); }
#line 735 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 59: // lvalue
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Lvalue* > (); }
#line 741 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 60: // main_class
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Main* > (); }
#line 747 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 61: // method_declaration
#line 118 "parser.y"
                 { yyo << yysym.value.template as < MethodDecl* > (); }
#line 753 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 62: // program
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Program* > (); }
#line 759 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 63: // statement
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Statement* > (); }
#line 765 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 64: // statements
#line 118 "parser.y"
                 { yyo << yysym.value.template as < StatementsList* > (); }
#line 771 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 65: // declaration
#line 118 "parser.y"
                 { yyo << yysym.value.template as < Declaration* > (); }
#line 777 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      case 66: // variable_declaration
#line 118 "parser.y"
                 { yyo << yysym.value.template as < VarDecl* > (); }
#line 783 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
        break;

      default:
        break;
    }
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 48: // binary_operator
        yylhs.value.emplace< BinaryOperator* > ();
        break;

      case 49: // class
        yylhs.value.emplace< Class* > ();
        break;

      case 50: // classes
        yylhs.value.emplace< ClassesList* > ();
        break;

      case 65: // declaration
        yylhs.value.emplace< Declaration* > ();
        break;

      case 51: // declarations
        yylhs.value.emplace< DeclarationList* > ();
        break;

      case 53: // expr_list
      case 54: // empty_expr_list
      case 55: // some_expr_list
        yylhs.value.emplace< ExprList* > ();
        break;

      case 52: // expr
        yylhs.value.emplace< Expression* > ();
        break;

      case 56: // formals
      case 57: // empty_formals
      case 58: // some_formals
        yylhs.value.emplace< Formals* > ();
        break;

      case 59: // lvalue
        yylhs.value.emplace< Lvalue* > ();
        break;

      case 60: // main_class
        yylhs.value.emplace< Main* > ();
        break;

      case 61: // method_declaration
        yylhs.value.emplace< MethodDecl* > ();
        break;

      case 62: // program
        yylhs.value.emplace< Program* > ();
        break;

      case 63: // statement
        yylhs.value.emplace< Statement* > ();
        break;

      case 64: // statements
        yylhs.value.emplace< StatementsList* > ();
        break;

      case 66: // variable_declaration
        yylhs.value.emplace< VarDecl* > ();
        break;

      case 43: // "number"
        yylhs.value.emplace< int > ();
        break;

      case 46: // simple_type
      case 47: // array_type
        yylhs.value.emplace< std::shared_ptr<Object> > ();
        break;

      case 42: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 123 "parser.y"
                             {yylhs.value.as < Program* > () = new Program(yystack_[1].value.as < Main* > (), yystack_[0].value.as < ClassesList* > ()); driver.program = yylhs.value.as < Program* > (); Location::GetInstance().SetLoc(yylhs.value.as < Program* > (), driver.location);}
#line 1101 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 3:
#line 126 "parser.y"
                        {yylhs.value.as < ClassesList* > () = new ClassesList();  Location::GetInstance().SetLoc(yylhs.value.as < ClassesList* > (), driver.location);}
#line 1107 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 4:
#line 127 "parser.y"
                        {yystack_[1].value.as < ClassesList* > ()->AddClass(yystack_[0].value.as < Class* > ()); yylhs.value.as < ClassesList* > () = yystack_[1].value.as < ClassesList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < ClassesList* > (), driver.location);}
#line 1113 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 5:
#line 131 "parser.y"
                                              {yylhs.value.as < Class* > () = new Class(yystack_[3].value.as < std::string > (), yystack_[1].value.as < DeclarationList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Class* > (), driver.location);}
#line 1119 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 6:
#line 135 "parser.y"
                                                                                              {yylhs.value.as < Main* > () = new Main(yystack_[11].value.as < std::string > (), yystack_[2].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Main* > (), driver.location);}
#line 1125 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 7:
#line 139 "parser.y"
                                {yylhs.value.as < Declaration* > () = yystack_[0].value.as < VarDecl* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Declaration* > (), driver.location);}
#line 1131 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 8:
#line 140 "parser.y"
                                {yylhs.value.as < Declaration* > () = yystack_[0].value.as < MethodDecl* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Declaration* > (), driver.location);}
#line 1137 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 9:
#line 144 "parser.y"
                                            {yylhs.value.as < DeclarationList* > () = new DeclarationList();  Location::GetInstance().SetLoc(yylhs.value.as < DeclarationList* > (), driver.location);}
#line 1143 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 10:
#line 145 "parser.y"
                                            {yystack_[1].value.as < DeclarationList* > ()->AddDeclaration(yystack_[0].value.as < Declaration* > ()); yylhs.value.as < DeclarationList* > () = yystack_[1].value.as < DeclarationList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < DeclarationList* > (), driver.location);}
#line 1149 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 11:
#line 149 "parser.y"
                                   {yylhs.value.as < VarDecl* > () = new VarDecl(yystack_[2].value.as < std::shared_ptr<Object> > (), yystack_[1].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < VarDecl* > (), driver.location);}
#line 1155 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 12:
#line 150 "parser.y"
                                   {yylhs.value.as < VarDecl* > () = new VarDecl(yystack_[2].value.as < std::shared_ptr<Object> > (), yystack_[1].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < VarDecl* > (), driver.location);}
#line 1161 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 13:
#line 154 "parser.y"
                                                                            {yylhs.value.as < MethodDecl* > () = new MethodDecl(yystack_[7].value.as < std::shared_ptr<Object> > (), yystack_[6].value.as < std::string > (), yystack_[4].value.as < Formals* > (), yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < MethodDecl* > (), driver.location);}
#line 1167 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 14:
#line 155 "parser.y"
                                                                            {yylhs.value.as < MethodDecl* > () = new MethodDecl(yystack_[7].value.as < std::shared_ptr<Object> > (), yystack_[6].value.as < std::string > (), yystack_[4].value.as < Formals* > (), yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < MethodDecl* > (), driver.location);}
#line 1173 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 15:
#line 156 "parser.y"
                                                                            { yylhs.value.as < MethodDecl* > () = new MethodDecl(
                    std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject())), yystack_[6].value.as < std::string > (), yystack_[4].value.as < Formals* > (), yystack_[1].value.as < StatementsList* > ());
                                                                               Location::GetInstance().SetLoc(yylhs.value.as < MethodDecl* > (), driver.location);
    }
#line 1182 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 16:
#line 163 "parser.y"
                    {yylhs.value.as < Formals* > () = yystack_[0].value.as < Formals* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1188 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 17:
#line 164 "parser.y"
                    {yylhs.value.as < Formals* > () = yystack_[0].value.as < Formals* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1194 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 18:
#line 168 "parser.y"
                    {yylhs.value.as < Formals* > () = new Formals();  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1200 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 19:
#line 172 "parser.y"
                                                    {yylhs.value.as < Formals* > () = new Formals(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1206 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 20:
#line 173 "parser.y"
                                                    {yylhs.value.as < Formals* > () = new Formals(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1212 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 21:
#line 174 "parser.y"
                                                    {yystack_[3].value.as < Formals* > ()->AddFormals(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ()); yylhs.value.as < Formals* > () = yystack_[3].value.as < Formals* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1218 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 22:
#line 175 "parser.y"
                                                    {yystack_[3].value.as < Formals* > ()->AddFormals(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ()); yylhs.value.as < Formals* > () = yystack_[3].value.as < Formals* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Formals* > (), driver.location);}
#line 1224 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 23:
#line 180 "parser.y"
                            {yylhs.value.as < std::shared_ptr<Object> > () = std::dynamic_pointer_cast<Object>(std::make_shared<IntegerObject>(IntegerObject(0)));  }
#line 1230 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 24:
#line 181 "parser.y"
                            {yylhs.value.as < std::shared_ptr<Object> > () = std::dynamic_pointer_cast<Object>(std::make_shared<BoolObject>(BoolObject(0)));  }
#line 1236 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 25:
#line 182 "parser.y"
                            {yylhs.value.as < std::shared_ptr<Object> > () = std::dynamic_pointer_cast<Object>(std::make_shared<IdentObject>(IdentObject(yystack_[0].value.as < std::string > ())));  }
#line 1242 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 26:
#line 186 "parser.y"
                            {yylhs.value.as < std::shared_ptr<Object> > () = std::dynamic_pointer_cast<Object>(std::make_shared<ArrayObject>(ArrayObject(yystack_[2].value.as < std::shared_ptr<Object> > ()))); }
#line 1248 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 27:
#line 190 "parser.y"
                                    {yylhs.value.as < StatementsList* > () = new StatementsList();  Location::GetInstance().SetLoc(yylhs.value.as < StatementsList* > (), driver.location);}
#line 1254 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 28:
#line 191 "parser.y"
                                    {yystack_[1].value.as < StatementsList* > ()->AddStatement(yystack_[0].value.as < Statement* > ()); yylhs.value.as < StatementsList* > () = yystack_[1].value.as < StatementsList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < StatementsList* > (), driver.location);}
#line 1260 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 29:
#line 195 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new AssertStatement(yystack_[2].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1266 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 30:
#line 196 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = yystack_[1].value.as < Declaration* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1272 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 31:
#line 197 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new OutStatement(yystack_[2].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1278 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 32:
#line 198 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new AssignStatement(yystack_[3].value.as < Lvalue* > (), yystack_[1].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1284 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 33:
#line 199 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new ScopeDeclStatement(yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1290 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 34:
#line 200 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new IfStatement(yystack_[4].value.as < Expression* > (), yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1296 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 35:
#line 201 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new IfElseStatement(yystack_[8].value.as < Expression* > (), yystack_[5].value.as < StatementsList* > (), yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1302 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 36:
#line 202 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new WhileStatement(yystack_[4].value.as < Expression* > (), yystack_[1].value.as < StatementsList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1308 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 37:
#line 203 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new ReturnStatement(yystack_[1].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1314 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 38:
#line 204 "parser.y"
                                                                            {yylhs.value.as < Statement* > () = new MethodInvokeStatement(yystack_[6].value.as < Expression* > (), yystack_[4].value.as < std::string > (), yystack_[2].value.as < ExprList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Statement* > (), driver.location);}
#line 1320 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 39:
#line 208 "parser.y"
                                {yylhs.value.as < Lvalue* > () = new SimpleLvalue(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Lvalue* > (), driver.location);}
#line 1326 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 40:
#line 209 "parser.y"
                                {yylhs.value.as < Lvalue* > () = new ArrayLvalue(yystack_[1].value.as < std::shared_ptr<Object> > (), yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Lvalue* > (), driver.location);}
#line 1332 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 41:
#line 210 "parser.y"
                                {yylhs.value.as < Lvalue* > () = new Lvalue(yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Lvalue* > (), driver.location);}
#line 1338 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 42:
#line 211 "parser.y"
                                {yylhs.value.as < Lvalue* > () = new ArrayElementLvalue(yystack_[3].value.as < std::string > (), yystack_[1].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Lvalue* > (), driver.location);}
#line 1344 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 43:
#line 215 "parser.y"
                            {yylhs.value.as < ExprList* > () = yystack_[0].value.as < ExprList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < ExprList* > (), driver.location);}
#line 1350 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 44:
#line 216 "parser.y"
                            {yylhs.value.as < ExprList* > () = yystack_[0].value.as < ExprList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < ExprList* > (), driver.location);}
#line 1356 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 45:
#line 220 "parser.y"
                            {yylhs.value.as < ExprList* > () = new ExprList();  Location::GetInstance().SetLoc(yylhs.value.as < ExprList* > (), driver.location);}
#line 1362 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 46:
#line 224 "parser.y"
                                    {yylhs.value.as < ExprList* > () = new ExprList(yystack_[0].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < ExprList* > (), driver.location);}
#line 1368 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 47:
#line 225 "parser.y"
                                    {yystack_[2].value.as < ExprList* > ()->AddExpr(yystack_[0].value.as < Expression* > ()); yylhs.value.as < ExprList* > () = yystack_[2].value.as < ExprList* > ();  Location::GetInstance().SetLoc(yylhs.value.as < ExprList* > (), driver.location);}
#line 1374 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 48:
#line 229 "parser.y"
                                                {yylhs.value.as < Expression* > () = new BinaryCallExpression(yystack_[2].value.as < Expression* > (), yystack_[1].value.as < BinaryOperator* > (), yystack_[0].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1380 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 49:
#line 230 "parser.y"
                                                {yylhs.value.as < Expression* > () = new IdentExpression(yystack_[0].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1386 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 50:
#line 231 "parser.y"
                                                {yylhs.value.as < Expression* > () = new NumberExpression(yystack_[0].value.as < int > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1392 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 51:
#line 232 "parser.y"
                                                {yylhs.value.as < Expression* > () = new UnarMinusExpression(yystack_[0].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1398 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 52:
#line 233 "parser.y"
                                                {yylhs.value.as < Expression* > () = new NotExpression(yystack_[0].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1404 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 53:
#line 234 "parser.y"
                                                {yylhs.value.as < Expression* > () = yystack_[1].value.as < Expression* > ();  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1410 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 54:
#line 235 "parser.y"
                                                {yylhs.value.as < Expression* > () = new BoolExpression(true);  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1416 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 55:
#line 236 "parser.y"
                                                {yylhs.value.as < Expression* > () = new BoolExpression(false);  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1422 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 56:
#line 237 "parser.y"
                                                {yylhs.value.as < Expression* > () = new ArrayGetExpression(yystack_[3].value.as < Expression* > (), yystack_[1].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1428 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 57:
#line 238 "parser.y"
                                                {yylhs.value.as < Expression* > () = new GetLengthExpression(yystack_[2].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1434 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 58:
#line 239 "parser.y"
                                                {yylhs.value.as < Expression* > () = new ArrayRvalueExpression(yystack_[3].value.as < std::shared_ptr<Object> > (), yystack_[1].value.as < Expression* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1440 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 59:
#line 240 "parser.y"
                                                {yylhs.value.as < Expression* > () = new IdentCreateExpression(yystack_[2].value.as < std::string > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1446 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 60:
#line 241 "parser.y"
                                                {yylhs.value.as < Expression* > () = new ThisExpression();  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1452 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 61:
#line 242 "parser.y"
                                                {yylhs.value.as < Expression* > () = new InvokeExpression(yystack_[5].value.as < Expression* > (), yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprList* > ());  Location::GetInstance().SetLoc(yylhs.value.as < Expression* > (), driver.location);}
#line 1458 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 62:
#line 246 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new AndOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1464 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 63:
#line 247 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new OrOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1470 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 64:
#line 248 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new LessOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1476 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 65:
#line 249 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new MoreOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1482 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 66:
#line 250 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new EqualOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1488 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 67:
#line 251 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new PlusOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1494 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 68:
#line 252 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new MinusOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1500 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 69:
#line 253 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new MulOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1506 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 70:
#line 254 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new DivOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1512 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;

  case 71:
#line 255 "parser.y"
            {yylhs.value.as < BinaryOperator* > () = new ProcOperator();  Location::GetInstance().SetLoc(yylhs.value.as < BinaryOperator* > (), driver.location);}
#line 1518 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"
    break;


#line 1522 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -57;

  const signed char parser::yytable_ninf_ = -42;

  const short
  parser::yypact_[] =
  {
     -22,   -26,   -57,    21,    11,     5,   -57,    25,    -7,   -57,
      28,    37,    32,   -57,    41,    -6,    56,   -57,    36,   -57,
     -57,   -57,   -16,    30,   -57,   -57,   -57,    66,    44,   -15,
      45,    69,    67,    68,    75,    78,    79,    80,   -57,   -57,
     -57,   -57,    39,    39,    39,    92,    -8,    55,    82,   -57,
      81,    88,    89,    42,    42,    42,   -57,    90,    96,   -57,
     -57,    97,    98,    99,    46,    42,   -57,    -2,   -57,     3,
      73,   561,   115,   -57,   105,   -57,   -57,   102,    39,   119,
     121,   -57,   579,   579,   417,   127,   -57,    42,    42,    42,
      42,   124,   122,   377,    42,    67,    68,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,    42,   -19,    42,
      42,   -57,   -57,    13,   101,   -57,   -57,     8,   -57,   -57,
     435,   453,   471,   489,   130,    42,   -57,   507,   525,   -57,
     125,   579,   397,   162,   -57,   -57,   197,   232,   132,   126,
     129,   131,   133,   -57,   543,   -57,   -57,    42,   -57,   -57,
     -57,   -57,    42,   -57,   -57,   -57,   -57,   -57,   579,   137,
     -57,   141,   138,   267,   302,   148,    42,   -57,   139,   -57,
     -57,   579,   156,   -57,   337,   -57
  };

  const signed char
  parser::yydefact_[] =
  {
       0,     0,     3,     0,     0,     2,     1,     0,     0,     4,
       0,     0,     0,     9,     0,     0,     0,     5,     0,    23,
      24,    25,     0,     0,     8,    10,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    11,
      12,    27,    18,    18,    18,     0,     0,     0,     0,    16,
      17,     0,     0,     0,     0,     0,    27,     0,     0,    54,
      55,     0,     0,     0,     0,     0,    60,    49,    50,     0,
       0,     0,     0,    28,     0,    19,    20,     0,     0,     0,
       0,    49,    51,    52,     0,     0,     6,     0,     0,     0,
       0,    25,     0,     0,     0,    39,    40,    68,    67,    69,
      70,    62,    63,    64,    65,    66,    71,     0,     0,     0,
       0,    30,    27,     0,     0,    27,    27,     0,    53,    33,
       0,     0,     0,     0,     0,     0,    37,     0,     0,    57,
       0,    48,     0,     0,    21,    22,     0,     0,     0,     0,
       0,     0,     0,    59,     0,    42,    56,    45,    32,    15,
      13,    14,    45,    31,    29,    27,    27,    58,    46,     0,
      43,    44,     0,     0,     0,    61,     0,    61,    34,    36,
      38,    47,     0,    27,     0,    35
  };

  const short
  parser::yypgoto_[] =
  {
     -57,   -13,    -5,   -57,   -57,   -57,   -57,   -46,    22,   -57,
     -57,   -29,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -56,
     140,   -57
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,    69,    70,   109,     9,     5,    15,    71,   159,   160,
     161,    48,    49,    50,    72,     2,    24,     3,    73,    45,
      74,    26
  };

  const short
  parser::yytable_[] =
  {
      85,   -41,    22,    31,    31,    29,     1,    82,    83,    84,
      23,    31,    17,    30,    51,    52,     4,    94,    18,    93,
     129,     6,    31,   130,    19,    20,    32,    36,     7,    46,
      46,    46,    31,     8,    75,    11,    21,    47,    47,    47,
     -25,   120,   121,   122,   123,    95,    53,   129,   127,    10,
     138,    92,    54,    12,    13,   134,   133,    55,    14,   136,
     137,   128,    28,   131,   132,   113,    19,    20,    16,    19,
      20,    27,    33,   114,    59,    60,    19,    20,    21,   144,
      64,    21,    34,    66,    81,    68,    35,    37,    91,    38,
      39,    40,    41,    42,    43,    44,    53,    76,    77,   163,
     164,   158,    54,    78,    79,    80,   158,    55,    86,    56,
      57,    87,    88,    89,    90,    96,    18,   174,   110,   112,
     171,    58,    19,    20,    59,    60,    61,    62,   111,    63,
      64,    53,    65,    66,    67,    68,   115,    54,   116,   124,
     147,   125,    55,   135,    56,   119,   143,   152,   155,   153,
     156,    18,   154,   165,   167,    25,    58,    19,    20,    59,
      60,    61,    62,   166,    63,    64,    53,    65,    66,    67,
      68,   170,    54,   173,   162,   172,     0,    55,     0,    56,
     149,     0,     0,     0,     0,     0,    18,     0,     0,     0,
       0,    58,    19,    20,    59,    60,    61,    62,     0,    63,
      64,    53,    65,    66,    67,    68,     0,    54,     0,     0,
       0,     0,    55,     0,    56,   150,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    58,    19,    20,    59,
      60,    61,    62,     0,    63,    64,    53,    65,    66,    67,
      68,     0,    54,     0,     0,     0,     0,    55,     0,    56,
     151,     0,     0,     0,     0,     0,    18,     0,     0,     0,
       0,    58,    19,    20,    59,    60,    61,    62,     0,    63,
      64,    53,    65,    66,    67,    68,     0,    54,     0,     0,
       0,     0,    55,     0,    56,   168,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    58,    19,    20,    59,
      60,    61,    62,     0,    63,    64,    53,    65,    66,    67,
      68,     0,    54,     0,     0,     0,     0,    55,     0,    56,
     169,     0,     0,     0,     0,     0,    18,     0,     0,     0,
       0,    58,    19,    20,    59,    60,    61,    62,     0,    63,
      64,    53,    65,    66,    67,    68,     0,    54,     0,     0,
       0,     0,    55,     0,    56,   175,     0,     0,     0,     0,
       0,    18,     0,     0,     0,     0,    58,    19,    20,    59,
      60,    61,    62,     0,    63,    64,     0,    65,    66,    67,
      68,    97,    98,    99,   100,   101,   102,     0,   103,   104,
     105,   106,     0,     0,     0,     0,   107,     0,   117,     0,
     126,    97,    98,    99,   100,   101,   102,     0,   103,   104,
     105,   106,     0,     0,     0,     0,   107,     0,   117,     0,
     148,    97,    98,    99,   100,   101,   102,     0,   103,   104,
     105,   106,     0,   118,     0,     0,   107,     0,   117,    97,
      98,    99,   100,   101,   102,     0,   103,   104,   105,   106,
       0,   139,     0,     0,   107,     0,   117,    97,    98,    99,
     100,   101,   102,     0,   103,   104,   105,   106,     0,   140,
       0,     0,   107,     0,   117,    97,    98,    99,   100,   101,
     102,     0,   103,   104,   105,   106,     0,   141,     0,     0,
     107,     0,   117,    97,    98,    99,   100,   101,   102,     0,
     103,   104,   105,   106,     0,   142,     0,     0,   107,     0,
     117,    97,    98,    99,   100,   101,   102,     0,   103,   104,
     105,   106,     0,     0,     0,     0,   107,   145,   117,    97,
      98,    99,   100,   101,   102,     0,   103,   104,   105,   106,
       0,     0,     0,     0,   107,   146,   117,    97,    98,    99,
     100,   101,   102,     0,   103,   104,   105,   106,     0,     0,
       0,     0,   107,   157,   117,    97,    98,    99,   100,   101,
     102,     0,   103,   104,   105,   106,     0,     0,     0,     0,
     107,     0,   108,    97,    98,    99,   100,   101,   102,     0,
     103,   104,   105,   106,     0,     0,     0,     0,   107,     0,
     117
  };

  const short
  parser::yycheck_[] =
  {
      56,     3,    15,    19,    19,    18,    28,    53,    54,    55,
      15,    19,    18,    18,    43,    44,    42,    19,    24,    65,
      39,     0,    19,    42,    30,    31,    42,    42,    17,    42,
      43,    44,    19,    28,    42,    42,    42,    42,    43,    44,
      42,    87,    88,    89,    90,    42,     4,    39,    94,    24,
      42,    64,    10,    25,    17,    42,   112,    15,    26,   115,
     116,   107,    26,   109,   110,    78,    30,    31,    27,    30,
      31,    15,    42,    78,    32,    33,    30,    31,    42,   125,
      38,    42,    16,    41,    42,    43,    42,    42,    42,    20,
      23,    23,    17,    15,    15,    15,     4,    42,    16,   155,
     156,   147,    10,    22,    16,    16,   152,    15,    18,    17,
      18,    15,    15,    15,    15,    42,    24,   173,     3,    17,
     166,    29,    30,    31,    32,    33,    34,    35,    23,    37,
      38,     4,    40,    41,    42,    43,    17,    10,    17,    15,
      15,    19,    15,    42,    17,    18,    16,    15,    17,    23,
      17,    24,    23,    16,    16,    15,    29,    30,    31,    32,
      33,    34,    35,    22,    37,    38,     4,    40,    41,    42,
      43,    23,    10,    17,   152,    36,    -1,    15,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      38,     4,    40,    41,    42,    43,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,     4,    40,    41,    42,
      43,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      38,     4,    40,    41,    42,    43,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,     4,    40,    41,    42,
      43,    -1,    10,    -1,    -1,    -1,    -1,    15,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,    37,
      38,     4,    40,    41,    42,    43,    -1,    10,    -1,    -1,
      -1,    -1,    15,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,    -1,    40,    41,    42,
      43,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,
      23,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,
      23,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    -1,    16,    -1,    -1,    19,    -1,    21,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      -1,    16,    -1,    -1,    19,    -1,    21,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    -1,    16,
      -1,    -1,    19,    -1,    21,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    -1,    16,    -1,    -1,
      19,    -1,    21,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    -1,    16,    -1,    -1,    19,    -1,
      21,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      13,    14,    -1,    -1,    -1,    -1,    19,    20,    21,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    13,    14,
      -1,    -1,    -1,    -1,    19,    20,    21,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    19,    20,    21,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      19,    -1,    21,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    13,    14,    -1,    -1,    -1,    -1,    19,    -1,
      21
  };

  const signed char
  parser::yystos_[] =
  {
       0,    28,    60,    62,    42,    50,     0,    17,    28,    49,
      24,    42,    25,    17,    26,    51,    27,    18,    24,    30,
      31,    42,    46,    47,    61,    65,    66,    15,    26,    46,
      47,    19,    42,    42,    16,    42,    42,    42,    20,    23,
      23,    17,    15,    15,    15,    64,    46,    47,    56,    57,
      58,    56,    56,     4,    10,    15,    17,    18,    29,    32,
      33,    34,    35,    37,    38,    40,    41,    42,    43,    46,
      47,    52,    59,    63,    65,    42,    42,    16,    22,    16,
      16,    42,    52,    52,    52,    64,    18,    15,    15,    15,
      15,    42,    46,    52,    19,    42,    42,     4,     5,     6,
       7,     8,     9,    11,    12,    13,    14,    19,    21,    48,
       3,    23,    17,    46,    47,    17,    17,    21,    16,    18,
      52,    52,    52,    52,    15,    19,    23,    52,    52,    39,
      42,    52,    52,    64,    42,    42,    64,    64,    42,    16,
      16,    16,    16,    16,    52,    20,    20,    15,    23,    18,
      18,    18,    15,    23,    23,    17,    17,    20,    52,    53,
      54,    55,    53,    64,    64,    16,    22,    16,    18,    18,
      23,    52,    36,    17,    64,    18
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    45,    62,    50,    50,    49,    60,    65,    65,    51,
      51,    66,    66,    61,    61,    61,    56,    56,    57,    58,
      58,    58,    58,    46,    46,    46,    47,    64,    64,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    59,
      59,    59,    59,    53,    53,    54,    55,    55,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      52,    52,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     2,     0,     2,     5,    13,     1,     1,     0,
       2,     3,     3,     9,     9,     9,     1,     1,     0,     2,
       2,     4,     4,     1,     1,     1,     3,     0,     2,     5,
       2,     5,     4,     3,     7,    11,     7,     3,     7,     2,
       2,     1,     4,     1,     1,     0,     1,     3,     3,     1,
       1,     2,     2,     3,     1,     1,     4,     3,     5,     4,
       1,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"=\"", "\"-\"", "\"+\"",
  "\"*\"", "\"/\"", "\"&&\"", "\"||\"", "\"!\"", "\"<\"", "\">\"",
  "\"==\"", "\"%\"", "\"(\"", "\")\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"",
  "\".\"", "\",\"", "\";\"", "\"public\"", "\"static\"", "\"void\"",
  "\"main\"", "\"class\"", "\"out\"", "\"int\"", "\"boolean\"", "\"true\"",
  "\"false\"", "\"assert\"", "\"if\"", "\"else\"", "\"while\"", "\"new\"",
  "\"length\"", "\"return\"", "\"this\"", "\"identifier\"", "\"number\"",
  "NEG", "$accept", "simple_type", "array_type", "binary_operator",
  "class", "classes", "declarations", "expr", "expr_list",
  "empty_expr_list", "some_expr_list", "formals", "empty_formals",
  "some_formals", "lvalue", "main_class", "method_declaration", "program",
  "statement", "statements", "declaration", "variable_declaration", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   123,   123,   126,   127,   131,   135,   139,   140,   144,
     145,   149,   150,   154,   155,   156,   163,   164,   168,   172,
     173,   174,   175,   180,   181,   182,   186,   190,   191,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   208,
     209,   210,   211,   215,   216,   220,   224,   225,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 2106 "/Users/iskandersagitov/Desktop/Study/Compilers/MINIJavaCompiler/Interpreter/parser.cpp"

#line 259 "parser.y"


void
yy::parser::error(const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
