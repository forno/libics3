#include"ics3/eeprom.hpp"

ics::Eeprom::Eeprom(const std::array<unsigned char, 64>& src)
: data {}
{
  std::copy(src.begin(), src.end(), data.begin());
}
