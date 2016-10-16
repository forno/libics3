#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include<stdexcept>

namespace ics {
  class Angle {
  public:
    static constexpr Angle newDegree(double = 0.0) noexcept;
    static Angle newRadian(double = 0.0) noexcept;
    static constexpr uint16_t MIN {3500};
    static constexpr uint16_t MAX {11500};

    Angle& operator=(const Angle&) noexcept;

    double get() const noexcept;
    void set(double);
    uint16_t getRaw() const noexcept;
    void setRaw(uint16_t);
  private:
    constexpr explicit Angle(double, double);
    static constexpr uint16_t castToRaw(double, double) noexcept;
    static constexpr uint16_t checkInvalidAngle(uint16_t);

    uint16_t rawData;
    const double rawCalibration;
  };

  constexpr Angle Angle::newDegree(double angle) noexcept {
    return Angle {800.0 / 27.0, angle};
  }

  constexpr Angle::Angle(double calibration, double angle)
  : rawData {checkInvalidAngle(castToRaw(angle, calibration))},
    rawCalibration {calibration}
  {}

  constexpr inline uint16_t Angle::castToRaw(double angle, double calibration) noexcept {
    return static_cast<uint16_t>(angle * calibration + 7500);
  }

  constexpr uint16_t Angle::checkInvalidAngle(uint16_t raw) {
    return raw < ics::Angle::MIN ? throw std::invalid_argument {"Too small angle"} :
           ics::Angle::MAX < raw ? throw std::invalid_argument {"Too big angle"} :
           raw;
  }
}

#endif // LIBICS3_ICS3_ANGLE_H_
