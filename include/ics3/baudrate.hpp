#ifndef LIBICS3_ICS3_BAUDRATE_H_
#define LIBICS3_ICS3_BAUDRATE_H_

#include<termios.h>

namespace ics {
  class Baudrate {
  public:
    static constexpr Baudrate RATE115200() noexcept;
    //static constexpr Baudrate RATE625000() noexcept;
    //static constexpr Baudrate RATE1250000() noexcept;
    constexpr speed_t getSpeed() const noexcept;
    constexpr operator speed_t() const noexcept;
    constexpr uint16_t getRomData() const noexcept;
    constexpr operator uint16_t() const noexcept;
  private:
    explicit constexpr Baudrate(speed_t, uint16_t) noexcept;

    const speed_t baudrate;
    const uint16_t romdata;
  };

  constexpr Baudrate Baudrate::RATE115200() noexcept {
    return Baudrate {B115200, 10};
  }

  constexpr speed_t Baudrate::getSpeed() const noexcept {
    return baudrate;
  }

  constexpr Baudrate::operator speed_t() const noexcept {
    return getSpeed();
  }

  constexpr uint16_t Baudrate::getRomData() const noexcept {
    return romdata;
  }

  constexpr Baudrate::operator uint16_t() const noexcept {
    return getRomData();
  }

  constexpr Baudrate::Baudrate(speed_t baudrate, uint16_t romdata) noexcept
  : baudrate {baudrate},
    romdata {romdata}
  {}
}

#endif // LIBICS3_ICS3_BAUDRATE_H_
