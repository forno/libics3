#include"ics3/parameter.hpp"

#include<stdexcept>

unsigned char ics::Parameter::get() const noexcept {
  return data;
}

void ics::Parameter::set(unsigned char input) {
  if (input < min) throw std::invalid_argument {"Too small value"};
  if (max < input) throw std::invalid_argument {"Too big value"};
  data = input;
}

unsigned char ics::Parameter::getSc() const noexcept {
  return sc;
}
