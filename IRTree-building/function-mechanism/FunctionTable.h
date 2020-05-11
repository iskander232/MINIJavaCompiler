#pragma once

#include <SymbolTable/Symbol.h>
#include <Types/Object.h>
#include <Types/IdentObject.h>

#include <stack>

class FunctionTable {
 public:
  void Put(Symbol symbol, int);
  void CreateVariable(Symbol symbol);

  int Get(Symbol key);
  bool Has(Symbol key);

  void BeginScope();
  void EndScope();

 private:
  std::unordered_map<Symbol, std::stack<int>> values_;
  std::stack<Symbol> symbols_;
};



