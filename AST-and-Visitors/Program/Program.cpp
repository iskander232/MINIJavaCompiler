#include "Program.h"

Program::Program(Main *main, ClassesList *classes_list) : classes_list_(classes_list), main_(main) {}

void Program::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

Main *Program::GetMain() {
  return main_;
}

ClassesList *Program::GetClassesList() {
  return classes_list_;
}