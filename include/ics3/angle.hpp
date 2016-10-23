#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include"ics3/check_invalid.hpp"

#define _USE_MATH_DEFINES
#include<cmath>
#undef _USE_MATH_DEFINES

namespace ics {
  class ICS3;
  class Angle {
    friend ICS3;
  public:
    static constexpr Angle newDegree(double = 0.0);
    static constexpr Angle newRadian(double = 0.0);
    static constexpr Angle newSameUnit(const Angle&, double = 0.0);
    static constexpr Angle newCalibration(double, double = 0.0);
    static constexpr uint16_t MIN {3500};
    static constexpr uint16_t MID {7500};
    static constexpr uint16_t MAX {11500};

    Angle& operator=(const Angle&) noexcept;
    constexpr double get() const noexcept;
    constexpr operator double() const noexcept;
    void set(double);
    Angle& operator=(double);
    constexpr uint16_t getRaw() const noexcept;
    void setRaw(uint16_t);
  private:
    constexpr explicit Angle(double, double);
    static constexpr uint16_t castToRaw(double, double) noexcept;
    static constexpr uint16_t checkInvalidAngle(uint16_t);

    uint16_t rawData;
    const double rawCalibration;
  };

  constexpr Angle Angle::newDegree(double angle) {
    return Angle {800.0 / 27.0, angle};
  }

  constexpr Angle Angle::newRadian(double angle) {
    return Angle {16000.0 / 3.0 / M_PI, angle};
  }

  constexpr Angle Angle::newSameUnit(const Angle& unit, double angle) {
    return Angle {unit.rawCalibration, angle};
  }

  constexpr Angle Angle::newCalibration(double calibration, double angle) {
    return Angle {calibration, angle};
  }

  inline Angle& Angle::operator=(const Angle& rhs) noexcept {
    rawData = rhs.rawData;
    return *this;
  }

  constexpr double Angle::get() const noexcept {
    return (rawData - MID) / rawCalibration;
  }

  constexpr Angle::operator double() const noexcept {
    return get();
  }

  inline void Angle::set(double angle) {
    setRaw(castToRaw(angle, rawCalibration)); // throw std::invalid_argument
  }

  inline Angle& Angle::operator=(double angle) {
    set(angle);
    return *this;
  }

  constexpr uint16_t Angle::getRaw() const noexcept {
    return rawData;
  }

  inline void Angle::setRaw(uint16_t raw) {
    rawData = checkInvalidAngle(raw); // throw std::invalid_argument
  }

  constexpr Angle::Angle(double calibration, double angle)
  : rawData {checkInvalidAngle(castToRaw(angle, calibration))}, // throw std::invalid_argument
    rawCalibration {calibration}
  {}

  constexpr uint16_t Angle::castToRaw(double angle, double calibration) noexcept {
    return static_cast<uint16_t>(angle * calibration + MID);
  }

  constexpr uint16_t Angle::checkInvalidAngle(uint16_t raw) {
    return checkInvalidRange(raw, MIN, MAX);
  }
}

#endif // LIBICS3_ICS3_ANGLE_H_
