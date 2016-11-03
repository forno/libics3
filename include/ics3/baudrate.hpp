#ifndef LIBICS3_ICS3_BAUDRATE_H_
#define LIBICS3_ICS3_BAUDRATE_H_

#include<termios.h>

namespace ics {
  class Baudrate {
  public:
    using type = uint8_t;
    static constexpr Baudrate RATE115200() noexcept;
    //static constexpr Baudrate RATE625000() noexcept;
    //static constexpr Baudrate RATE1250000() noexcept;
    constexpr type get() const noexcept;
    constexpr operator type() const noexcept;
    constexpr speed_t getSpeed() const noexcept;
  private:
    explicit constexpr Baudrate(type, speed_t) noexcept;

    const type romdata;
    const speed_t baudrate;
  };

  constexpr Baudrate Baudrate::RATE115200() noexcept {
    return Baudrate {10, B115200};
  }

  constexpr Baudrate::type Baudrate::get() const noexcept {
    return romdata;
  }

  constexpr Baudrate::operator Baudrate::type() const noexcept {
    return get();
  }

  constexpr speed_t Baudrate::getSpeed() const noexcept {
    return baudrate;
  }

  constexpr Baudrate::Baudrate(type romdata, speed_t baudrate) noexcept
  : romdata {romdata},
    baudrate {baudrate}
  {}
}

#endif // LIBICS3_ICS3_BAUDRATE_H_
