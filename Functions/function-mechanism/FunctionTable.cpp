#include <iostream>
#include "FunctionTable.h"


void FunctionTable::Put(Symbol symbol, int value) {
  if (values_.find(symbol) == values_.end()) {
    throw std::runtime_error("Value doesn't exist");
  }
  values_[symbol].pop();
  values_[symbol].push(value);
  symbols_.push(symbol);
}

int FunctionTable::Get(Symbol symbol) {
  if (values_.find(symbol) == values_.end()) {
    throw std::runtime_error("Value doesn't exist");
  }
  return values_[symbol].top();
}

bool FunctionTable::Has(Symbol key) {
  return values_.find(key) != values_.end();
}

void FunctionTable::CreateVariable(Symbol symbol) {
  if (values_.find(symbol) == values_.end()) {
    values_[symbol] = std::stack<int>();
  }
  values_[symbol].push(0);
}

void FunctionTable::BeginScope() {
  symbols_.push(Symbol("{"));
}

void FunctionTable::EndScope() {
  while (symbols_.top() != Symbol("{")) {
    Symbol symbol = symbols_.top();

    values_[symbol].pop();
    if (values_[symbol].empty()) {
      values_.erase(symbol);
    }
    symbols_.pop();
  }
  symbols_.pop();
}