#include "ClassesList.h"

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
  return classes_list_[i];
}