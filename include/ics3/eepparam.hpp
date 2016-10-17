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

    static constexpr EepParam strech(uint16_t = 60) noexcept;
    static constexpr EepParam speed(uint16_t = 127) noexcept;
    static constexpr EepParam punch(uint16_t = 1) noexcept;
    static constexpr EepParam deadBand(uint16_t = 2) noexcept;
    static constexpr EepParam dumping(uint16_t = 40) noexcept;
    static constexpr EepParam selfTimer(uint16_t = 250) noexcept;
    static constexpr EepParam flag(uint16_t = 0x8C) noexcept;
    static constexpr EepParam pulseMax(uint16_t = 11500) noexcept;
    static constexpr EepParam pulseMin(uint16_t = 3500) noexcept;
    static constexpr EepParam baudrate(uint16_t = 10) noexcept;
    static constexpr EepParam temperature(uint16_t = 80) noexcept;
    static constexpr EepParam current(uint16_t = 63) noexcept;
    static constexpr EepParam response(uint16_t = 0) noexcept;
    static constexpr EepParam userOffset(uint16_t = 0) noexcept;
    static constexpr EepParam id(uint16_t = 0) noexcept;
    static constexpr EepParam strech1(uint16_t = 60) noexcept;
    static constexpr EepParam strech2(uint16_t = 60) noexcept;
    static constexpr EepParam strech3(uint16_t = 60) noexcept;

    constexpr uint16_t get() const noexcept;
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

  constexpr EepParam EepParam::strech(uint16_t data) noexcept {
    return EepParam {2, 2, 2, 254, &EepParam::setEven, data};
  }

  constexpr EepParam EepParam::speed(uint16_t data) noexcept {
    return EepParam {4, 2, 1, 127, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::punch(uint16_t data) noexcept {
    return EepParam {6, 2, 0, 10, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::deadBand(uint16_t data) noexcept {
    return EepParam {8, 2, 0, 5, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::dumping(uint16_t data) noexcept {
    return EepParam {10, 2, 1, 255, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::selfTimer(uint16_t data) noexcept {
    return EepParam {12, 2, 10, 255, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::flag(uint16_t data) noexcept {
    return EepParam {14, 2, 0, 255, &EepParam::setFlag, data};
  }

  constexpr EepParam EepParam::pulseMax(uint16_t data) noexcept {
    return EepParam {16, 4, 3500, 11500, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::pulseMin(uint16_t data) noexcept {
    return EepParam {20, 4, 3500, 11500, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::baudrate(uint16_t data) noexcept {
    return EepParam {26, 2, 0, 10, &EepParam::setBaudrate, data};
  }

  constexpr EepParam EepParam::temperature(uint16_t data) noexcept {
    return EepParam {28, 2, 1, 127, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::current(uint16_t data) noexcept {
    return EepParam {30, 2, 1, 63, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::response(uint16_t data) noexcept {
    return EepParam {50, 2, 1, 5, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::userOffset(uint16_t data) noexcept {
    return EepParam {52, 2, static_cast<uint16_t>(-127), 127, &EepParam::setOffset, data};
  }

  constexpr EepParam EepParam::id(uint16_t data) noexcept {
    return EepParam {56, 2, 0, 31, &EepParam::setNormal, data};
  }

  constexpr EepParam EepParam::strech1(uint16_t data) noexcept {
    return EepParam {58, 2, 2, 254, &EepParam::setEven, data};
  }

  constexpr EepParam EepParam::strech2(uint16_t data) noexcept {
    return EepParam {60, 2, 2, 254, &EepParam::setEven, data};
  }

  constexpr EepParam EepParam::strech3(uint16_t data) noexcept {
    return EepParam {62, 2, 2, 254, &EepParam::setEven, data};
  }

  constexpr uint16_t EepParam::get() const noexcept {
    return data;
  }

  inline void EepParam::set(uint16_t input) {
    (this->*setFunc)(input); // throw std::invalid_argument
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
