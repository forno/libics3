#include "ics3/angle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

ics::Angle ics::Angle::newDegree() noexcept {
  static const Angle DEGREE(-130, 130, &ics::Angle::getRawDegree);
  return DEGREE;
}

ics::Angle ics::Angle::newRadian() noexcept {
  static const double limit = 130 * M_PI / 180;
  static const Angle RADIAN(-limit, limit, &ics::Angle::getRawRadian);
  return RADIAN;
}

double ics::Angle::get() const noexcept {
  return data;
}

void ics::Angle::set(double angle) throw(std::invalid_argument) {
  if (angle < min) throw std::invalid_argument("Too small angle");
  if (max < angle) throw std::invalid_argument("Too big angle");
  data = angle;
}

uint16_t ics::Angle::getRaw() const noexcept {
  return (this->*getRawFunc)();
}

ics::Angle::Angle(double min, double max, uint16_t (Angle::*getRawFunc)() const noexcept) noexcept
: min(min),
  max(max),
  getRawFunc(getRawFunc),
  data(0)
{}

uint16_t ics::Angle::getRawDegree() const noexcept {
  return static_cast<uint16_t>(data * 800 / 27 + 7500);
}

uint16_t ics::Angle::getRawRadian() const noexcept {
  return static_cast<uint16_t>(data / M_PI * 16000 / 3 + 7500);
}

