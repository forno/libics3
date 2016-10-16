#include"ics3/eeprom.hpp"

#include"ics3/eepparam.hpp"

#include<stdexcept>

ics::EepParam ics::Eeprom::get(EepParam param) const {
  param.read(data);
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
