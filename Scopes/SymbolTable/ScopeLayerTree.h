#pragma once

#include "ScopeLayer.h"

#include <stack>

class ScopeLayerTree {
 public:
    explicit ScopeLayerTree(ScopeLayer* root);
    void GoDown();
    void GoUp();
    void GoNext();
    void AddChildAndGoThere();
    ScopeLayer* GetCurrentLayer();
    void ResetVisit();
 public:
    ScopeLayer* root_;
    ScopeLayer* current_layer_;
    std::stack<size_t> offset_;
};