#pragma once

#include <BaseElement/BaseElement.h>
#include <map>
#include <parser.hh>

class Location {
 public:
  static Location &GetInstance();

  void SetLoc(BaseElement* base_element, yy::location loc);
  void SetElement(BaseElement* element);
  yy::location LastLoc();

  Location(const Location &other) = delete;
  Location &operator=(const Location &) = delete;

 private:
  Location();
  ~Location() = default;
  BaseElement *last_element;
  std::map<BaseElement *, yy::location> locations_;
};