#ifndef LIBICS3_ICS3_EEPPARAM_H_
#define LIBICS3_ICS3_EEPPARAM_H_

#include"ics3/check_invalid.hpp"
#include"ics3/baudrate.hpp"

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

    static constexpr EepParam stretch(uint16_t = 60);
    static constexpr EepParam speed(uint16_t = 127);
    static constexpr EepParam punch(uint16_t = 1);
    static constexpr EepParam deadBand(uint16_t = 2);
    static constexpr EepParam dumping(uint16_t = 40);
    static constexpr EepParam selfTimer(uint16_t = 250);
    static constexpr EepParam flag(uint16_t = 0x8C);
    static constexpr EepParam pulseMax(uint16_t = 11500);
    static constexpr EepParam pulseMin(uint16_t = 3500);
    static constexpr EepParam baudrate(uint16_t = 10);
    static constexpr EepParam temperature(uint16_t = 80);
    static constexpr EepParam current(uint16_t = 63);
    static constexpr EepParam response(uint16_t = 0);
    static constexpr EepParam userOffset(uint16_t = 0);
    static constexpr EepParam id(uint16_t = 0);
    static constexpr EepParam strech1(uint16_t = 60);
    static constexpr EepParam strech2(uint16_t = 60);
    static constexpr EepParam strech3(uint16_t = 60);

    constexpr uint16_t get() const noexcept;
    constexpr operator uint16_t() const noexcept;
    void set(uint16_t);
    EepParam& operator=(uint16_t);
    void write(std::array<uint8_t, 64>&) const noexcept;
    void read(const std::array<uint8_t, 64>&);
  private:
    constexpr explicit EepParam(
        size_t,
        size_t,
        uint16_t,
        uint16_t,
        uint16_t (*)(uint16_t, uint16_t, uint16_t),
        uint16_t
    );
    static constexpr uint16_t checkInvalidRange(uint16_t, uint16_t, uint16_t);
    static constexpr uint16_t checkInvalidEvenRange(uint16_t, uint16_t, uint16_t);
    static constexpr uint16_t checkInvalidFlag(uint16_t, uint16_t, uint16_t);
    static constexpr uint16_t checkInvalidBaudrate(uint16_t, uint16_t, uint16_t);
    static constexpr uint16_t checkInvalidOffset(uint16_t, uint16_t, uint16_t);

    const size_t offset;
    const size_t length;
    const uint16_t min;
    const uint16_t max;
    uint16_t (*const setFunc)(uint16_t, uint16_t, uint16_t);
    uint16_t data;
  };

  constexpr EepParam EepParam::stretch(uint16_t data) {
    return EepParam {2, 2, 2, 254, &EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::speed(uint16_t data) {
    return EepParam {4, 2, 1, 127, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::punch(uint16_t data) {
    return EepParam {6, 2, 0, 10, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::deadBand(uint16_t data) {
    return EepParam {8, 2, 0, 5, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::dumping(uint16_t data) {
    return EepParam {10, 2, 1, 255, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::selfTimer(uint16_t data) {
    return EepParam {12, 2, 10, 255, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::flag(uint16_t data) {
    return EepParam {14, 2, 0, 255, &EepParam::checkInvalidFlag, data};
  }

  constexpr EepParam EepParam::pulseMax(uint16_t data) {
    return EepParam {16, 4, 3500, 11500, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::pulseMin(uint16_t data) {
    return EepParam {20, 4, 3500, 11500, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::baudrate(uint16_t data) {
    return EepParam {26, 2, 0, 10, &EepParam::checkInvalidBaudrate, data};
  }

  constexpr EepParam EepParam::temperature(uint16_t data) {
    return EepParam {28, 2, 1, 127, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::current(uint16_t data) {
    return EepParam {30, 2, 1, 63, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::response(uint16_t data) {
    return EepParam {50, 2, 1, 5, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::userOffset(uint16_t data) {
    return EepParam {52, 2, static_cast<uint16_t>(-127), 127, &EepParam::checkInvalidOffset, data};
  }

  constexpr EepParam EepParam::id(uint16_t data) {
    return EepParam {56, 2, 0, 31, &EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::strech1(uint16_t data) {
    return EepParam {58, 2, 2, 254, &EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::strech2(uint16_t data) {
    return EepParam {60, 2, 2, 254, &EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::strech3(uint16_t data) {
    return EepParam {62, 2, 2, 254, &EepParam::checkInvalidEvenRange, data};
  }

  constexpr uint16_t EepParam::get() const noexcept {
    return data;
  }

  constexpr EepParam::operator uint16_t() const noexcept {
    return get();
  }

  inline void EepParam::set(uint16_t input) {
    data = (*setFunc)(input, min, max); // throw std::invalid_argument
  }

  inline EepParam& EepParam::operator=(uint16_t input) {
    set(input);
    return *this;
  }

  constexpr EepParam::EepParam(
      size_t offset,
      size_t length,
      uint16_t min,
      uint16_t max,
      uint16_t (*setFunc)(uint16_t, uint16_t, uint16_t),
      uint16_t data
  )
  : offset(offset),
    length(length),
    min(min),
    max(max),
    setFunc(setFunc),
    data(setFunc(data, min, max)) // throw std::invalid_argument
  {}

  constexpr uint16_t EepParam::checkInvalidRange(uint16_t input, uint16_t min, uint16_t max) {
    return ics::checkInvalidRange(input, min, max);
  }

  constexpr uint16_t EepParam::checkInvalidEvenRange(uint16_t input, uint16_t min, uint16_t max) {
    return input % 2 ?
           throw std::out_of_range {"Must even value"} :
           checkInvalidRange(input, min, max); // throw std::invalid_argument
  }

  constexpr uint16_t EepParam::checkInvalidFlag(uint16_t input, uint16_t, uint16_t) {
    return !(input & 0x04) ? throw std::out_of_range {"Eepparam(flag): Must up bits 0x04"} :
           ~(input | ~0x60) ? throw std::out_of_range {"Eepparam(flag): Must down bits 0x60"} :
           input;
  }

  constexpr uint16_t EepParam::checkInvalidBaudrate(uint16_t input, uint16_t, uint16_t) {
    return input == Baudrate::RATE115200().getRomData() ? input :
           //input == Baudrate::RATE625000().getRomData() ? input :
           //input == Baudrate::RATE1250000().getRomData() ? input :
           throw std::invalid_argument {"baudrate not exist"};
  }

  constexpr uint16_t EepParam::checkInvalidOffset(uint16_t input, uint16_t min, uint16_t max) {
    return input < max ? input : // this min < 0; min of uint16_t is 0
           min < input ? input : // this min < 0; input must bigger than min.
           throw std::out_of_range {"Eeprom(offset): range over"}; // min < input < max is failed
  }
}

#endif // LIBICS3_ICS3_EEPPARAM_H_
