#include "Program.h"
#include <Location/Location.h>

Program::Program(Main *main, ClassesList *classes_list) : classes_list_(classes_list), main_(main) {}

void Program::Accept(Visitor *visitor) {
  Location::GetInstance().SetElement(dynamic_cast<BaseElement*>(this));
  visitor->Visit(this);
}

Main *Program::GetMain() {
  return main_;
}

ClassesList *Program::GetClassesList() {
  return classes_list_;
}