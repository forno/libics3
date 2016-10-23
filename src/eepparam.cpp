#include"ics3/eepparam.hpp"

#include<stdexcept>

constexpr int byteSize {4};

void ics::EepParam::write(std::array<unsigned char, 64>& dest) const noexcept {
  uint16_t mask {0xF};
  for (size_t i {offset + length - 1}; i >= offset; --i) {
    dest[i] = data & mask;
    mask <<= byteSize;
  }
}

void ics::EepParam::read(const std::array<unsigned char, 64>& src) {
  constexpr uint16_t mask {0xF};
  uint16_t result {0};
  for (size_t i {0}; i < length; ++i)
    result |= (src[offset + length - 1 - i] & mask) << (i * byteSize);
  set(result); // throw std::invalid_argument
}
