#include "ics3/eeprom.hpp"

#include "ics3/eepparam.hpp"
#include "ics3/ics3.hpp"

#include <stdexcept>

ics::EepParam ics::Eeprom::get(EepParam param) const {
  try {
    param.read(data);
  } catch (...) {
    throw std::runtime_error {"Fail data: non initialize EEPROM by ICS"};
  }
  return param;
}

void ics::Eeprom::set(const EepParam& param) noexcept {
  param.write(data);
}

void ics::Eeprom::copyTo(std::vector<unsigned char>& dest) const noexcept {
  dest.resize(data.size());
  std::copy(data.begin(), data.end(), dest.begin());
}

void ics::Eeprom::copyTo(std::array<unsigned char, 64>& dest) const noexcept {
  dest = data;
}

ics::Eeprom::Eeprom(const std::array<unsigned char, 64>& src)
: data {src}
{}
