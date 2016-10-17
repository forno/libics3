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
