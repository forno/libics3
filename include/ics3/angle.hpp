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
  private:
    Angle(double, double, uint16_t (Angle::*)() const noexcept) noexcept;
    uint16_t getRawDegree() const noexcept;
    uint16_t getRawRadian() const noexcept;

    const double min;
    const double max;
    uint16_t (Angle::*const getRawFunc)() const noexcept; // no new to no declaration of destructor, copy, etc...
    double data;
  };
}

#endif // LIBICS3_ICS3_ANGLE_H_
