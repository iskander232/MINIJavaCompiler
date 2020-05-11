#pragma once

#include "Symbol.h"
#include "Types/Object.h"
#include <Types/FunctionObject.h>

#include <unordered_map>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <Types/Object.h>

 class ScopeLayer{
 public:
  explicit ScopeLayer(ScopeLayer* parent);
  ScopeLayer();
  void DeclareVariable(Symbol symbol);
  void DeclareFunction(Symbol symbol, std::shared_ptr<FunctionObject> func);
  void Put(Symbol symbol, std::shared_ptr<Object> value);
  std::shared_ptr<Object> Get(Symbol symbol);
  std::shared_ptr<FunctionObject> GetFunc(Symbol func_name);
  bool Has(Symbol symbol);
  bool HasFunc(Symbol func_name);

  void AddChild(ScopeLayer* child);

  ScopeLayer* GetChild(size_t index);

  size_t GetChildrenCount();
  ScopeLayer* GetParent() const;
 private:
  std::unordered_map<Symbol, std::shared_ptr<Object>> values_;
  std::map<Symbol, std::shared_ptr<FunctionObject>> functions_;
  std::unordered_map<Symbol, size_t> offsets_;
  std::vector<Symbol> symbols_;
  std::string name_;
  ScopeLayer* parent_;
  std::vector<ScopeLayer*> children_;
};