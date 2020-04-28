#include "ClassesList.h"
#include <Location/Location.h>

void ClassesList::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

void ClassesList::AddClass(Class *clas) {
  classes_list_.push_back(clas);
}

size_t ClassesList::GetSize() {
  return classes_list_.size();
}

Class * ClassesList::GetIth(int i) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  return classes_list_[i];
}