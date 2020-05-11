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

  void AddMapping(Symbol name, ScopeLayer* layer);

  ScopeLayer* GetFunctionScopeByName(Symbol name);
 private:
  std::map<Symbol, ScopeLayer*> layer_mapping_;

};