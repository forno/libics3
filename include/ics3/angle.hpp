#ifndef LIBICS3_ICS3_ANGLE_H_
#define LIBICS3_ICS3_ANGLE_H_

namespace ics {

  class Angle {
  public:
    static Angle createDegree() noexcept;
    static Angle createRadian() noexcept;

    double get() const noexcept;
    void set() noexcept;
    uint16_t getRaw() const noexcept;
  private:
    explicit Angle(double, double, uint16_t (*)()) noexcept;
    uint16_t rawDegree() const noexcept;
    uint16_t rawRadian() const noexcept;

    const double min;
    const double max;
    uint16_t (*const getRawFunc)();
  };
}

#endif // LIBICS3_ICS3_ANGLE_H_
