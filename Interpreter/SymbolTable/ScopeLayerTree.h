#pragma once

#include "ScopeLayer.h"

#include <stack>

class ScopeLayerTree {
 public:
  explicit ScopeLayerTree(ScopeLayer *root);
  ScopeLayerTree(const ScopeLayerTree &other);

  std::shared_ptr<Object> Get(Symbol symbol);
  ScopeLayer *root_;
  ~ScopeLayerTree();

  void AddMapping(std::pair<Symbol, Symbol> name, ScopeLayer* layer);

  ScopeLayer* GetFunctionScopeByName(std::pair<Symbol, Symbol> name);
 private:
  std::map<std::pair<Symbol, Symbol>, ScopeLayer*> layer_mapping_;

};