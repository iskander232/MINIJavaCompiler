#include "ScopeLayerTree.h"

#include <stdexcept>

ScopeLayerTree::ScopeLayerTree(ScopeLayer *root) : root_(root) {
  current_layer_ = root;
  offset_.push(0);
}

ScopeLayer *ScopeLayerTree::GetCurrentLayer() {
  return current_layer_;
}

void ScopeLayerTree::GoUp() {
  auto parent = current_layer_->GetParent();
  if (!parent) {
    throw std::runtime_error("It's uppest layer");
  }
  current_layer_ = parent;
  offset_.pop();
}

void ScopeLayerTree::GoDown() {
  if (offset_.top() >= current_layer_->GetChildrenCount()) {
    throw std::runtime_error("Can't go down");
  }
  current_layer_ = current_layer_->GetChild(offset_.top());
  offset_.push(0);
}

void ScopeLayerTree::GoNext() {
  size_t index = offset_.top();
  offset_.pop();
  offset_.push(index + 1);
}

void ScopeLayerTree::AddChildAndGoThere() {
  auto new_layer = new ScopeLayer(current_layer_);
  GoDown();
}

void ScopeLayerTree::ResetVisit() {
  while (!offset_.empty()){
    offset_.pop();
  }
  offset_.push(0);
}