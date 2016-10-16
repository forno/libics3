#include "ics3/eepparam.hpp"

ics::EepParam ics::EepParam::strech() noexcept {
  static const EepParam STRECH(2, 2, 2, 254, &ics::EepParam::setEven, 60);
  return STRECH;
}

ics::EepParam ics::EepParam::speed() noexcept {
  static const EepParam SPEED(4, 2, 1, 127, &ics::EepParam::setNormal, 127);
  return SPEED;
}

ics::EepParam ics::EepParam::punch() noexcept {
  static const EepParam PUNCH(6, 2, 0, 10, &ics::EepParam::setNormal, 1);
  return PUNCH;
}

ics::EepParam ics::EepParam::deadBand() noexcept {
  static const EepParam DEAD_BAND(8, 2, 0, 5, &ics::EepParam::setNormal, 2);
  return DEAD_BAND;
}

ics::EepParam ics::EepParam::dumping() noexcept {
  static const EepParam DUMPING(10, 2, 1, 255, &ics::EepParam::setNormal, 40);
  return DUMPING;
}

ics::EepParam ics::EepParam::selfTimer() noexcept {
  static const EepParam SELF_TIMER(12, 2, 10, 255, &ics::EepParam::setNormal, 250);
  return SELF_TIMER;
}

ics::EepParam ics::EepParam::flag() noexcept {
  static const EepParam FLAG(14, 2, 0, 255, &ics::EepParam::setFlag, 0x8C);
  return FLAG;
}

ics::EepParam ics::EepParam::pulseMax() noexcept {
  static const EepParam PULSE_MAX(16, 4, 3500, 11500, &ics::EepParam::setNormal, 11500);
  return PULSE_MAX;
}

ics::EepParam ics::EepParam::pulseMin() noexcept {
  static const EepParam PULSE_MIN(20, 4, 3500, 11500, &ics::EepParam::setNormal, 3500);
  return PULSE_MIN;
}

ics::EepParam ics::EepParam::baudrate() noexcept {
  static const EepParam BAUDRATE(26, 2, 0, 10, &ics::EepParam::setBaudrate, 10);
  return BAUDRATE;
}

ics::EepParam ics::EepParam::temperature() noexcept {
  static const EepParam TEMPERATURE(28, 2, 1, 127, &ics::EepParam::setNormal, 80);
  return TEMPERATURE;
}

ics::EepParam ics::EepParam::current() noexcept {
  static const EepParam CURRENT(30, 2, 1, 63, &ics::EepParam::setNormal, 63);
  return CURRENT;
}

ics::EepParam ics::EepParam::response() noexcept {
  static const EepParam RESPONSE(50, 2, 1, 5, &ics::EepParam::setNormal, 3);
  return RESPONSE;
}

ics::EepParam ics::EepParam::userOffset() noexcept {
  static const EepParam USER_OFFSET(52, 2, -127, 127, &ics::EepParam::setOffset, 0);
  return USER_OFFSET;
}

ics::EepParam ics::EepParam::id() noexcept {
  static const EepParam ID(56, 2, 0, 31, &ics::EepParam::setNormal, 0);
  return ID;
}

ics::EepParam ics::EepParam::strech1() noexcept {
  static const EepParam STRECH1(58, 2, 2, 254, &ics::EepParam::setEven, 60);
  return STRECH1;
}

ics::EepParam ics::EepParam::strech2() noexcept {
  static const EepParam STRECH2(60, 2, 2, 254, &ics::EepParam::setEven, 60);
  return STRECH2;
}

ics::EepParam ics::EepParam::strech3() noexcept {
  static const EepParam STRECH3(62, 2, 2, 254, &ics::EepParam::setEven, 60);
  return STRECH3;
}

uint16_t ics::EepParam::get() const noexcept {
  return data;
}

void ics::EepParam::set(uint16_t input) {
  (this->*setFunc)(input); // throw std::invalid_argument
}

void ics::EepParam::write(std::array<unsigned char, 64>& dest) const noexcept {
  uint16_t mask = 0xF;
  for (size_t i = offset + length - 1; i >= offset; i--) {
    dest[i] = data & mask;
    mask <<= 4;
  }
}

void ics::EepParam::read(const std::array<unsigned char, 64>& src) {
  uint16_t result = 0;
  uint16_t mask = 0xF;
  for (size_t i = offset + length - 1; i >= offset; i--) {
    result |= src[i] & mask;
    mask <<= 4;
  }
  set(result); // throw std::invalid_argument
}

ics::EepParam::EepParam(size_t offset,
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

void ics::EepParam::setNormal(uint16_t input) {
  if (input < min) throw std::invalid_argument("Too small value");
  if (max < input) throw std::invalid_argument("Too big value");
  data = input;
}

void ics::EepParam::setEven(uint16_t input) {
  if (input % 2) throw std::invalid_argument("Must even value");
  setNormal(input); // throw std::invalid_argument
}

void ics::EepParam::setFlag(uint16_t input) {
  input &= 010011111;
  input |= 000001000;
  data = input;
}

void ics::EepParam::setBaudrate(uint16_t input) {
  Baudrate const buf = static_cast<Baudrate>(input);
  switch (buf) {
  case RATE115200: case RATE625000: case RATE1250000:
    break;
  default:
    throw std::invalid_argument("this baudrate not exist");
  }
  data = buf;
}

void ics::EepParam::setOffset(uint16_t input) {
  static const int8_t minBuf = min; // I expect stand 0x8000 input cast to minus value
  int8_t inputBuf = input; // I expect stand 0x8000 input cast to minus value
  if (inputBuf < minBuf) throw std::invalid_argument("Too small value");
  if (max < inputBuf) throw std::invalid_argument("Too big value");
  data = static_cast<uint8_t>(inputBuf);
}
