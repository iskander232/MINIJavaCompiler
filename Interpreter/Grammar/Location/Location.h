#pragma once

#include <BaseElement/BaseElement.h>
#include <map>
#include <Grammar/parser.hh>
#include <stack>

class Location {
 public:
  static Location &GetInstance();

  void SetLoc(BaseElement* base_element, yy::location loc);
  void SetPrevLoc();
  void SetElement(BaseElement* element);
  yy::location LastLoc();

  Location(const Location &other) = delete;
  Location &operator=(const Location &) = delete;

 private:
  Location() = default;
  ~Location() = default;
  std::stack<BaseElement*> element_;
  std::map<BaseElement *, yy::location> locations_;
};