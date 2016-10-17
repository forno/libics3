#ifndef LIBICS3_ICS3_EEPPARAM_H_
#define LIBICS3_ICS3_EEPPARAM_H_

#include<array>

namespace ics {
  class EepParam {
  public:
    enum Flag : uint16_t {
      REVERSE =   0x1,
      FREE =      0x2,
      PWMINH =    0x8,
      ROLL_MODE = 0x10,
      SLAVE =     0x80
    };
    enum Baudrate : uint16_t {
      RATE115200 = 10,
      RATE625000 = 1,
      RATE1250000 = 0
    };

    static constexpr EepParam strech() noexcept;
    static constexpr EepParam speed() noexcept;
    static constexpr EepParam punch() noexcept;
    static constexpr EepParam deadBand() noexcept;
    static constexpr EepParam dumping() noexcept;
    static constexpr EepParam selfTimer() noexcept;
    static constexpr EepParam flag() noexcept;
    static constexpr EepParam pulseMax() noexcept;
    static constexpr EepParam pulseMin() noexcept;
    static constexpr EepParam baudrate() noexcept;
    static constexpr EepParam temperature() noexcept;
    static constexpr EepParam current() noexcept;
    static constexpr EepParam response() noexcept;
    static constexpr EepParam userOffset() noexcept;
    static constexpr EepParam id() noexcept;
    static constexpr EepParam strech1() noexcept;
    static constexpr EepParam strech2() noexcept;
    static constexpr EepParam strech3() noexcept;

    uint16_t get() const noexcept;
    void set(uint16_t);
    void write(std::array<unsigned char, 64>&) const noexcept;
    void read(const std::array<unsigned char, 64>&);
  private:
    constexpr explicit EepParam(
        size_t,
        size_t,
        uint16_t,
        uint16_t,
        void (EepParam::*)(uint16_t),
        uint16_t
    ) noexcept;
    void setNormal(uint16_t);
    void setEven(uint16_t);
    void setFlag(uint16_t);
    void setBaudrate(uint16_t);
    void setOffset(uint16_t);

    const size_t offset;
    const size_t length;
    const uint16_t min;
    const uint16_t max;
    void (EepParam::*const setFunc)(uint16_t);
    uint16_t data;
  };

  constexpr EepParam EepParam::strech() noexcept {
    return EepParam {2, 2, 2, 254, &EepParam::setEven, 60};
  }

  constexpr EepParam EepParam::speed() noexcept {
    return EepParam {4, 2, 1, 127, &EepParam::setNormal, 127};
  }

  constexpr EepParam EepParam::punch() noexcept {
    return EepParam {6, 2, 0, 10, &EepParam::setNormal, 1};
  }

  constexpr EepParam EepParam::deadBand() noexcept {
    return EepParam {8, 2, 0, 5, &EepParam::setNormal, 2};
  }

  constexpr EepParam EepParam::dumping() noexcept {
    return EepParam {10, 2, 1, 255, &EepParam::setNormal, 40};
  }

  constexpr EepParam EepParam::selfTimer() noexcept {
    return EepParam {12, 2, 10, 255, &EepParam::setNormal, 250};
  }

  constexpr EepParam EepParam::flag() noexcept {
    return EepParam {14, 2, 0, 255, &EepParam::setFlag, 0x8C};
  }

  constexpr EepParam EepParam::pulseMax() noexcept {
    return EepParam {16, 4, 3500, 11500, &EepParam::setNormal, 11500};
  }

  constexpr EepParam EepParam::pulseMin() noexcept {
    return EepParam {20, 4, 3500, 11500, &EepParam::setNormal, 3500};
  }

  constexpr EepParam EepParam::baudrate() noexcept {
    return EepParam {26, 2, 0, 10, &EepParam::setBaudrate, 10};
  }

  constexpr EepParam EepParam::temperature() noexcept {
    return EepParam {28, 2, 1, 127, &EepParam::setNormal, 80};
  }

  constexpr EepParam EepParam::current() noexcept {
    return EepParam {30, 2, 1, 63, &EepParam::setNormal, 63};
  }

  constexpr EepParam EepParam::response() noexcept {
    return EepParam {50, 2, 1, 5, &EepParam::setNormal, 3};
  }

  constexpr EepParam EepParam::userOffset() noexcept {
    return EepParam {52, 2, static_cast<uint16_t>(-127), 127, &EepParam::setOffset, 0};
  }

  constexpr EepParam EepParam::id() noexcept {
    return EepParam {56, 2, 0, 31, &EepParam::setNormal, 0};
  }

  constexpr EepParam EepParam::strech1() noexcept {
    return EepParam {58, 2, 2, 254, &EepParam::setEven, 60};
  }

  constexpr EepParam EepParam::strech2() noexcept {
    return EepParam {60, 2, 2, 254, &EepParam::setEven, 60};
  }

  constexpr EepParam EepParam::strech3() noexcept {
    return EepParam {62, 2, 2, 254, &EepParam::setEven, 60};
  }

  constexpr EepParam::EepParam(
      size_t offset,
      size_t length,
      uint16_t min,
      uint16_t max,
      void (EepParam::*setFunc)(uint16_t),
      uint16_t default_data
  ) noexcept
  : offset(offset),
    length(length),
    min(min),
    max(max),
    setFunc(setFunc),
    data(default_data)
  {}
}

#endif // LIBICS3_ICS3_EEPPARAM_H_
