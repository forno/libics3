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

uint16_t ics::EepParam::checkInvalidRange(uint16_t input, uint16_t min, uint16_t max) {
  return input < min ? throw std::invalid_argument {"Too small argument"} :
         max < input ? throw std::invalid_argument {"Too small argument"} :
         input;
}

uint16_t ics::EepParam::checkInvalidEvenRange(uint16_t input, uint16_t min, uint16_t max) {
  return input % 2 ?
         throw std::invalid_argument {"Must even value"} :
         checkInvalidRange(input, min, max); // throw std::invalid_argument
}

uint16_t ics::EepParam::checkInvalidFlag(uint16_t input, uint16_t, uint16_t) {
  return input & 0x60 ? throw std::invalid_argument {"Eepparam(flag): Must down bits 0x60"} :
         !(input & 0x04) ? throw std::invalid_argument {"Eepparam(flag): Must up bits 0x04"} :
         input;
}

uint16_t ics::EepParam::checkInvalidBaudrate(uint16_t input, uint16_t, uint16_t) {
  return input == RATE115200 ? input :
         input == RATE625000 ? input :
         input == RATE1250000 ? input :
         throw std::invalid_argument {"baudrate not exist"};
}

uint16_t ics::EepParam::checkInvalidOffset(uint16_t input, uint16_t min, uint16_t max) {
  return input < max ? input : // this min < 0; min of uint16_t is 0
         min < input ? input : // this min < 0; input must bigger than min.
         throw std::invalid_argument {"Eeprom(offset): range over"}; // min < input < max is failed
}
