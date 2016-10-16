#include"ics3/eeprom.hpp"

#include"ics3/eepparam.hpp"

#include<stdexcept>

ics::EepParam ics::Eeprom::get(EepParam place) const {
  place.read(data);
  return place;
}

void ics::Eeprom::set(const EepParam& param) noexcept {
  param.write(data);
}

ics::Eeprom::Eeprom(const std::array<unsigned char, 64>& src)
: data {src}
{}
