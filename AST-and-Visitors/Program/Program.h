#pragma once

#include "BaseElement/BaseElement.h"
#include "Classes/ClassesList.h"
#include "Main/Main.h"

class Program : public BaseElement {
 public:
  Program(Main *main_, ClassesList *classes_list);
  Main *GetMain();
  ClassesList *GetClassesList();
  void Accept(Visitor *visitor) override;
 private:
  ClassesList *classes_list_;
  Main *main_;
};