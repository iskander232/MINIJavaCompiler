#include "ScopeLayer.h"

#include <iostream>

ScopeLayer::ScopeLayer(ScopeLayer *parent) : parent_(parent) {
  parent_->AddChild(this);
}

ScopeLayer::ScopeLayer() : parent_(nullptr) {}

void ScopeLayer::DeclareVariable(Symbol symbol) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::make_shared<BasicObject>(BasicObject(BasicType::Void));
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::Put(Symbol symbol, std::shared_ptr<BasicObject> value) {

  ScopeLayer *current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    current_layer->values_.find(symbol)->second = value;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

bool ScopeLayer::Has(Symbol symbol) {
  return values_.find(symbol) != values_.end();
}

std::shared_ptr<BasicObject> ScopeLayer::Get(Symbol symbol) {
  ScopeLayer *current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

ScopeLayer *ScopeLayer::GetChild(size_t index) {
  return children_[index];
}

size_t ScopeLayer::GetChildrenCount() {
  return children_.size();
}

void ScopeLayer::AddChild(ScopeLayer *child) {
  children_.push_back(child);
}

ScopeLayer *ScopeLayer::GetParent() const {
  return parent_;
}