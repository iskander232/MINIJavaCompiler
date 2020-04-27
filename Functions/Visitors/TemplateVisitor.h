#pragma once

#include "Visitor.h"
#include "BaseElement/BaseElement.h"
template<typename T>
class TemplateVisitor : public Visitor {
 public:
    T Accept(BaseElement* element);
 protected:
    T tos_value_;

};