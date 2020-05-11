
#pragma once

#include <SymbolTable/Symbol.h>
#include <Types/FunctionObject.h>
#include <map>

using func_symbol = Symbol;
class FunctionStorage {
 public:
  static FunctionStorage &GetInstance();
  void Set(func_symbol symbol, std::shared_ptr<FunctionObject> function);
  std::shared_ptr<FunctionObject> Get(func_symbol symbol) const;
 private:
  FunctionStorage() = default;
  ~FunctionStorage() = default;
  FunctionStorage(const FunctionStorage &other) = delete;
  FunctionStorage &operator=(const FunctionStorage &) = delete;
  std::map<func_symbol, std::shared_ptr<FunctionObject>> functions_;
};


