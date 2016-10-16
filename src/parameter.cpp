#include "ics3/parameter.hpp"

#include <stdexcept>

ics::Parameter ics::Parameter::stretch() noexcept {
  return Parameter {0x01, 1, 127, 30};
}

ics::Parameter ics::Parameter::speed() noexcept {
  return Parameter {0x02, 1, 127, 127};
}

ics::Parameter ics::Parameter::current() noexcept {
  return Parameter {0x03, 0, 63, 63};
}

ics::Parameter ics::Parameter::temperature() noexcept {
  return Parameter {0x04, 1, 127, 80};
}

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

ics::Parameter::Parameter(unsigned char sc, unsigned char min, unsigned char max, unsigned char default_data) noexcept
: sc {sc},
  min {min},
  max {max},
  data {default_data}
{}
