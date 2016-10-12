#include "ics3/parameter.hpp"

ics::Parameter ics::Parameter::stretch() noexcept {
  static const Parameter STRETCH(0x01, 1, 127, 30);
  return STRETCH;
}

ics::Parameter ics::Parameter::speed() noexcept {
  static const Parameter SPEED(0x02, 1, 127, 127);
  return SPEED;
}

ics::Parameter ics::Parameter::current() noexcept {
  static const Parameter CURRENT(0x03, 0, 63, 63);
  return CURRENT;
}

ics::Parameter ics::Parameter::temperature() noexcept {
  static const Parameter TEMPERATURE(0x04, 1, 127, 80);
  return TEMPERATURE;
}

unsigned char ics::Parameter::get() const noexcept {
  return data;
}

void ics::Parameter::set(unsigned char input) {
  if (input < min) throw std::invalid_argument("Too small value");
  if (max < input) throw std::invalid_argument("Too big value");
  data = input;
}

unsigned char ics::Parameter::getSc() const noexcept {
  return sc;
}

ics::Parameter::Parameter(unsigned char sc, unsigned char min, unsigned char max, unsigned char default_data) noexcept
: sc(sc),
  min(min),
  max(max),
  data(default_data)
{}
