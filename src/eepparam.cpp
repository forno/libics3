#include"ics3/eepparam.hpp"

#include<stdexcept>

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
