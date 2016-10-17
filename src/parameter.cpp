#include"ics3/parameter.hpp"

#include<stdexcept>

void ics::Parameter::set(unsigned char input) {
  if (input < min) throw std::invalid_argument {"Too small value"};
  if (max < input) throw std::invalid_argument {"Too big value"};
  data = input;
}
