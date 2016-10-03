#include "ics3/angle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

ics::Angle ics::Angle::newDegree() noexcept {
  static const double limit = 130;
  static const Angle DEGREE(-limit, limit, 800.0 / 27.0);
  return DEGREE;
}

ics::Angle ics::Angle::newRadian() noexcept {
  static const double limit = 130 * M_PI / 180;
  static const Angle RADIAN(-limit, limit, 16000.0 / 3.0 / M_PI);
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
  return static_cast<uint16_t>(data * rawCalibration + 7500);
}

void ics::Angle::setRaw(uint16_t raw) throw(std::invalid_argument) {
  try {
    set((raw - 7500) / rawCalibration);
  } catch (std::invalid_argument e) {
    throw e;
  }
}

ics::Angle::Angle(double min, double max, double calibration) noexcept
: min(min),
  max(max),
  rawCalibration(calibration),
  data(0)
{}
