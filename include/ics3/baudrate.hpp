#ifndef LIBICS3_ICS3_BAUDRATE_H_
#define LIBICS3_ICS3_BAUDRATE_H_

#include<termios.h>

namespace ics {
  class Baudrate {
  public:
    static constexpr const Baudrate RATE115200() noexcept;
    //static constexpr Baudrate RATE625000() noexcept;
    //static constexpr Baudrate RATE1250000() noexcept;
    constexpr uint16_t get() const noexcept;
    constexpr operator uint16_t() const noexcept;
    constexpr speed_t getSpeed() const noexcept;
  private:
    explicit constexpr Baudrate(uint16_t, speed_t) noexcept;

    const uint16_t romdata;
    const speed_t baudrate;
  };

  constexpr const Baudrate Baudrate::RATE115200() noexcept {
    return Baudrate {10, B115200};
  }

  constexpr uint16_t Baudrate::get() const noexcept {
    return romdata;
  }

  constexpr Baudrate::operator uint16_t() const noexcept {
    return get();
  }

  constexpr speed_t Baudrate::getSpeed() const noexcept {
    return baudrate;
  }

  constexpr Baudrate::Baudrate(uint16_t romdata, speed_t baudrate) noexcept
  : romdata {romdata},
    baudrate {baudrate}
  {}
}

#endif // LIBICS3_ICS3_BAUDRATE_H_
