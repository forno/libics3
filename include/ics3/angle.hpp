#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include <stdexcept>

namespace ics {
  class Angle {
  public:
    static Angle newDegree(double = 0.0) noexcept;
    static Angle newRadian(double = 0.0) noexcept;
    static const uint16_t MIN;
    static const uint16_t MAX;

    double get() const noexcept;
    void set(double);
    uint16_t getRaw() const noexcept;
    void setRaw(uint16_t);
  private:
    Angle(double, double) noexcept;

    const double rawCalibration;
    uint16_t rawData;
  };
}

#endif // LIBICS3_ICS3_ANGLE_H_
