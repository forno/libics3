#include"ics3/angle.hpp"

#define _USE_MATH_DEFINES
#include<cmath>

ics::Angle ics::Angle::newRadian(double angle) noexcept {
  return Angle {16000.0 / 3.0 / M_PI, angle};
}

ics::Angle& ics::Angle::operator=(const Angle& rhs) noexcept {
  rawData = rhs.rawData;
  return *this;
}

double ics::Angle::get() const noexcept {
  return (rawData - 7500) / rawCalibration;
}

void ics::Angle::set(double angle) {
  setRaw(castToRaw(angle, rawCalibration)); // throw std::invalid_argument
}

uint16_t ics::Angle::getRaw() const noexcept {
  return rawData;
}

void ics::Angle::setRaw(uint16_t raw) {
  checkInvalidAngle(raw); // throw std::invalid_argument
  rawData = raw;
}
