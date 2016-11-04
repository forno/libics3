#ifndef LIBICS3_ICS3_EEPPARAM_H_
#define LIBICS3_ICS3_EEPPARAM_H_

#include"ics3/baudrate.hpp"
#include"ics3/check_invalid.hpp"

#include<array>

namespace ics {
  class EepParam {
  public:
    using type = uint16_t;
    using TargetContainer = std::array<uint8_t, 64>;
    using size_type = TargetContainer::size_type;
    using InvalidChecker = type (&)(type, type, type);
    enum Flag : type {
      REVERSE =   0x01,
      FREE =      0x02,
      PWMINH =    0x08,
      ROLL_MODE = 0x10,
      SLAVE =     0x80
    };
    static constexpr int byteSize {4};
    static constexpr type mask {0xF};

    static constexpr EepParam stretch(type = 60);
    static constexpr EepParam speed(type = 127);
    static constexpr EepParam punch(type = 1);
    static constexpr EepParam deadBand(type = 2);
    static constexpr EepParam dumping(type = 40);
    static constexpr EepParam selfTimer(type = 250);
    static constexpr EepParam flag(type = 0x8C);
    static constexpr EepParam pulseMax(type = 11500);
    static constexpr EepParam pulseMin(type = 3500);
    static constexpr EepParam baudrate(type = 10);
    static constexpr EepParam temperature(type = 80);
    static constexpr EepParam current(type = 63);
    static constexpr EepParam response(type = 0);
    static constexpr EepParam userOffset(type = 0);
    static constexpr EepParam id(type = 0);
    static constexpr EepParam strech1(type = 60);
    static constexpr EepParam strech2(type = 60);
    static constexpr EepParam strech3(type = 60);
    static constexpr EepParam newEepParam(const EepParam&, type);

    constexpr type get() const noexcept;
    constexpr operator type() const noexcept;
    void set(type);
    EepParam& operator=(type);
    void read(const TargetContainer&);
    void write(TargetContainer&) const noexcept;
  private:
    constexpr EepParam( // non explicit, user cannot touch this
        size_type,
        size_type,
        type,
        type,
        InvalidChecker,
        type);
    static constexpr type checkInvalidRange(type, type, type);
    static constexpr type checkInvalidEvenRange(type, type, type);
    static constexpr type checkInvalidFlag(type, type, type);
    static constexpr type checkInvalidBaudrate(type, type, type);
    static constexpr type checkInvalidOffset(type, type, type);

    const size_type offset;
    const size_type length;
    const type min;
    const type max;
    InvalidChecker setFunc;
    type data;
  };

  constexpr EepParam EepParam::stretch(type data) {
    return {2, 2, 2, 254, EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::speed(type data) {
    return {4, 2, 1, 127, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::punch(type data) {
    return {6, 2, 0, 10, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::deadBand(type data) {
    return {8, 2, 0, 5, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::dumping(type data) {
    return {10, 2, 1, 255, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::selfTimer(type data) {
    return {12, 2, 10, 255, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::flag(type data) {
    return {14, 2, 0, 255, EepParam::checkInvalidFlag, data};
  }

  constexpr EepParam EepParam::pulseMax(type data) {
    return {16, 4, 3500, 11500, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::pulseMin(type data) {
    return {20, 4, 3500, 11500, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::baudrate(type data) {
    return {26, 2, 0, 10, EepParam::checkInvalidBaudrate, data};
  }

  constexpr EepParam EepParam::temperature(type data) {
    return {28, 2, 1, 127, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::current(type data) {
    return {30, 2, 1, 63, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::response(type data) {
    return {50, 2, 1, 5, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::userOffset(type data) {
    return {52, 2, 0x81, 127, EepParam::checkInvalidOffset, data}; // 0x81 is -127 on uint8_t type
  }

  constexpr EepParam EepParam::id(type data) {
    return {56, 2, 0, 31, EepParam::checkInvalidRange, data};
  }

  constexpr EepParam EepParam::strech1(type data) {
    return {58, 2, 2, 254, EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::strech2(type data) {
    return {60, 2, 2, 254, EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::strech3(type data) {
    return {62, 2, 2, 254, EepParam::checkInvalidEvenRange, data};
  }

  constexpr EepParam EepParam::newEepParam(const EepParam& paramType, type data) {
    return {paramType.offset, paramType.length, paramType.min, paramType.max, paramType.setFunc, data};
  }

  constexpr EepParam::type EepParam::get() const noexcept {
    return data;
  }

  constexpr EepParam::operator type() const noexcept {
    return get();
  }

  inline void EepParam::set(type input) {
    data = setFunc(input, min, max); // throw std::invalid_argument, std::out_of_range
  }

  inline EepParam& EepParam::operator=(type input) {
    set(input);
    return *this;
  }

  inline void EepParam::read(const TargetContainer& src) {
    type result {0};
    const size_type loopend = offset + length;
    for (size_type i {offset}; i < loopend; ++i) {
      result <<= byteSize;
      result |= src[i] & mask;
    }
    set(result); // throw std::invalid_argument, std::out_of_range
  }

  inline void EepParam::write(TargetContainer& dest) const noexcept {
    type nowData {data};
    for (size_type i {offset + length - 1}; i >= offset; --i) {
      dest[i] = nowData & mask;
      nowData >>= byteSize;
    }
  }

  constexpr EepParam::EepParam(
      size_type offset,
      size_type length,
      type min,
      type max,
      InvalidChecker setFunc,
      type data)
  : offset(offset),
    length(length),
    min(min),
    max(max),
    setFunc(setFunc),
    data(setFunc(data, min, max)) // throw std::invalid_argument, std::out_of_range
  {}

  constexpr EepParam::type EepParam::checkInvalidRange(type input, type min, type max) {
    return ics::checkInvalidRange(input, min, max);
  }

  constexpr EepParam::type EepParam::checkInvalidEvenRange(type input, type min, type max) {
    return input % 2 ?
           throw std::out_of_range {"Must even value"} :
           checkInvalidRange(input, min, max); // throw std::out_of_range
  }

  constexpr EepParam::type EepParam::checkInvalidFlag(type input, type, type) {
    return !(input & 0x04) ? throw std::invalid_argument {"Eepparam(flag): Must up bits 0x04"} :
           ~(input | ~0x60) ? throw std::invalid_argument {"Eepparam(flag): Must down bits 0x60"} :
           input;
  }

  constexpr EepParam::type EepParam::checkInvalidBaudrate(type input, type, type) {
    return input == Baudrate::RATE115200().get() ? input :
           //input == Baudrate::RATE625000().get() ? input :
           //input == Baudrate::RATE1250000().get() ? input :
           throw std::invalid_argument {"baudrate not exist"};
  }

  constexpr EepParam::type EepParam::checkInvalidOffset(type input, type min, type max) {
    return input < max ? input : // this min < 0; min value is 0
           min < input ? input : // this min < 0; input must is bigger than min.
           throw std::out_of_range {"Eeprom(offset): range over"}; // min < input < max is failed
  }
}

#endif // LIBICS3_ICS3_EEPPARAM_H_
