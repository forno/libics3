#include"ics3/eepparam.hpp"

#include<stdexcept>

ics::EepParam ics::EepParam::strech() noexcept {
  return EepParam {2, 2, 2, 254, &ics::EepParam::setEven, 60};
}

ics::EepParam ics::EepParam::speed() noexcept {
  return EepParam {4, 2, 1, 127, &ics::EepParam::setNormal, 127};
}

ics::EepParam ics::EepParam::punch() noexcept {
  return EepParam {6, 2, 0, 10, &ics::EepParam::setNormal, 1};
}

ics::EepParam ics::EepParam::deadBand() noexcept {
  return EepParam {8, 2, 0, 5, &ics::EepParam::setNormal, 2};
}

ics::EepParam ics::EepParam::dumping() noexcept {
  return EepParam {10, 2, 1, 255, &ics::EepParam::setNormal, 40};
}

ics::EepParam ics::EepParam::selfTimer() noexcept {
  return EepParam {12, 2, 10, 255, &ics::EepParam::setNormal, 250};
}

ics::EepParam ics::EepParam::flag() noexcept {
  return EepParam {14, 2, 0, 255, &ics::EepParam::setFlag, 0x8C};
}

ics::EepParam ics::EepParam::pulseMax() noexcept {
  return EepParam {16, 4, 3500, 11500, &ics::EepParam::setNormal, 11500};
}

ics::EepParam ics::EepParam::pulseMin() noexcept {
  return EepParam {20, 4, 3500, 11500, &ics::EepParam::setNormal, 3500};
}

ics::EepParam ics::EepParam::baudrate() noexcept {
  return EepParam {26, 2, 0, 10, &ics::EepParam::setBaudrate, 10};
}

ics::EepParam ics::EepParam::temperature() noexcept {
  return EepParam {28, 2, 1, 127, &ics::EepParam::setNormal, 80};
}

ics::EepParam ics::EepParam::current() noexcept {
  return EepParam {30, 2, 1, 63, &ics::EepParam::setNormal, 63};
}

ics::EepParam ics::EepParam::response() noexcept {
  return EepParam {50, 2, 1, 5, &ics::EepParam::setNormal, 3};
}

ics::EepParam ics::EepParam::userOffset() noexcept {
  return EepParam {52, 2, static_cast<uint16_t>(-127), 127, &ics::EepParam::setOffset, 0};
}

ics::EepParam ics::EepParam::id() noexcept {
  return EepParam {56, 2, 0, 31, &ics::EepParam::setNormal, 0};
}

ics::EepParam ics::EepParam::strech1() noexcept {
  return EepParam {58, 2, 2, 254, &ics::EepParam::setEven, 60};
}

ics::EepParam ics::EepParam::strech2() noexcept {
  return EepParam {60, 2, 2, 254, &ics::EepParam::setEven, 60};
}

ics::EepParam ics::EepParam::strech3() noexcept {
  return EepParam {62, 2, 2, 254, &ics::EepParam::setEven, 60};
}

uint16_t ics::EepParam::get() const noexcept {
  return data;
}

void ics::EepParam::set(uint16_t input) {
  (this->*setFunc)(input); // throw std::invalid_argument
}

void ics::EepParam::write(std::array<unsigned char, 64>& dest) const noexcept {
  uint16_t mask {0xF};
  for (size_t i {offset + length - 1}; i >= offset; i--) {
    dest[i] = data & mask;
    mask <<= 4;
  }
}

void ics::EepParam::read(const std::array<unsigned char, 64>& src) {
  uint16_t result {0};
  uint16_t mask {0xF};
  for (size_t i {offset + length - 1}; i >= offset; i--) {
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
  if (input < min) throw std::invalid_argument {"Too small value"};
  if (max < input) throw std::invalid_argument {"Too big value"};
  data = input;
}

void ics::EepParam::setEven(uint16_t input) {
  if (input % 2) throw std::invalid_argument {"Must even value"};
  setNormal(input); // throw std::invalid_argument
}

void ics::EepParam::setFlag(uint16_t input) {
  input &= 0x9f;
  input |= 0x08;
  data = input;
}

void ics::EepParam::setBaudrate(uint16_t input) {
  Baudrate const buf {static_cast<Baudrate>(input)};
  switch (buf) {
  case RATE115200: case RATE625000: case RATE1250000:
    break;
  default:
    throw std::invalid_argument("this baudrate not exist");
  }
  data = buf;
}

void ics::EepParam::setOffset(uint16_t input) {
  static const int8_t minBuf {static_cast<int8_t>(min)}; // I expect stand 0x8000 input cast to minus value
  int8_t inputBuf {static_cast<int8_t>(input)}; // I expect stand 0x8000 input cast to minus value
  if (inputBuf < minBuf) throw std::invalid_argument {"Too small value"};
  if (max < inputBuf) throw std::invalid_argument {"Too big value"};
  data = static_cast<uint8_t>(inputBuf);
}
