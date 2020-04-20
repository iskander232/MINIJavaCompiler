#pragma once

#include "Symbol.h"
#include "Types/Object.h"

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <Types/BasicObject.h>

class ScopeLayer {
 public:
    explicit ScopeLayer(ScopeLayer* parent);
    ScopeLayer();
    void DeclareVariable(Symbol symbol);
    void Put(Symbol symbol, std::shared_ptr<BasicObject> value);
    std::shared_ptr<BasicObject> Get(Symbol symbol);
    bool Has(Symbol symbol);

    void AddChild(ScopeLayer* child);

    ScopeLayer* GetChild(size_t index);
    size_t GetChildrenCount();
    ScopeLayer* GetParent() const;
 private:
    std::unordered_map<Symbol, std::shared_ptr<BasicObject>> values_;
    std::unordered_map<Symbol, size_t> offsets_;
    std::vector<Symbol> symbols_;
    std::string name_;
    ScopeLayer* parent_;
    std::vector<ScopeLayer* > children_;
};