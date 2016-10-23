#include"ics3/eepparam.hpp"

#include<stdexcept>

constexpr int byteSize {4};
constexpr uint16_t mask {0xF};

void ics::EepParam::write(std::array<uint8_t, 64>& dest) const noexcept {
  uint16_t nowData {data};
  for (size_t i {offset + length - 1}; i >= offset; --i) {
    dest[i] = nowData & mask;
    nowData >>= byteSize;
  }
}

void ics::EepParam::read(const std::array<uint8_t, 64>& src) {
  uint16_t result {0};
  for (size_t i {0}; i < length; ++i)
    result |= (src[offset + length - 1 - i] & mask) << (i * byteSize);
  set(result); // throw std::invalid_argument
}
