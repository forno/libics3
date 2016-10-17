#include"ics3/eeprom.hpp"

ics::EepParam ics::Eeprom::get(EepParam place) const {
  place.read(data);
  return place;
}

ics::Eeprom::Eeprom(const std::array<unsigned char, 64>& src)
: data {}
{
  std::copy(src.begin(), src.end(), data.begin());
}
