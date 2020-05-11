#include "ScopeLayerTree.h"

ScopeLayerTree::ScopeLayerTree(ScopeLayer *root) : root_(root) {}

ScopeLayerTree::~ScopeLayerTree() {

}

ScopeLayerTree::ScopeLayerTree(const ScopeLayerTree &other) {
  root_ = other.root_;
  layer_mapping_ = other.layer_mapping_;
}

void ScopeLayerTree::AddMapping(Symbol name, ScopeLayer* layer) {
  if (layer_mapping_.find(name) != layer_mapping_.end()) {
    throw std::runtime_error("Function has already been declared");
  }
  layer_mapping_[name] = layer;
}

ScopeLayer* ScopeLayerTree::GetFunctionScopeByName(Symbol name) {
  if (layer_mapping_.find(name) == layer_mapping_.end()) {
    throw std::runtime_error("No such function");
  }
  return layer_mapping_[name];
}

std::shared_ptr<Object> ScopeLayerTree::Get(Symbol symbol) {
  return root_->Get(symbol);
}