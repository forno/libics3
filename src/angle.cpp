#include "ics3/angle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

ics::Angle ics::Angle::createDegree() noexcept {
  static const Angle DEGREE(-130, 130, &ics::Angle::rawDegree);
  return DEGREE;
}

ics::Angle ics::Angle::createRadian() noexcept {
  static const double limit = 130 * M_PI / 180;
  static const Angle RADIAN(-limit, limit, &ics::Angle::rawRadian);
  return RADIAN;
}

double ics::Angle::get() const noexcept {
  return data;
}

void ics::Angle::set(double angle) throw(std::invalid_argument) {
  try {
    checkValid(angle);
  } catch (const std::invalid_argument e) {
    throw e;
  }
  data = angle;
}

uint16_t ics::Angle::getRaw() const noexcept {
  return (this->*getRawFunc)();
}

ics::Angle::Angle(double min, double max, uint16_t (Angle::*getRawFunc)() const) noexcept
: min(min),
  max(max),
  getRawFunc(getRawFunc)
{}

uint16_t ics::Angle::rawDegree() const noexcept {
  return static_cast<uint16_t>(data * 800 / 27 + 7500);
}

uint16_t ics::Angle::rawRadian() const noexcept {
  return static_cast<uint16_t>(data / M_PI * 16000 / 3 + 7500);
}

void ics::Angle::checkValid(double input) const throw(std::invalid_argument) {
  if (input < min) throw std::invalid_argument("Too small angle");
  if (max < input) throw std::invalid_argument("Too big angle");
}
