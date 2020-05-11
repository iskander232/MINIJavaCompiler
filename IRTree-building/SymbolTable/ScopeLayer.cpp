#include "ScopeLayer.h"

#include <iostream>

#include "Types/UninitObject.h"

ScopeLayer::ScopeLayer(ScopeLayer*parent) : parent_(parent) {
  parent_->AddChild(this);
}

ScopeLayer::ScopeLayer() : parent_(nullptr) {}

void ScopeLayer::DeclareVariable(Symbol symbol) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::dynamic_pointer_cast<Object>(std::make_shared<UninitObject>(UninitObject()));
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::DeclareFunction(Symbol symbol, std::shared_ptr<FunctionObject> func) {
  if (functions_.find(symbol) != functions_.end()) {
    throw std::runtime_error("Function has declared");
  }

  functions_[symbol] = func;
}

void ScopeLayer::Put(Symbol symbol, std::shared_ptr<Object> value) {

  ScopeLayer* current_layer = this;

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

bool ScopeLayer::HasFunc(Symbol func_name) {
  return functions_.find(func_name) != functions_.end();
}

std::shared_ptr<Object> ScopeLayer::Get(Symbol symbol) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

std::shared_ptr<FunctionObject> ScopeLayer::GetFunc(Symbol func_name) {
  ScopeLayer* current_layer = this;

  while (!current_layer->HasFunc(func_name) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }

  if (current_layer->HasFunc(func_name)) {
    return current_layer->functions_.find(func_name)->second;
  } else {
    throw std::runtime_error("Function not declared");
  }
}

ScopeLayer* ScopeLayer::GetChild(size_t index) {
  return children_[index];
}

size_t ScopeLayer::GetChildrenCount() {
  return children_.size();
}

void ScopeLayer::AddChild(ScopeLayer* child) {
  children_.push_back(child);
}

ScopeLayer* ScopeLayer::GetParent() const {
  return parent_;
}