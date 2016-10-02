#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

#include <stdexcept>

namespace ics {
  class Angle {
  public:
    static Angle newDegree() noexcept;
    static Angle newRadian() noexcept;

    double get() const noexcept;
    void set(double) throw(std::invalid_argument);
    uint16_t getRaw() const noexcept;
    void setRaw(uint16_t) throw(std::invalid_argument);
  private:
    Angle(double, double, double) noexcept;

    const double min;
    const double max;
    const double rawCalibration;
    double data;
  };
}

#endif // LIBICS3_ICS3_ANGLE_H_
