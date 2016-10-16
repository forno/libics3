#include "ics3/angle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

ics::Angle ics::Angle::newDegree(double angle) noexcept {
  return Angle(800.0 / 27.0, angle);
}

ics::Angle ics::Angle::newRadian(double angle) noexcept {
  return Angle(16000.0 / 3.0 / M_PI, angle);
}

const uint16_t ics::Angle::MIN = 3500;
const uint16_t ics::Angle::MAX = 11500;

ics::Angle& ics::Angle::operator=(const Angle& rhs) noexcept {
  rawData = rhs.rawData;
  return *this;
}

double ics::Angle::get() const noexcept {
  return (rawData - 7500) / rawCalibration;
}

void ics::Angle::set(double angle) {
  setRaw(static_cast<uint16_t>(angle * rawCalibration + 7500)); // throw std::invalid_argument
}

uint16_t ics::Angle::getRaw() const noexcept {
  return rawData;
}

void ics::Angle::setRaw(uint16_t raw) {
  if (raw < MIN) throw std::invalid_argument("Too min angle");
  if (MAX < raw) throw std::invalid_argument("Too big angle");
  rawData = raw;
}

ics::Angle::Angle(double calibration, double angle) noexcept
: rawCalibration(calibration),
  rawData(angle * calibration + 7500)
{}
