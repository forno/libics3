#include "ics3/eepparam.hpp"

ics::EepParam ics::EepParam::strech() noexcept {
  static EepParam STRECH(2, 2, 254, &ics::EepParam::setRaw2byte, &ics::EepParam::setEven, 60);
  return STRECH;
}

ics::EepParam ics::EepParam::speed() noexcept {
  static EepParam SPEED(4, 1, 127, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 127);
  return SPEED;
}

ics::EepParam ics::EepParam::punch() noexcept {
  static EepParam PUNCH(6, 0, 10, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 1);
  return PUNCH;
}

ics::EepParam ics::EepParam::deadBand() noexcept {
  static EepParam DEAD_BAND(8, 0, 5, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 2);
  return DEAD_BAND;
}

ics::EepParam ics::EepParam::dumping() noexcept {
  static EepParam DUMPING(10, 1, 255, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 40);
  return DUMPING;
}

ics::EepParam ics::EepParam::selfTimer() noexcept {
  static EepParam SELF_TIMER(12, 10, 255, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 250);
  return SELF_TIMER;
}

ics::EepParam ics::EepParam::flag() noexcept {
  static EepParam FLAG(14, 0, 255, &ics::EepParam::setRaw2byte, &ics::EepParam::setFlag, 0x8C);
  return FLAG;
}

ics::EepParam ics::EepParam::pulseMax() noexcept {
  static EepParam PULSE_MAX(16, 3500, 11500, &ics::EepParam::setRaw4byte, &ics::EepParam::setNormal, 11500);
  return PULSE_MAX;
}

ics::EepParam ics::EepParam::pulseMin() noexcept {
  static EepParam PULSE_MIN(20, 3500, 11500, &ics::EepParam::setRaw4byte, &ics::EepParam::setNormal, 3500);
  return PULSE_MIN;
}

ics::EepParam ics::EepParam::baudrate() noexcept {
  static EepParam BAUDRATE(26, 0, 10, &ics::EepParam::setRaw2byte, &ics::EepParam::setBaudrate, 10);
  return BAUDRATE;
}

ics::EepParam ics::EepParam::temperature() noexcept {
  static EepParam TEMPERATURE(28, 1, 127, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 80);
  return TEMPERATURE;
}

ics::EepParam ics::EepParam::current() noexcept {
  static EepParam CURRENT(30, 1, 63, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 63);
  return CURRENT;
}

ics::EepParam ics::EepParam::response() noexcept {
  static EepParam RESPONSE(50, 1, 5, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 3);
  return RESPONSE;
}

ics::EepParam ics::EepParam::userOffset() noexcept {
  static EepParam USER_OFFSET(52, -127, 127, &ics::EepParam::setRaw2byte, &ics::EepParam::setOffset, 0);
  return USER_OFFSET;
}

ics::EepParam ics::EepParam::id() noexcept {
  static EepParam ID(56, 0, 31, &ics::EepParam::setRaw2byte, &ics::EepParam::setNormal, 0);
  return ID;
}

ics::EepParam ics::EepParam::strech1() noexcept {
  static EepParam STRECH1(58, 2, 254, &ics::EepParam::setRaw2byte, &ics::EepParam::setEven, 60);
  return STRECH1;
}

ics::EepParam ics::EepParam::strech2() noexcept {
  static EepParam STRECH2(60, 2, 254, &ics::EepParam::setRaw2byte, &ics::EepParam::setEven, 60);
  return STRECH2;
}

ics::EepParam ics::EepParam::strech3() noexcept {
  static EepParam STRECH3(62, 2, 254, &ics::EepParam::setRaw2byte, &ics::EepParam::setEven, 60);
  return STRECH3;
}

void ics::EepParam::setRaw(std::array<unsigned char, 64> &dest) const noexcept {
  (this->*setRawFunc)(dest);
}

uint16_t ics::EepParam::get() const noexcept {
  return data;
}

void ics::EepParam::set(uint16_t input) throw(std::invalid_argument) {
  try {
    (this->*setFunc)(input);
  } catch (std::invalid_argument e) {
    throw e;
  }
}

ics::EepParam::EepParam(int offset,
                        uint16_t min,
                        uint16_t max,
                        void (EepParam::*setRawFunc)(std::array<unsigned char, 64> &) const noexcept,
                        void (EepParam::*setFunc)(uint16_t) throw(std::invalid_argument),
                        uint16_t default_data
                       ) noexcept
: offset(offset),
  min(min),
  max(max),
  setRawFunc(setRawFunc),
  setFunc(setFunc),
  data(default_data)
{}

void ics::EepParam::setRaw2byte(std::array<unsigned char, 64> &dest) const noexcept {
  dest[offset] =     data & 0xF0;
  dest[offset + 1] = data & 0x0F;
}

void ics::EepParam::setRaw4byte(std::array<unsigned char, 64> &dest) const noexcept {
  dest[offset] =     data & 0xF000;
  dest[offset + 1] = data & 0x0F00;
  dest[offset + 2] = data & 0x00F0;
  dest[offset + 3] = data & 0x000F;
}

void ics::EepParam::setNormal(uint16_t input) throw(std::invalid_argument) {
  if (input < min) throw std::invalid_argument("Too small value");
  if (max < input) throw std::invalid_argument("Too big value");
  data = input;
}

void ics::EepParam::setEven(uint16_t input) throw(std::invalid_argument) {
  if (input % 2) throw std::invalid_argument("Must even value");
  try {
    setNormal(input);
  } catch (std::invalid_argument e) {
    throw e;
  }
}

void ics::EepParam::setFlag(uint16_t input) throw(std::invalid_argument) {
  input &= 010011111;
  input |= 000001000;
  data = input;
}

void ics::EepParam::setBaudrate(uint16_t input) throw(std::invalid_argument) {
  EepBaudrate const buf = static_cast<EepBaudrate>(input);
  switch (buf) {
  case RATE115200: case RATE625000: case RATE1250000:
    break;
  default:
    throw std::invalid_argument("this baudrate not exist");
  }
  data = input;
}

void ics::EepParam::setOffset(uint16_t input) throw(std::invalid_argument) {
  static const int8_t minBuf = min; // I expect stand 0x8000 input cast to minus value
  int8_t inputBuf = input; // I expect stand 0x8000 input cast to minus value
  if (inputBuf < minBuf) throw std::invalid_argument("Too small value");
  if (max < inputBuf) throw std::invalid_argument("Too big value");
  data = static_cast<uint8_t>(inputBuf);
}
