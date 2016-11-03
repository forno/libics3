#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include"ics3/check_invalid.hpp"

namespace ics {
  class ICS3;
  class Angle {
    friend ICS3; // for touch setRaw
  public:
    using rawType = uint16_t;
    static constexpr Angle newDegree(double = 0.0);
    static constexpr Angle newRadian(double = 0.0);
    static constexpr Angle newSameUnit(const Angle&, double = 0.0);
    static constexpr Angle newCalibration(double, double = 0.0);
    static constexpr rawType MIN {3500};
    static constexpr rawType MID {7500};
    static constexpr rawType MAX {11500};
    static constexpr double PI {3.141592653589793};

    Angle(const Angle&) noexcept = default;
    Angle& operator=(const Angle&) noexcept;
    constexpr double get() const noexcept;
    constexpr operator double() const noexcept;
    void set(double);
    Angle& operator=(double);
    constexpr rawType getRaw() const noexcept;
    void setRaw(rawType);
  private:
    constexpr explicit Angle(double, double);
    static constexpr rawType castToRaw(double, double) noexcept;
    static constexpr rawType checkInvalidAngle(rawType);

    rawType rawData;
    const double rawCalibration;
  };

  constexpr Angle Angle::newDegree(double angle) {
    return Angle {800.0 / 27.0, angle};
  }

  constexpr Angle Angle::newRadian(double angle) {
    return Angle {16000.0 / 3.0 / PI, angle};
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
    setRaw(castToRaw(rawCalibration, angle)); // throw std::out_of_range
  }

  inline Angle& Angle::operator=(double angle) {
    set(angle);
    return *this;
  }

  constexpr Angle::rawType Angle::getRaw() const noexcept {
    return rawData;
  }

  inline void Angle::setRaw(rawType raw) {
    rawData = checkInvalidAngle(raw); // throw std::out_of_range
  }

  constexpr Angle::Angle(double calibration, double angle)
  : rawData {checkInvalidAngle(castToRaw(calibration, angle))}, // throw std::out_of_range
    rawCalibration {calibration}
  {}

  constexpr Angle::rawType Angle::castToRaw(double calibration, double angle) noexcept {
    return static_cast<rawType>((calibration * angle) + MID);
  }

  constexpr Angle::rawType Angle::checkInvalidAngle(rawType raw) {
    return checkInvalidRange(raw, MIN, MAX);
  }
}

#endif // LIBICS3_ICS3_ANGLE_H_
